
// AUTOGENERATED cpp. DO NOT modify manually.
//
#include "minter/api/gate/gate_results.h"

void ::minter::gate::from_json(const nlohmann::json& j, ::minter::gate::gas_value& resp) {
    if (j.find("error") != j.end() && !j.at("error").is_null())
        j.at("error").get_to<minter::gate::error_result>(resp.error);
    if (j.find("min_gas_price") != j.end() && !j.at("min_gas_price").is_null())
        j.at("min_gas_price").get_to<dev::bigint>(resp.gas);
}
void ::minter::gate::to_json(nlohmann::json& j, const ::minter::gate::gas_value& resp) {
    j = nlohmann::json{
        {"error", resp.error},
        {"min_gas_price", resp.gas},
    };
}
void ::minter::gate::from_json(const nlohmann::json& j, ::minter::gate::price_commissions& resp) {
    if (j.find("error") != j.end() && !j.at("error").is_null())
        j.at("error").get_to<minter::gate::error_result>(resp.error);
    if (j.find("coin") != j.end() && !j.at("coin").is_null())
        j.at("coin").get_to<minter::explorer::coin_item_base>(resp.coin);
    if (j.find("payload_byte") != j.end() && !j.at("payload_byte").is_null())
        j.at("payload_byte").get_to<dev::bigint>(resp.payload_byte);
    if (j.find("send") != j.end() && !j.at("send").is_null())
        j.at("send").get_to<dev::bigint>(resp.send);
    if (j.find("buy_bancor") != j.end() && !j.at("buy_bancor").is_null())
        j.at("buy_bancor").get_to<dev::bigint>(resp.buy_bancor);
    if (j.find("sell_bancor") != j.end() && !j.at("sell_bancor").is_null())
        j.at("sell_bancor").get_to<dev::bigint>(resp.sell_bancor);
    if (j.find("sell_all_bancor") != j.end() && !j.at("sell_all_bancor").is_null())
        j.at("sell_all_bancor").get_to<dev::bigint>(resp.sell_all_bancor);
    if (j.find("buy_pool_base") != j.end() && !j.at("buy_pool_base").is_null())
        j.at("buy_pool_base").get_to<dev::bigint>(resp.buy_pool_base);
    if (j.find("sell_pool_base") != j.end() && !j.at("sell_pool_base").is_null())
        j.at("sell_pool_base").get_to<dev::bigint>(resp.sell_pool_base);
    if (j.find("sell_all_pool_base") != j.end() && !j.at("sell_all_pool_base").is_null())
        j.at("sell_all_pool_base").get_to<dev::bigint>(resp.sell_all_pool_base);
    if (j.find("buy_pool_delta") != j.end() && !j.at("buy_pool_delta").is_null())
        j.at("buy_pool_delta").get_to<dev::bigint>(resp.buy_pool_delta);
    if (j.find("sell_pool_delta") != j.end() && !j.at("sell_pool_delta").is_null())
        j.at("sell_pool_delta").get_to<dev::bigint>(resp.sell_pool_delta);
    if (j.find("sell_all_pool_delta") != j.end() && !j.at("sell_all_pool_delta").is_null())
        j.at("sell_all_pool_delta").get_to<dev::bigint>(resp.sell_all_pool_delta);
    if (j.find("create_ticker3") != j.end() && !j.at("create_ticker3").is_null())
        j.at("create_ticker3").get_to<dev::bigint>(resp.create_ticker3);
    if (j.find("create_ticker4") != j.end() && !j.at("create_ticker4").is_null())
        j.at("create_ticker4").get_to<dev::bigint>(resp.create_ticker4);
    if (j.find("create_ticker5") != j.end() && !j.at("create_ticker5").is_null())
        j.at("create_ticker5").get_to<dev::bigint>(resp.create_ticker5);
    if (j.find("create_ticker6") != j.end() && !j.at("create_ticker6").is_null())
        j.at("create_ticker6").get_to<dev::bigint>(resp.create_ticker6);
    if (j.find("create_ticker7_10") != j.end() && !j.at("create_ticker7_10").is_null())
        j.at("create_ticker7_10").get_to<dev::bigint>(resp.create_ticker7_10);
    if (j.find("create_coin") != j.end() && !j.at("create_coin").is_null())
        j.at("create_coin").get_to<dev::bigint>(resp.create_coin);
    if (j.find("create_token") != j.end() && !j.at("create_token").is_null())
        j.at("create_token").get_to<dev::bigint>(resp.create_token);
    if (j.find("recreate_coin") != j.end() && !j.at("recreate_coin").is_null())
        j.at("recreate_coin").get_to<dev::bigint>(resp.recreate_coin);
    if (j.find("recreate_token") != j.end() && !j.at("recreate_token").is_null())
        j.at("recreate_token").get_to<dev::bigint>(resp.recreate_token);
    if (j.find("declare_candidacy") != j.end() && !j.at("declare_candidacy").is_null())
        j.at("declare_candidacy").get_to<dev::bigint>(resp.declare_candidacy);
    if (j.find("delegate") != j.end() && !j.at("delegate").is_null())
        j.at("delegate").get_to<dev::bigint>(resp.delegate);
    if (j.find("unbond") != j.end() && !j.at("unbond").is_null())
        j.at("unbond").get_to<dev::bigint>(resp.unbond);
    if (j.find("redeem_check") != j.end() && !j.at("redeem_check").is_null())
        j.at("redeem_check").get_to<dev::bigint>(resp.redeem_check);
    if (j.find("set_candidate_on") != j.end() && !j.at("set_candidate_on").is_null())
        j.at("set_candidate_on").get_to<dev::bigint>(resp.set_candidate_on);
    if (j.find("set_candidate_off") != j.end() && !j.at("set_candidate_off").is_null())
        j.at("set_candidate_off").get_to<dev::bigint>(resp.set_candidate_off);
    if (j.find("create_multisig") != j.end() && !j.at("create_multisig").is_null())
        j.at("create_multisig").get_to<dev::bigint>(resp.create_multisig);
    if (j.find("multisend_base") != j.end() && !j.at("multisend_base").is_null())
        j.at("multisend_base").get_to<dev::bigint>(resp.multisend_base);
    if (j.find("multisend_delta") != j.end() && !j.at("multisend_delta").is_null())
        j.at("multisend_delta").get_to<dev::bigint>(resp.multisend_delta);
    if (j.find("edit_candidate") != j.end() && !j.at("edit_candidate").is_null())
        j.at("edit_candidate").get_to<dev::bigint>(resp.edit_candidate);
    if (j.find("set_halt_block") != j.end() && !j.at("set_halt_block").is_null())
        j.at("set_halt_block").get_to<dev::bigint>(resp.set_halt_block);
    if (j.find("edit_ticker_owner") != j.end() && !j.at("edit_ticker_owner").is_null())
        j.at("edit_ticker_owner").get_to<dev::bigint>(resp.edit_ticker_owner);
    if (j.find("edit_multisig") != j.end() && !j.at("edit_multisig").is_null())
        j.at("edit_multisig").get_to<dev::bigint>(resp.edit_multisig);
    if (j.find("edit_candidate_public_key") != j.end() && !j.at("edit_candidate_public_key").is_null())
        j.at("edit_candidate_public_key").get_to<dev::bigint>(resp.edit_candidate_public_key);
    if (j.find("create_swap_pool") != j.end() && !j.at("create_swap_pool").is_null())
        j.at("create_swap_pool").get_to<dev::bigint>(resp.create_swap_pool);
    if (j.find("add_liquidity") != j.end() && !j.at("add_liquidity").is_null())
        j.at("add_liquidity").get_to<dev::bigint>(resp.add_liquidity);
    if (j.find("remove_liquidity") != j.end() && !j.at("remove_liquidity").is_null())
        j.at("remove_liquidity").get_to<dev::bigint>(resp.remove_liquidity);
    if (j.find("edit_candidate_commission") != j.end() && !j.at("edit_candidate_commission").is_null())
        j.at("edit_candidate_commission").get_to<dev::bigint>(resp.edit_candidate_commission);
    if (j.find("mint_token") != j.end() && !j.at("mint_token").is_null())
        j.at("mint_token").get_to<dev::bigint>(resp.mint_token);
    if (j.find("burn_token") != j.end() && !j.at("burn_token").is_null())
        j.at("burn_token").get_to<dev::bigint>(resp.burn_token);
    if (j.find("vote_commission") != j.end() && !j.at("vote_commission").is_null())
        j.at("vote_commission").get_to<dev::bigint>(resp.vote_commission);
    if (j.find("vote_update") != j.end() && !j.at("vote_update").is_null())
        j.at("vote_update").get_to<dev::bigint>(resp.vote_update);
}
void ::minter::gate::to_json(nlohmann::json& j, const ::minter::gate::price_commissions& resp) {
    j = nlohmann::json{
        {"error", resp.error},
        {"coin", resp.coin},
        {"payload_byte", resp.payload_byte},
        {"send", resp.send},
        {"buy_bancor", resp.buy_bancor},
        {"sell_bancor", resp.sell_bancor},
        {"sell_all_bancor", resp.sell_all_bancor},
        {"buy_pool_base", resp.buy_pool_base},
        {"sell_pool_base", resp.sell_pool_base},
        {"sell_all_pool_base", resp.sell_all_pool_base},
        {"buy_pool_delta", resp.buy_pool_delta},
        {"sell_pool_delta", resp.sell_pool_delta},
        {"sell_all_pool_delta", resp.sell_all_pool_delta},
        {"create_ticker3", resp.create_ticker3},
        {"create_ticker4", resp.create_ticker4},
        {"create_ticker5", resp.create_ticker5},
        {"create_ticker6", resp.create_ticker6},
        {"create_ticker7_10", resp.create_ticker7_10},
        {"create_coin", resp.create_coin},
        {"create_token", resp.create_token},
        {"recreate_coin", resp.recreate_coin},
        {"recreate_token", resp.recreate_token},
        {"declare_candidacy", resp.declare_candidacy},
        {"delegate", resp.delegate},
        {"unbond", resp.unbond},
        {"redeem_check", resp.redeem_check},
        {"set_candidate_on", resp.set_candidate_on},
        {"set_candidate_off", resp.set_candidate_off},
        {"create_multisig", resp.create_multisig},
        {"multisend_base", resp.multisend_base},
        {"multisend_delta", resp.multisend_delta},
        {"edit_candidate", resp.edit_candidate},
        {"set_halt_block", resp.set_halt_block},
        {"edit_ticker_owner", resp.edit_ticker_owner},
        {"edit_multisig", resp.edit_multisig},
        {"edit_candidate_public_key", resp.edit_candidate_public_key},
        {"create_swap_pool", resp.create_swap_pool},
        {"add_liquidity", resp.add_liquidity},
        {"remove_liquidity", resp.remove_liquidity},
        {"edit_candidate_commission", resp.edit_candidate_commission},
        {"mint_token", resp.mint_token},
        {"burn_token", resp.burn_token},
        {"vote_commission", resp.vote_commission},
        {"vote_update", resp.vote_update},
    };
}
void ::minter::gate::from_json(const nlohmann::json& j, ::minter::gate::commission_value& resp) {
    if (j.find("error") != j.end() && !j.at("error").is_null())
        j.at("error").get_to<minter::gate::error_result>(resp.error);
    if (j.find("commission") != j.end() && !j.at("commission").is_null())
        j.at("commission").get_to<dev::bigint>(resp.value);
}
void ::minter::gate::to_json(nlohmann::json& j, const ::minter::gate::commission_value& resp) {
    j = nlohmann::json{
        {"error", resp.error},
        {"commission", resp.value},
    };
}
void ::minter::gate::from_json(const nlohmann::json& j, ::minter::gate::exchange_sell_value& resp) {
    if (j.find("error") != j.end() && !j.at("error").is_null())
        j.at("error").get_to<minter::gate::error_result>(resp.error);
    if (j.find("will_get") != j.end() && !j.at("will_get").is_null())
        j.at("will_get").get_to<dev::bigint>(resp.will_get);
    if (j.find("commission") != j.end() && !j.at("commission").is_null())
        j.at("commission").get_to<dev::bigint>(resp.commission);
    if (j.find("swap_from") != j.end() && !j.at("swap_from").is_null())
        j.at("swap_from").get_to<estimate_swap_from>(resp.swap_from);
}
void ::minter::gate::to_json(nlohmann::json& j, const ::minter::gate::exchange_sell_value& resp) {
    j = nlohmann::json{
        {"error", resp.error},
        {"will_get", resp.will_get},
        {"commission", resp.commission},
        {"swap_from", resp.swap_from},
    };
}
void ::minter::gate::from_json(const nlohmann::json& j, ::minter::gate::exchange_buy_value& resp) {
    if (j.find("error") != j.end() && !j.at("error").is_null())
        j.at("error").get_to<minter::gate::error_result>(resp.error);
    if (j.find("will_pay") != j.end() && !j.at("will_pay").is_null())
        j.at("will_pay").get_to<dev::bigint>(resp.will_pay);
    if (j.find("commission") != j.end() && !j.at("commission").is_null())
        j.at("commission").get_to<dev::bigint>(resp.commission);
    if (j.find("swap_from") != j.end() && !j.at("swap_from").is_null())
        j.at("swap_from").get_to<estimate_swap_from>(resp.swap_from);
}
void ::minter::gate::to_json(nlohmann::json& j, const ::minter::gate::exchange_buy_value& resp) {
    j = nlohmann::json{
        {"error", resp.error},
        {"will_pay", resp.will_pay},
        {"commission", resp.commission},
        {"swap_from", resp.swap_from},
    };
}
void ::minter::gate::from_json(const nlohmann::json& j, ::minter::gate::tx_count_value& resp) {
    if (j.find("error") != j.end() && !j.at("error").is_null())
        j.at("error").get_to<minter::gate::error_result>(resp.error);
    if (j.find("nonce") != j.end() && !j.at("nonce").is_null())
        j.at("nonce").get_to<dev::bigint>(resp.count);
}
void ::minter::gate::to_json(nlohmann::json& j, const ::minter::gate::tx_count_value& resp) {
    j = nlohmann::json{
        {"error", resp.error},
        {"nonce", resp.count},
    };
}
void ::minter::gate::from_json(const nlohmann::json& j, ::minter::gate::send_tx_data& resp) {
    if (j.find("nonce") != j.end() && !j.at("nonce").is_null())
        j.at("nonce").get_to<dev::bigint>(resp.nonce);
    if (j.find("hash") != j.end() && !j.at("hash").is_null())
        j.at("hash").get_to<minter::hash_t>(resp.hash);
    if (j.find("raw_tx") != j.end() && !j.at("raw_tx").is_null())
        j.at("raw_tx").get_to<std::string>(resp.raw_tx);
    if (j.find("height") != j.end() && !j.at("height").is_null())
        j.at("height").get_to<dev::bigint>(resp.height);
    if (j.find("from") != j.end() && !j.at("from").is_null())
        j.at("from").get_to<minter::address_t>(resp.from);
    if (j.find("type") != j.end() && !j.at("type").is_null())
        j.at("type").get_to<std::string>(resp.type);
    if (j.find("gas_coin") != j.end() && !j.at("gas_coin").is_null())
        j.at("gas_coin").get_to<minter::explorer::coin_item_base>(resp.gas_coin);
    if (j.find("tags") != j.end() && !j.at("tags").is_null())
        j.at("tags").get_to<std::unordered_map<std::string, std::string>>(resp.tags);
}
void ::minter::gate::to_json(nlohmann::json& j, const ::minter::gate::send_tx_data& resp) {
    j = nlohmann::json{
        {"nonce", resp.nonce},
        {"hash", resp.hash},
        {"raw_tx", resp.raw_tx},
        {"height", resp.height},
        {"from", resp.from},
        {"type", resp.type},
        {"gas_coin", resp.gas_coin},
        {"tags", resp.tags},
    };
}
void ::minter::gate::from_json(const nlohmann::json& j, ::minter::gate::tx_send_result& resp) {
    if (j.find("error") != j.end() && !j.at("error").is_null())
        j.at("error").get_to<minter::gate::error_result>(resp.error);
    if (j.find("hash") != j.end() && !j.at("hash").is_null())
        j.at("hash").get_to<minter::hash_t>(resp.hash);
    if (j.find("transaction") != j.end() && !j.at("transaction").is_null())
        j.at("transaction").get_to<send_tx_data>(resp.transaction);
}
void ::minter::gate::to_json(nlohmann::json& j, const ::minter::gate::tx_send_result& resp) {
    j = nlohmann::json{
        {"error", resp.error},
        {"hash", resp.hash},
        {"transaction", resp.transaction},
    };
}