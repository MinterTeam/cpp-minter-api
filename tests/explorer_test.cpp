/*!
 * minter_api.
 * explorer_test.cpp
 *
 * \date 2019
 * \author Eduard Maximovich (edward.vstock@gmail.com)
 * \link   https://github.com/edwardstock
 */

#define JSON_DIAGNOSTICS 1
#include <gtest/gtest.h>
#include <iostream>
#include <minter/api/explorer/explorer_repo.h>
#include <minter/api/gate/gate_repo.h>
#include <toolbox/strings.hpp>

TEST(Explorer, PoolRoute) {
    mpd_setminalloc(4);
    namespace exp = minter::explorer;
    namespace gate = minter::gate;

    exp::repository exp_repo;

    exp::coin_item_base bip{
        dev::bigint("0"), "BIP", exp::coin_type::coin};
    exp::coin_item_base navalny{
        dev::bigint("2054"), "NAVALNY", exp::coin_type::token};

    auto res = exp_repo.get_pool_route(bip, navalny, dev::bigdec18("1000"), exp::pool_swap_type::buy).as_blocking();

    exp::pool_route route = res.first();
    std::cout << route.coins.size() << std::endl;
    std::cout << route.amount_out << std::endl;
    std::cout << route.amount_in << std::endl;
}

TEST(Explorer, DecodeError) {
    const std::string error_result = R"({"error":{"code":"301","message":"\"From\" coin equals to \"to\" coin","data":{"code":"301","coin_id_to_buy":"13","coin_id_to_sell":"13","coin_to_buy":"NUT","coin_to_sell":"NUT"}}})";

    auto val = nlohmann::json::parse(error_result);

    minter::gate::tx_send_result res = val.get<minter::gate::tx_send_result>();

    ASSERT_EQ(301, res.error.code);
}
