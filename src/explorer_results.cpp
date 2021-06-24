/*!
 * minter-api.
 * results.cpp
 *
 * \date 2019
 * \author Eduard Maximovich (edward.vstock@gmail.com)
 * \link   https://github.com/edwardstock
 */

#include "minter/api/explorer/explorer_results.h"

::nlohmann::json minter::explorer::transaction_item::_data_encode(nlohmann::json&,
                                                                  const ::minter::explorer::transaction_item&) {
    return nlohmann::json();
}
void minter::explorer::transaction_item::_data_decode(const nlohmann::json& j,
                                                      ::minter::explorer::transaction_item& resp) {

    using namespace minter;

    switch (resp.type) {
    case tx_type_val::send_coin: {
        tx_send_result result = j.at("data").get<tx_send_result>();
        resp.data = std::make_shared<tx_send_result>(std::move(result));
        break;
    }
    case tx_type_val::sell_coin:
    case tx_type_val::sell_all_coins:
    case tx_type_val::buy_coin: {
        tx_convert_result result = j.at("data").get<tx_convert_result>();
        resp.data = std::make_shared<tx_convert_result>(std::move(result));
        break;
    }
    case tx_type_val::create_coin: {
        tx_create_coin_result result = j.at("data").get<tx_create_coin_result>();
        resp.data = std::make_shared<tx_create_coin_result>(std::move(result));
        break;
    }
    case tx_type_val::declare_candidacy: {
        tx_declare_candidacy_result result = j.at("data").get<tx_declare_candidacy_result>();
        resp.data = std::make_shared<tx_declare_candidacy_result>(std::move(result));
        break;
    }
    case tx_type_val::delegate:
    case tx_type_val::unbond: {
        tx_delegate_unbond_result result = j.at("data").get<tx_delegate_unbond_result>();
        resp.data = std::make_shared<tx_delegate_unbond_result>(std::move(result));
        break;
    }
    case tx_type_val::redeem_check: {
        tx_redeem_check_result result = j.at("data").get<tx_redeem_check_result>();
        resp.data = std::make_shared<tx_redeem_check_result>(std::move(result));
        break;
    }
    case tx_type_val::set_candidate_on:
    case tx_type_val::set_candidate_off: {
        tx_set_candidate_on_off_result result = j.at("data").get<tx_set_candidate_on_off_result>();
        resp.data = std::make_shared<tx_set_candidate_on_off_result>(std::move(result));
        break;
    }
    case tx_type_val::create_multisig: {
        tx_create_multisig_result result = j.at("data").get<tx_create_multisig_result>();
        resp.data = std::make_shared<tx_create_multisig_result>(std::move(result));
        break;
    }
    case tx_type_val::multisend: {
        tx_multisend_result result = j.at("data").get<tx_multisend_result>();
        resp.data = std::make_shared<tx_multisend_result>(std::move(result));
        break;
    }
    case tx_type_val::edit_candidate: {
        tx_edit_candidate_result result = j.at("data").get<tx_edit_candidate_result>();
        resp.data = std::make_shared<tx_edit_candidate_result>(std::move(result));
        break;
    }
    /// \since minter 1.2
    case tx_type_val::set_halt_block: {
        tx_set_halt_block_result result = j.at("data").get<tx_set_halt_block_result>();
        resp.data = std::make_shared<tx_set_halt_block_result>(std::move(result));
        break;
    }
    case tx_type_val::recreate_coin: {
        tx_recreate_coin_result result = j.at("data").get<tx_recreate_coin_result>();
        resp.data = std::make_shared<tx_recreate_coin_result>(std::move(result));
        break;
    }
    case tx_type_val::edit_coin_owner: {
        tx_edit_coin_owner_result result = j.at("data").get<tx_edit_coin_owner_result>();
        resp.data = std::make_shared<tx_edit_coin_owner_result>(std::move(result));
        break;
    }
    case tx_type_val::edit_multisig: {
        tx_edit_multisig_result result = j.at("data").get<tx_edit_multisig_result>();
        resp.data = std::make_shared<tx_edit_multisig_result>(std::move(result));
        break;
    }
    case tx_type_val::edit_candidate_public_key: {
        tx_edit_candidate_pubkey_result result = j.at("data").get<tx_edit_candidate_pubkey_result>();
        resp.data = std::make_shared<tx_edit_candidate_pubkey_result>(std::move(result));
        break;
    }
    /// \since minter 2.0
    case tx_type_val::add_liquidity: {
        tx_add_liquidity_result result = j.at("data").get<tx_add_liquidity_result>();
        resp.data = std::make_shared<tx_add_liquidity_result>(std::move(result));
        break;
    }
    case tx_type_val::remove_liquidity: {
        tx_remove_liquidity_result result = j.at("data").get<tx_remove_liquidity_result>();
        resp.data = std::make_shared<tx_remove_liquidity_result>(std::move(result));
        break;
    }
    case tx_type_val::sell_swap_pool: {
        tx_sell_swap_pool_result result = j.at("data").get<tx_sell_swap_pool_result>();
        resp.data = std::make_shared<tx_sell_swap_pool_result>(std::move(result));
        break;
    }
    case tx_type_val::buy_swap_pool: {
        tx_buy_swap_pool_result result = j.at("data").get<tx_buy_swap_pool_result>();
        resp.data = std::make_shared<tx_buy_swap_pool_result>(std::move(result));
        break;
    }
    case tx_type_val::sell_all_swap_pool: {
        tx_sell_all_swap_pool_result result = j.at("data").get<tx_sell_all_swap_pool_result>();
        resp.data = std::make_shared<tx_sell_all_swap_pool_result>(std::move(result));
        break;
    }
    case tx_type_val::edit_candidate_commission: {
        tx_edit_candidate_commission_result result = j.at("data").get<tx_edit_candidate_commission_result>();
        resp.data = std::make_shared<tx_edit_candidate_commission_result>(std::move(result));
        break;
    }
    case tx_type_val::mint_token: {
        tx_mint_token_result result = j.at("data").get<tx_mint_token_result>();
        resp.data = std::make_shared<tx_mint_token_result>(std::move(result));
        break;
    }
    case tx_type_val::burn_token: {
        tx_burn_token_result result = j.at("data").get<tx_burn_token_result>();
        resp.data = std::make_shared<tx_burn_token_result>(std::move(result));
        break;
    }
    case tx_type_val::create_token: {
        tx_create_token_result result = j.at("data").get<tx_create_token_result>();
        resp.data = std::make_shared<tx_create_token_result>(std::move(result));
        break;
    }
    case tx_type_val::recreate_token: {
        tx_recreate_token_result result = j.at("data").get<tx_recreate_token_result>();
        resp.data = std::make_shared<tx_recreate_token_result>(std::move(result));
        break;
    }
    case tx_type_val::vote_commission: {
        tx_vote_commission_result result = j.at("data").get<tx_vote_commission_result>();
        resp.data = std::make_shared<tx_vote_commission_result>(std::move(result));
        break;
    }
    case tx_type_val::vote_update: {
        tx_vote_update_result result = j.at("data").get<tx_vote_update_result>();
        resp.data = std::make_shared<tx_vote_update_result>(std::move(result));
        break;
    }
    case tx_type_val::create_swap_pool: {
        tx_create_swap_pool_result result = j.at("data").get<tx_create_swap_pool_result>();
        resp.data = std::make_shared<tx_create_swap_pool_result>(std::move(result));
        break;
    }
    default:
        // nothing yet
        break;
    }
}
