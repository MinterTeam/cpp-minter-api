/*!
 * minter_api.
 * gate_repository.cpp
 *
 * \date 2019
 * \author Eduard Maximovich (edward.vstock@gmail.com)
 * \link   https://github.com/edwardstock
 */

#include "minter/api/gate/gate_repo.h"

#include <minter/tx.hpp>

using namespace minter::gate;

dev::bigdec18 minter::gate::get_tx_fee_by_type(minter::gate::price_commissions tx_fees, minter::tx_type_val type) {
    dev::bigdec18 out;
    switch (type) {
    case minter::tx_type_val::send_coin:
        out = minter::utils::humanize_value(tx_fees.send);
        break;
    case minter::tx_type_val::sell_coin:
        out = minter::utils::humanize_value(tx_fees.sell_bancor);
        break;
    case minter::tx_type_val::sell_all_coins:
        out = minter::utils::humanize_value(tx_fees.sell_all_bancor);
        break;
    case minter::tx_type_val::buy_coin:
        out = minter::utils::humanize_value(tx_fees.buy_bancor);
        break;
    case minter::tx_type_val::create_coin:
        out = minter::utils::humanize_value(tx_fees.create_coin);
        break;
    case minter::tx_type_val::declare_candidacy:
        out = minter::utils::humanize_value(tx_fees.declare_candidacy);
        break;
    case minter::tx_type_val::delegate:
        out = minter::utils::humanize_value(tx_fees.delegate);
        break;
    case minter::tx_type_val::unbond:
        out = minter::utils::humanize_value(tx_fees.unbond);
        break;
    case minter::tx_type_val::redeem_check:
        out = minter::utils::humanize_value(tx_fees.redeem_check);
        break;
    case minter::tx_type_val::set_candidate_on:
        out = minter::utils::humanize_value(tx_fees.set_candidate_on);
        break;
    case minter::tx_type_val::set_candidate_off:
        out = minter::utils::humanize_value(tx_fees.set_candidate_off);
        break;
    case minter::tx_type_val::create_multisig:
        out = minter::utils::humanize_value(tx_fees.create_multisig);
        break;
    case minter::tx_type_val::multisend:
        out = minter::utils::humanize_value(tx_fees.multisend_base);
        break;
    case minter::tx_type_val::edit_candidate:
        out = minter::utils::humanize_value(tx_fees.edit_candidate);
        break;

    case minter::tx_type_val::set_halt_block:
        out = minter::utils::humanize_value(tx_fees.set_halt_block);
        break;
    case minter::tx_type_val::recreate_coin:
        out = minter::utils::humanize_value(tx_fees.recreate_coin);
        break;
    case minter::tx_type_val::edit_coin_owner:
        out = minter::utils::humanize_value(tx_fees.edit_ticker_owner);
        break;
    case minter::tx_type_val::edit_multisig:
        out = minter::utils::humanize_value(tx_fees.edit_multisig);
        break;
    case minter::tx_type_val::edit_candidate_public_key:
        out = minter::utils::humanize_value(tx_fees.edit_candidate_public_key);
        break;

    case minter::tx_type_val::add_liquidity:
        out = minter::utils::humanize_value(tx_fees.add_liquidity);
        break;
    case minter::tx_type_val::remove_liquidity:
        out = minter::utils::humanize_value(tx_fees.remove_liquidity);
        break;
    case minter::tx_type_val::sell_swap_pool:
        out = minter::utils::humanize_value(tx_fees.sell_pool_base);
        break;
    case minter::tx_type_val::buy_swap_pool:
        out = minter::utils::humanize_value(tx_fees.buy_pool_base);
        break;
    case minter::tx_type_val::sell_all_swap_pool:
        out = minter::utils::humanize_value(tx_fees.sell_all_pool_base);
        break;
    case minter::tx_type_val::edit_candidate_commission:
        out = minter::utils::humanize_value(tx_fees.edit_candidate_commission);
        break;
    case minter::tx_type_val::mint_token:
        out = minter::utils::humanize_value(tx_fees.mint_token);
        break;
    case minter::tx_type_val::burn_token:
        out = minter::utils::humanize_value(tx_fees.burn_token);
        break;
    case minter::tx_type_val::create_token:
        out = minter::utils::humanize_value(tx_fees.create_token);
        break;
    case minter::tx_type_val::recreate_token:
        out = minter::utils::humanize_value(tx_fees.recreate_token);
        break;
    case minter::tx_type_val::vote_commission:
        out = minter::utils::humanize_value(tx_fees.vote_commission);
        break;
    case minter::tx_type_val::vote_update:
        out = minter::utils::humanize_value(tx_fees.vote_update);
        break;
    case minter::tx_type_val::create_swap_pool:
        out = minter::utils::humanize_value(tx_fees.create_swap_pool);
        break;

    default:
        out = dev::bigdec18("1");
    }
    return out;
}

minter::gate::repository::repository() {
}

