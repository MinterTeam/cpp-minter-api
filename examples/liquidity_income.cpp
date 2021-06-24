/*!
 * minter_api.
 * liquidity_income.cpp
 *
 * \date 2021
 * \author Eduard Maximovich (edward.vstock@gmail.com)
 * \link   https://github.com/edwardstock
 */

#include <iostream>
#include <minter/api/explorer/explorer_repo.h>

struct liquidity_share {
    minter::explorer::coin_item_base coin0, coin1;
    dev::bigdec18 amount0, amount1;
    minter::explorer::pool_provider provider;
    dev::bigdec18 remAmount0, remAmount1;
};

int main() {
    mpd_setminalloc(bigmath::MINALLOC);

    namespace exp = minter::explorer;
    exp::repository exp_repo;
    minter::address_t address("<YOUR_MINTER_ADDRESS_HERE>");

    exp::tx_list_t out_txs;
    exp::pool_providers current_shares;

    try {
        auto tx_res = exp_repo.get_transactions(address, 0, 0, exp::repository::tx_send_type::outgoing).as_blocking();
        if (tx_res.count() && tx_res.first().error.code == 0) {
            out_txs = tx_res.first().data;
        } else {
            throw std::runtime_error(tx_res.first().error.message);
        }
        auto shares_res = exp_repo.get_pool_providers(address).as_blocking();
        if (shares_res.count() && shares_res.first().error.code == 0) {
            current_shares = shares_res.first().data;
        } else {
            throw std::runtime_error(shares_res.first().error.message);
        }

    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    exp::tx_list_t add_liquidity_txs;
    exp::tx_list_t rem_liquidity_txs;
    for (auto&& tx : out_txs) {
        if (tx.type == minter::tx_type_val::add_liquidity) {
            add_liquidity_txs.push_back(std::move(tx));
        } else if (tx.type == minter::tx_type_val::remove_liquidity) {
            rem_liquidity_txs.push_back(std::move(tx));
        }
    }

    if (add_liquidity_txs.empty()) {
        std::cerr << "Not found any add_liquidity transactions. Exiting." << std::endl;
        return 0;
    }

    std::unordered_map<std::string, liquidity_share> shares_sum;

    for (const auto& tx : add_liquidity_txs) {
        auto* data = (exp::tx_add_liquidity_result*) tx.data.get();
        if (shares_sum.count(data->pool_token.symbol)) {
            auto& share = shares_sum.at(data->pool_token.symbol);
            if (share.coin0.id == data->coin0.id) {
                share.amount0 = share.amount0 + data->volume0;
                share.amount1 = share.amount1 + data->volume1;
            } else {
                share.amount0 = share.amount0 + data->volume1;
                share.amount1 = share.amount1 + data->volume0;
            }

        } else {

            liquidity_share share;
            share.coin0 = data->coin0;
            share.coin1 = data->coin1;
            share.amount0 = data->volume0;
            share.amount1 = data->volume1;
            share.remAmount0 = dev::bigdec18("0");
            share.remAmount1 = dev::bigdec18("0");

            auto active_share = std::find_if(current_shares.begin(), current_shares.end(), [data, &tx](const exp::pool_provider& pp) {
                return pp.token.symbol == data->pool_token.symbol;
            });
            if (active_share != current_shares.end()) {
                share.provider = (*active_share);
                if (share.provider.coin0.id != share.coin0.id) {
                    auto np0 = share.provider.amount1;
                    auto np1 = share.provider.amount0;
                    auto cp0 = share.provider.coin1;
                    auto cp1 = share.provider.coin0;
                    share.provider.amount0 = np0;
                    share.provider.amount1 = np1;
                    share.provider.coin0 = cp0;
                    share.provider.coin1 = cp1;
                }
                shares_sum.insert(std::pair<std::string, liquidity_share>(data->pool_token.symbol, share));
            }
        }
    }

    for (const auto& tx : rem_liquidity_txs) {
        auto* data = (exp::tx_remove_liquidity_result*) tx.data.get();
        if (!shares_sum.count(data->pool_token.symbol)) {
            continue;
        }
        auto& share = shares_sum.at(data->pool_token.symbol);
        if (share.coin0.id == data->coin0.id) {
            share.remAmount0 = share.remAmount0 + data->volume0;
            share.remAmount1 = share.remAmount1 + data->volume1;
        } else {
            share.remAmount0 = share.remAmount0 + data->volume1;
            share.remAmount1 = share.remAmount1 + data->volume0;
        }
    }

    std::cout << "Found " << shares_sum.size() << " shares" << std::endl;
    const dev::bigdec18 hund("100");
    const dev::bigdec18 zero("0");

    for (const auto& share : shares_sum) {
        std::cout << share.first << ":\n";
        std::cout << "\t           " << share.second.coin0.symbol << " / " << share.second.coin1.symbol << "\n";

        dev::bigdec18 current0, current1;
        dev::bigdec18 added0, added1;

        current0 = share.second.provider.amount0;
        current1 = share.second.provider.amount1;
        added0 = share.second.amount0;
        added1 = share.second.amount1;
        dev::bigdec18 removed0 = share.second.remAmount0;
        dev::bigdec18 removed1 = share.second.remAmount1;

        std::cout << "\tAdded:    " << added0.format(".4f") << " / " << added1.format(".4f") << "\n";
        std::cout << "\tRemoved:  " << removed0.format(".4f") << " / " << removed1.format(".4f") << "\n";
        std::cout << "\tCurrent:  " << current0.format(".4f") << " / " << current1.format(".4f") << "\n";

        dev::bigdec18 first = hund - (((added0 - removed0) / current0) * hund);
        dev::bigdec18 second = hund - (((added1 - removed1) / current1) * hund);

        std::cout << "\tDiff:    ";
        if (first > zero) {
            std::cout << "+" << first.format(".4f") << "%";
        } else {
            std::cout << first.format(".4f") << "%";
        }
        std::cout << " / ";
        if (second > zero) {
            std::cout << "+" << second.format(".4f") << "%";
        } else {
            std::cout << second.format(".4f") << "%";
        }
        std::cout << " = ";
        dev::bigdec18 diffSum = first + second;
        if (diffSum > zero) {
            std::cout << "+" << diffSum.format(".4f") << "%";
        } else {
            std::cout << diffSum.format(".4f") << "%";
        }
        std::cout << std::endl;
    }

    return 0;
}