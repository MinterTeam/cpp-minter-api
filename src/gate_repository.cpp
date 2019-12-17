/*!
 * minter_api.
 * gate_repository.cpp
 *
 * \date 2019
 * \author Eduard Maximovich (edward.vstock@gmail.com)
 * \link   https://github.com/edwardstock
 */

#include "minter/api/gate/repository.h"
#include "minter/api/gate/results.hpp"

using namespace minter::gate;

TASK_RES(gas_value)
repository::get_min_gas() {
    auto req = newRequest();
    req.add_path("min-gas");

    return MAKE_TASK(gas_value, req);
}

TASK_RES(tx_count_value)
gate::repository::get_tx_count(const address_t& address) {
    auto req = newRequest();
    req.add_path("nonce");
    req.add_path(address.to_string());

    return MAKE_TASK(tx_count_value, req);
}

TASK_RES(commission_value)
gate::repository::get_tx_commission_value(const dev::bytes_data& tx_sign) {
    auto req = newRequest();
    req.add_path("estimate");
    req.add_path("tx-commission");
    req.add_query({"transaction", tx_sign.to_hex()});

    return MAKE_TASK(commission_value, req);
}

TASK_RES(exchange_buy_value)
gate::repository::get_exchange_buy_currency(const std::string& coin_to_sell,
                                            const dev::bigdec18& value_to_buy,
                                            const std::string& coin_to_buy) {
    auto req = newRequest();
    req.add_path("estimate/coin-buy");
    req.add_query({"coinToSell", coin_to_sell});
    req.add_query({"valueToBuy", utils::to_string(minter::utils::normalize_value(value_to_buy))});
    req.add_query({"coinToBuy", coin_to_buy});

    return MAKE_TASK(exchange_buy_value, req);
}

TASK_RES(exchange_sell_value)
gate::repository::get_exchange_sell_currency(const std::string& coin_to_sell,
                                             const dev::bigdec18& value_to_sell,
                                             const std::string& coin_to_buy) {
    auto req = newRequest();
    req.add_path("estimate/coin-sell");
    req.add_query({"coinToSell", coin_to_sell});
    req.add_query({"valueToSell", utils::to_string(minter::utils::normalize_value(value_to_sell))});
    req.add_query({"coinToBuy", coin_to_buy});

    return MAKE_TASK(exchange_sell_value, req);
}

TASK_RES(tx_send_result)
gate::repository::send_tx(const dev::bytes_data& tx_sign) {
    auto req = newRequest();
    req.set_header({"content-type", "application/x-www-form-urlencoded"});
    req.set_method(httb::request::method::post);
    req.add_path("transaction/push");

    {
        nlohmann::json j;
        j["transaction"] = tx_sign.to_hex();
        std::stringstream ss;
        ss << j;
        req.set_body(httb::body_string(ss.str()));
    }

    return MAKE_TASK(tx_send_result, req);
}

tx_init_data gate::repository::get_tx_init_data(const minter::address_t& address, bool& error) {
    using namespace minter::gate;

    error = false;
    dev::bigint nonce = dev::bigint("1");
    dev::bigint gas = dev::bigint("1");

    auto nonce_task =
        get_tx_count(address)
            ->success([&nonce](result<tx_count_value> result) {
                nonce = result.data.count + dev::bigint("1");
            })
            ->error([&error](httb::response resp, result<tx_count_value> result) {
                error = true;
                std::cerr << resp.status_message << std::endl;
                std::cerr << resp.get_body() << std::endl;
            });
    auto gas_task =
        get_min_gas()
            ->success([&gas](result<gas_value> result) {
                gas = result.data.gas;
            })
            ->error([&error](httb::response resp, result<gas_value> result) {
                error = true;
                std::cerr << resp.status_message << std::endl;
                std::cerr << resp.get_body() << std::endl;
            });

    minter::net::pair_task<
        minter::gate::result<tx_count_value>,
        result<gas_value>>
        executor(nonce_task, gas_task);

    executor.execute();

    tx_init_data out{nonce, gas};

    return out;
}