TASK_RES_ROOT(gas_value)
minter::gate::repository::get_min_gas() {
    auto req = create_request();
    req.add_path("min_gas_price");

    return MAKE_TASK_ROOT(gas_value, req);
}

TASK_RES_ROOT(tx_count_value)
minter::gate::repository::get_tx_count(const minter::address_t& address) {
    auto req = create_request();
    req.add_path("nonce");
    req.add_path((address.to_string()));

    return MAKE_TASK_ROOT(tx_count_value, req);
}

TASK_RES_ROOT(minter::gate::price_commissions)
minter::gate::repository::get_price_commissions() {
    auto req = create_request();
    req.add_path("price_commissions");

    return MAKE_TASK_ROOT(price_commissions, req);
}

TASK_RES_ROOT(commission_value)
minter::gate::repository::get_tx_commission_value(const dev::bytes_data& tx_sign) {
    auto req = create_request();
    req.add_path("estimate_tx_commission");
    req.add_path((tx_sign.to_hex()));

    return MAKE_TASK_ROOT(commission_value, req);
}

TASK_RES_ROOT(minter::gate::commission_value)
minter::gate::repository::get_base_tx_fee() {
    minter::privkey_t pk("1FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFC");
    minter::address_t addr(pk);
    auto tx_builder = minter::new_tx();
    tx_builder->set_chain_id(MINTER_CHAIN_ID);
    tx_builder->set_gas_coin_id(minter::def_coin_id);
    tx_builder->set_gas_price(dev::bigint("1"));
    auto data = tx_builder->tx_send_coin();
    data->set_coin_id(minter::def_coin_id);
    data->set_value("0");
    data->set_to(addr);
    auto tx = data->build();
    auto sign = tx->sign_single(pk);

    return get_tx_commission_value(sign);
}

TASK_RES_ROOT(exchange_buy_value)
minter::gate::repository::get_exchange_buy_currency(const std::string& coin_to_sell,
                                                    const dev::bigdec18& value_to_buy,
                                                    const std::string& coin_to_buy) {
    auto req = create_request();
    req.add_path("estimate_coin_buy");
    req.add_query({"coin_id_to_sell", (coin_to_sell)});
    req.add_query({"value_to_buy", (
                                       minter::utils::to_string(minter::utils::normalize_value(value_to_buy)))});
    req.add_query({"coin_id_to_buy", (coin_to_buy)});

    return MAKE_TASK_ROOT(exchange_buy_value, req);
}

TASK_RES_ROOT(exchange_sell_value)
minter::gate::repository::get_exchange_sell_currency(const std::string& coin_to_sell,
                                                     const dev::bigdec18& value_to_sell,
                                                     const std::string& coin_to_buy) {
    auto req = create_request();
    req.add_path("estimate_coin_sell");
    req.add_query({"coin_id_to_sell", (coin_to_sell)});
    req.add_query({"value_to_sell", (
                                        minter::utils::to_string(minter::utils::normalize_value(value_to_sell)))});
    req.add_query({"coin_id_to_buy", (coin_to_buy)});

    return MAKE_TASK_ROOT(exchange_sell_value, req);
}

TASK_RES_ROOT(tx_send_result)
minter::gate::repository::send_tx(const dev::bytes_data& tx_sign) {
    auto req = create_request();
    req.set_header({"content-type", "application/json; charset=UTF-8"});
    req.set_method(minter::api::request::method::post);
    req.add_path("send_transaction");
    {
        nlohmann::json j;
        j["tx"] = tx_sign.to_hex();
        std::stringstream ss;
        ss << j;
        req.set_body((ss.str()));
    }

    return MAKE_TASK_ROOT(tx_send_result, req);
}

TASK_RES_ROOT(minter::gate::tx_init_data)
minter::gate::repository::get_tx_init_data(const minter::address_t& address) {

    return get_min_gas()
        .combine_latest([this](gas_value gas, tx_count_value nonce, price_commissions fees) {
            tx_init_data init_data;
            init_data.nonce = (nonce.count + dev::bigint("1"));
            init_data.gas = gas.gas;
            init_data.gas_coin = minter::def_coin_id;
            init_data.gas_representing_coin = fees.coin;
            init_data.gas_base_coin_rate = dev::bigdec18("1");
            init_data.tx_fees = fees;

            if (init_data.gas_representing_coin.id != minter::def_coin_id) {
                auto tx_fee = get_base_tx_fee().as_blocking().first();
                // initData.gasBaseCoinRate = it.result.getValue() / initData.priceCommissions.getByType(OperationType.SendCoin).humanizeDecimal()
                init_data.gas_base_coin_rate = minter::utils::humanize_value(tx_fee.value / init_data.tx_fees.send);
            }

            return init_data;
        },
                        get_tx_count(address), get_price_commissions());
}

std::string minter::gate::repository::repository::get_base_url() const {
    return {MINTER_GATE_API};
}