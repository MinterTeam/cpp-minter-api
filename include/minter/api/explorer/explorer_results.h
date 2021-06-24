#ifndef GEN_EXPLORER_RESULTS
#define GEN_EXPLORER_RESULTS

// AUTOGENERATED header. DO NOT modify manually.
//
#include "minter/api/explorer/base.h"
#include "minter/api/gate/base.h"

#include <minter/address.h>
#include <minter/hash.h>
#include <minter/minter_tx_config.h>
#include <minter/public_key.h>
#include <minter/tx/tx_type.h>
#include <nlohmann/json.hpp>
#include <string>
#include <vector>

namespace minter {
namespace explorer {

struct transaction_item {
    dev::bigint txn;
    minter::hash_t hash;
    dev::bigint nonce;
    dev::bigint height;
    std::string timestamp;
    minter::tx_type_val type;
    std::string payload;
    minter::address_t from;
    std::shared_ptr<minter::explorer::tx_result> data;
    dev::bigint gas;
    dev::bigint gas_price;
    minter::explorer::coin_item_base gas_coin;
    dev::bigdec18 fee;
    static ::nlohmann::json _data_encode(nlohmann::json& j, const ::minter::explorer::transaction_item& resp);
    static void _data_decode(const nlohmann::json& j, ::minter::explorer::transaction_item& resp);
};
struct coin_item : public minter::explorer::coin_item_base {
    std::string name;
    uint32_t crr;
    dev::bigdec18 reserve_valance;
    dev::bigdec18 max_supply;
    minter::address_t owner_address;
    dev::bigdec18 volume;
    bool mintable;
    bool burnable;
};
struct tx_send_result : public minter::explorer::tx_result {
    minter::address_t to;
    minter::explorer::coin_item_base coin;
    dev::bigdec18 value;
};
struct tx_create_coin_result : public minter::explorer::tx_result {
    std::string name;
    std::string symbol;
    dev::bigdec18 initial_amount;
    dev::bigdec18 initial_reserve;
    uint32_t crr;
};
struct tx_convert_result : public minter::explorer::tx_result {
    minter::explorer::coin_item_base coin_to_sell;
    minter::explorer::coin_item_base coin_to_buy;
    dev::bigdec18 value_to_buy;
    dev::bigdec18 value_to_sell;
    dev::bigdec18 maximum_value_to_sell;
    dev::bigdec18 minimum_value_to_buy;
};
struct tx_declare_candidacy_result : public minter::explorer::tx_result {
    minter::address_t address;
    minter::pubkey_t pub_key;
    uint32_t commission;
    minter::explorer::coin_item_base coin;
    dev::bigdec18 stake;
};
struct tx_set_candidate_on_off_result : public minter::explorer::tx_result {
    minter::pubkey_t pub_key;
};
struct tx_delegate_unbond_result : public minter::explorer::tx_result {
    minter::pubkey_t pub_key;
    minter::explorer::coin_item_base coin;
    dev::bigdec18 stake;
    dev::bigdec18 value;
};
struct tx_check_data_result {
    minter::explorer::coin_item_base coin;
    minter::explorer::coin_item_base gas_coin;
    dev::bigint nonce;
    dev::bigdec18 value;
    minter::address_t sender;
    dev::bigint due_block;
};
struct tx_redeem_check_result : public minter::explorer::tx_result {
    std::string raw_check;
    std::string proof;
    dev::bigdec18 stake;
    dev::bigdec18 value;
    tx_check_data_result check;
};
struct tx_create_multisig_result : public minter::explorer::tx_result {
    dev::bigint threshold;
    std::vector<dev::bigint> weights;
    std::vector<minter::address_t> addresses;
};
struct tx_multisend_result : public minter::explorer::tx_result {
    std::vector<tx_send_result> items;
};
struct tx_edit_candidate_result : public minter::explorer::tx_result {
    minter::address_t reward_address;
    minter::address_t owner_address;
    minter::pubkey_t pub_key;
};
struct tx_edit_candidate_pubkey_result : public minter::explorer::tx_result {
    minter::pubkey_t pub_key;
    minter::pubkey_t new_pub_key;
};
struct tx_set_halt_block_result : public minter::explorer::tx_result {
    minter::pubkey_t pub_key;
    dev::bigint height;
};
struct tx_edit_multisig_result : public minter::explorer::tx_create_multisig_result {
};
struct tx_price_vote_result : public minter::explorer::tx_result {
    dev::bigint price;
};
struct tx_recreate_coin_result : public minter::explorer::tx_create_coin_result {
};
struct tx_add_liquidity_result : public minter::explorer::tx_result {
    minter::explorer::coin_item_base coin0;
    minter::explorer::coin_item_base coin1;
    minter::explorer::coin_item_base pool_token;
    dev::bigdec18 volume0;
    dev::bigdec18 volume1;
    dev::bigdec18 maximum_volume1;
    dev::bigdec18 liquidity;
};
struct tx_remove_liquidity_result : public minter::explorer::tx_result {
    minter::explorer::coin_item_base coin0;
    minter::explorer::coin_item_base coin1;
    minter::explorer::coin_item_base pool_token;
    dev::bigdec18 volume0;
    dev::bigdec18 volume1;
    dev::bigdec18 minimum_volume0;
    dev::bigdec18 minimum_volume1;
    dev::bigdec18 liquidity;
};
struct tx_convert_swap_pool_result : public minter::explorer::tx_result {
    std::vector<minter::explorer::coin_item_base> coins;
    coin_item_base coin_to_buy;
    coin_item_base coin_to_sell;
    dev::bigdec18 value_to_sell;
    dev::bigdec18 value_to_buy;
    dev::bigdec18 minimum_value_to_buy;
    dev::bigdec18 maximum_value_to_sell;
};
struct tx_sell_swap_pool_result : public minter::explorer::tx_convert_swap_pool_result {
};
struct tx_sell_all_swap_pool_result : public minter::explorer::tx_convert_swap_pool_result {
};
struct tx_buy_swap_pool_result : public minter::explorer::tx_convert_swap_pool_result {
};
struct tx_create_swap_pool_result : public minter::explorer::tx_result {
    minter::explorer::coin_item_base coin0;
    minter::explorer::coin_item_base coin1;
    minter::explorer::coin_item_base pool_token;
    dev::bigdec18 volume0;
    dev::bigdec18 volume1;
    dev::bigdec18 liquidity;
};
struct tx_edit_candidate_commission_result : public minter::explorer::tx_result {
    minter::pubkey_t pub_key;
    uint32_t commission;
};
struct tx_mint_token_result : public minter::explorer::tx_result {
    minter::explorer::coin_item_base coin;
    dev::bigdec18 value;
};
struct tx_burn_token_result : public minter::explorer::tx_result {
    minter::explorer::coin_item_base coin;
    dev::bigdec18 value;
};
struct tx_create_token_result : public minter::explorer::tx_result {
    std::string symbol;
    dev::bigdec18 initial_amount;
    dev::bigdec18 max_supply;
    bool mintable;
    bool burnable;
};
struct tx_recreate_token_result : public minter::explorer::tx_result {
    std::string symbol;
    dev::bigdec18 initial_amount;
    dev::bigdec18 max_supply;
    bool mintable;
    bool burnable;
};
struct tx_edit_coin_owner_result : public minter::explorer::tx_result {
    std::string symbol;
    minter::address_t new_owner;
};
struct tx_vote_commission_result : public minter::explorer::tx_result {
    minter::pubkey_t pub_key;
    dev::bigint height;
    minter::explorer::coin_item_base coin;
    dev::bigint payload_byte;
    dev::bigint send;
    dev::bigint buy_bancor;
    dev::bigint sell_bancor;
    dev::bigint sell_all_bancor;
    dev::bigint buy_pool_base;
    dev::bigint sell_pool_base;
    dev::bigint sell_all_pool_base;
    dev::bigint buy_pool_delta;
    dev::bigint sell_pool_delta;
    dev::bigint sell_all_pool_delta;
    dev::bigint create_ticker3;
    dev::bigint create_ticker4;
    dev::bigint create_ticker5;
    dev::bigint create_ticker6;
    dev::bigint create_ticker7_10;
    dev::bigint create_coin;
    dev::bigint create_token;
    dev::bigint recreate_coin;
    dev::bigint recreate_token;
    dev::bigint declare_candidacy;
    dev::bigint delegate;
    dev::bigint unbond;
    dev::bigint redeem_check;
    dev::bigint set_candidate_on;
    dev::bigint set_candidate_off;
    dev::bigint create_multisig;
    dev::bigint multisend_base;
    dev::bigint multisend_delta;
    dev::bigint edit_candidate;
    dev::bigint set_halt_block;
    dev::bigint edit_ticker_owner;
    dev::bigint edit_multisig;
    dev::bigint edit_candidate_public_key;
    dev::bigint create_swap_pool;
    dev::bigint add_liquidity;
    dev::bigint remove_liquidity;
    dev::bigint edit_candidate_commission;
    dev::bigint mint_token;
    dev::bigint burn_token;
    dev::bigint vote_commission;
    dev::bigint vote_update;
};
struct tx_vote_update_result : public minter::explorer::tx_result {
    minter::pubkey_t pub_key;
    dev::bigint height;
    std::string version;
};
struct validator_meta {
    std::string name;
    std::string description;
    std::string site_url;
    std::string icon_url;
};
struct validator_item {
    minter::pubkey_t pub_key;
    int status;
    dev::bigdec18 stake;
    dev::bigdec18 part;
    validator_meta meta;
    uint32_t commission;
};
struct balance_item {
    minter::explorer::coin_item_base coin;
    dev::bigdec18 amount;
    dev::bigdec18 bip_amount;
};
struct balance_items {
    minter::address_t address;
    std::vector<balance_item> balances;
};
struct delegated_item {
    minter::pubkey_t pub_key;
    minter::explorer::coin_item_base coin;
    dev::bigdec18 amount;
    dev::bigdec18 bip_amount;
    bool is_waitlisted;
    minter::explorer::validator_item validator;
};
struct reward_item {
    uint64_t block;
    std::string role;
    dev::bigdec18 amount;
    minter::address_t address;
    minter::pubkey_t validator;
    std::string timestamp;
};
struct block_validator_item {
    minter::pubkey_t pub_key;
    bool is_signed;
    validator_meta meta;
};
struct block_info_item {
    dev::bigint height;
    size_t size;
    size_t tx_count;
    std::string block_time;
    std::string timestamp;
    dev::bigdec18 reward;
    minter::hash_t hash;
    std::vector<block_validator_item> validators;
};
struct delegator_item {
    minter::explorer::coin_item_base coin;
    minter::address_t address;
    dev::bigdec18 value;
    dev::bigdec18 bip_value;
};
struct validator_detailed_item {
    minter::pubkey_t pub_key;
    int status;
    dev::bigdec18 stake;
    dev::bigdec18 part;
    validator_meta meta;
    uint64_t delegator_count;
    std::vector<delegator_item> delegator_list;
};
struct net_status {
    double avg_block_time;
    double bip_price_change;
    double bip_price_usd;
    dev::bigint latest_block_height;
    double market_cap;
    dev::bigint total_txn;
    double tx_per_second;
};
struct net_status_page {
    uint64_t active_candidates;
    uint64_t active_validators;
    dev::bigdec18 avg_tx_commission;
    dev::bigint bip_emission;
    dev::bigdec18 block_speed_24h;
    uint64_t blocks_count;
    uint64_t custom_coins_count;
    uint64_t delegators_count;
    dev::bigdec18 custom_coins_sum;
    dev::bigdec18 free_float_bip;
    uint64_t non_zero_addresses_count;
    uint64_t pools_count;
    std::string status;
    dev::bigdec18 total_commission;
    dev::bigdec18 total_delegated_bip;
    dev::bigint tx_24h_count;
    dev::bigdec18 tx_per_second;
    dev::bigint total_txn;
    double uptime;
};
struct pool {
    minter::explorer::coin_item_base coin0;
    minter::explorer::coin_item_base coin1;
    dev::bigdec18 amount0;
    dev::bigdec18 amount1;
    dev::bigdec18 liquidity;
    dev::bigdec18 liquidity_bip;
};
struct pool_provider {
    minter::address_t address;
    minter::explorer::coin_item_base coin0;
    minter::explorer::coin_item_base coin1;
    minter::explorer::coin_item_base token;
    dev::bigdec18 amount0;
    dev::bigdec18 amount1;
    dev::bigdec18 liquidity;
    dev::bigdec18 liquidity_share;
    dev::bigdec18 liquidity_bip;
};
struct pool_route : public minter::gate::result {
    minter::gate::estimate_swap_from swap_type;
    dev::bigdec18 amount_in;
    dev::bigdec18 amount_out;
    std::vector<minter::explorer::coin_item_base> coins;
};
MINTER_TX_API void from_json(const nlohmann::json& j, ::minter::explorer::transaction_item& resp);
MINTER_TX_API void to_json(nlohmann::json& j, const ::minter::explorer::transaction_item& resp);
MINTER_TX_API void from_json(const nlohmann::json& j, ::minter::explorer::coin_item& resp);
MINTER_TX_API void to_json(nlohmann::json& j, const ::minter::explorer::coin_item& resp);
MINTER_TX_API void from_json(const nlohmann::json& j, ::minter::explorer::tx_send_result& resp);
MINTER_TX_API void to_json(nlohmann::json& j, const ::minter::explorer::tx_send_result& resp);
MINTER_TX_API void from_json(const nlohmann::json& j, ::minter::explorer::tx_create_coin_result& resp);
MINTER_TX_API void to_json(nlohmann::json& j, const ::minter::explorer::tx_create_coin_result& resp);
MINTER_TX_API void from_json(const nlohmann::json& j, ::minter::explorer::tx_convert_result& resp);
MINTER_TX_API void to_json(nlohmann::json& j, const ::minter::explorer::tx_convert_result& resp);
MINTER_TX_API void from_json(const nlohmann::json& j, ::minter::explorer::tx_declare_candidacy_result& resp);
MINTER_TX_API void to_json(nlohmann::json& j, const ::minter::explorer::tx_declare_candidacy_result& resp);
MINTER_TX_API void from_json(const nlohmann::json& j, ::minter::explorer::tx_set_candidate_on_off_result& resp);
MINTER_TX_API void to_json(nlohmann::json& j, const ::minter::explorer::tx_set_candidate_on_off_result& resp);
MINTER_TX_API void from_json(const nlohmann::json& j, ::minter::explorer::tx_delegate_unbond_result& resp);
MINTER_TX_API void to_json(nlohmann::json& j, const ::minter::explorer::tx_delegate_unbond_result& resp);
MINTER_TX_API void from_json(const nlohmann::json& j, ::minter::explorer::tx_check_data_result& resp);
MINTER_TX_API void to_json(nlohmann::json& j, const ::minter::explorer::tx_check_data_result& resp);
MINTER_TX_API void from_json(const nlohmann::json& j, ::minter::explorer::tx_redeem_check_result& resp);
MINTER_TX_API void to_json(nlohmann::json& j, const ::minter::explorer::tx_redeem_check_result& resp);
MINTER_TX_API void from_json(const nlohmann::json& j, ::minter::explorer::tx_create_multisig_result& resp);
MINTER_TX_API void to_json(nlohmann::json& j, const ::minter::explorer::tx_create_multisig_result& resp);
MINTER_TX_API void from_json(const nlohmann::json& j, ::minter::explorer::tx_multisend_result& resp);
MINTER_TX_API void to_json(nlohmann::json& j, const ::minter::explorer::tx_multisend_result& resp);
MINTER_TX_API void from_json(const nlohmann::json& j, ::minter::explorer::tx_edit_candidate_result& resp);
MINTER_TX_API void to_json(nlohmann::json& j, const ::minter::explorer::tx_edit_candidate_result& resp);
MINTER_TX_API void from_json(const nlohmann::json& j, ::minter::explorer::tx_edit_candidate_pubkey_result& resp);
MINTER_TX_API void to_json(nlohmann::json& j, const ::minter::explorer::tx_edit_candidate_pubkey_result& resp);
MINTER_TX_API void from_json(const nlohmann::json& j, ::minter::explorer::tx_set_halt_block_result& resp);
MINTER_TX_API void to_json(nlohmann::json& j, const ::minter::explorer::tx_set_halt_block_result& resp);
MINTER_TX_API void from_json(const nlohmann::json& j, ::minter::explorer::tx_edit_multisig_result& resp);
MINTER_TX_API void to_json(nlohmann::json& j, const ::minter::explorer::tx_edit_multisig_result& resp);
MINTER_TX_API void from_json(const nlohmann::json& j, ::minter::explorer::tx_price_vote_result& resp);
MINTER_TX_API void to_json(nlohmann::json& j, const ::minter::explorer::tx_price_vote_result& resp);
MINTER_TX_API void from_json(const nlohmann::json& j, ::minter::explorer::tx_recreate_coin_result& resp);
MINTER_TX_API void to_json(nlohmann::json& j, const ::minter::explorer::tx_recreate_coin_result& resp);
MINTER_TX_API void from_json(const nlohmann::json& j, ::minter::explorer::tx_add_liquidity_result& resp);
MINTER_TX_API void to_json(nlohmann::json& j, const ::minter::explorer::tx_add_liquidity_result& resp);
MINTER_TX_API void from_json(const nlohmann::json& j, ::minter::explorer::tx_remove_liquidity_result& resp);
MINTER_TX_API void to_json(nlohmann::json& j, const ::minter::explorer::tx_remove_liquidity_result& resp);
MINTER_TX_API void from_json(const nlohmann::json& j, ::minter::explorer::tx_convert_swap_pool_result& resp);
MINTER_TX_API void to_json(nlohmann::json& j, const ::minter::explorer::tx_convert_swap_pool_result& resp);
MINTER_TX_API void from_json(const nlohmann::json& j, ::minter::explorer::tx_sell_swap_pool_result& resp);
MINTER_TX_API void to_json(nlohmann::json& j, const ::minter::explorer::tx_sell_swap_pool_result& resp);
MINTER_TX_API void from_json(const nlohmann::json& j, ::minter::explorer::tx_sell_all_swap_pool_result& resp);
MINTER_TX_API void to_json(nlohmann::json& j, const ::minter::explorer::tx_sell_all_swap_pool_result& resp);
MINTER_TX_API void from_json(const nlohmann::json& j, ::minter::explorer::tx_buy_swap_pool_result& resp);
MINTER_TX_API void to_json(nlohmann::json& j, const ::minter::explorer::tx_buy_swap_pool_result& resp);
MINTER_TX_API void from_json(const nlohmann::json& j, ::minter::explorer::tx_create_swap_pool_result& resp);
MINTER_TX_API void to_json(nlohmann::json& j, const ::minter::explorer::tx_create_swap_pool_result& resp);
MINTER_TX_API void from_json(const nlohmann::json& j, ::minter::explorer::tx_edit_candidate_commission_result& resp);
MINTER_TX_API void to_json(nlohmann::json& j, const ::minter::explorer::tx_edit_candidate_commission_result& resp);
MINTER_TX_API void from_json(const nlohmann::json& j, ::minter::explorer::tx_mint_token_result& resp);
MINTER_TX_API void to_json(nlohmann::json& j, const ::minter::explorer::tx_mint_token_result& resp);
MINTER_TX_API void from_json(const nlohmann::json& j, ::minter::explorer::tx_burn_token_result& resp);
MINTER_TX_API void to_json(nlohmann::json& j, const ::minter::explorer::tx_burn_token_result& resp);
MINTER_TX_API void from_json(const nlohmann::json& j, ::minter::explorer::tx_create_token_result& resp);
MINTER_TX_API void to_json(nlohmann::json& j, const ::minter::explorer::tx_create_token_result& resp);
MINTER_TX_API void from_json(const nlohmann::json& j, ::minter::explorer::tx_recreate_token_result& resp);
MINTER_TX_API void to_json(nlohmann::json& j, const ::minter::explorer::tx_recreate_token_result& resp);
MINTER_TX_API void from_json(const nlohmann::json& j, ::minter::explorer::tx_edit_coin_owner_result& resp);
MINTER_TX_API void to_json(nlohmann::json& j, const ::minter::explorer::tx_edit_coin_owner_result& resp);
MINTER_TX_API void from_json(const nlohmann::json& j, ::minter::explorer::tx_vote_commission_result& resp);
MINTER_TX_API void to_json(nlohmann::json& j, const ::minter::explorer::tx_vote_commission_result& resp);
MINTER_TX_API void from_json(const nlohmann::json& j, ::minter::explorer::tx_vote_update_result& resp);
MINTER_TX_API void to_json(nlohmann::json& j, const ::minter::explorer::tx_vote_update_result& resp);
MINTER_TX_API void from_json(const nlohmann::json& j, ::minter::explorer::validator_meta& resp);
MINTER_TX_API void to_json(nlohmann::json& j, const ::minter::explorer::validator_meta& resp);
MINTER_TX_API void from_json(const nlohmann::json& j, ::minter::explorer::validator_item& resp);
MINTER_TX_API void to_json(nlohmann::json& j, const ::minter::explorer::validator_item& resp);
MINTER_TX_API void from_json(const nlohmann::json& j, ::minter::explorer::balance_item& resp);
MINTER_TX_API void to_json(nlohmann::json& j, const ::minter::explorer::balance_item& resp);
MINTER_TX_API void from_json(const nlohmann::json& j, ::minter::explorer::balance_items& resp);
MINTER_TX_API void to_json(nlohmann::json& j, const ::minter::explorer::balance_items& resp);
MINTER_TX_API void from_json(const nlohmann::json& j, ::minter::explorer::delegated_item& resp);
MINTER_TX_API void to_json(nlohmann::json& j, const ::minter::explorer::delegated_item& resp);
MINTER_TX_API void from_json(const nlohmann::json& j, ::minter::explorer::reward_item& resp);
MINTER_TX_API void to_json(nlohmann::json& j, const ::minter::explorer::reward_item& resp);
MINTER_TX_API void from_json(const nlohmann::json& j, ::minter::explorer::block_validator_item& resp);
MINTER_TX_API void to_json(nlohmann::json& j, const ::minter::explorer::block_validator_item& resp);
MINTER_TX_API void from_json(const nlohmann::json& j, ::minter::explorer::block_info_item& resp);
MINTER_TX_API void to_json(nlohmann::json& j, const ::minter::explorer::block_info_item& resp);
MINTER_TX_API void from_json(const nlohmann::json& j, ::minter::explorer::delegator_item& resp);
MINTER_TX_API void to_json(nlohmann::json& j, const ::minter::explorer::delegator_item& resp);
MINTER_TX_API void from_json(const nlohmann::json& j, ::minter::explorer::validator_detailed_item& resp);
MINTER_TX_API void to_json(nlohmann::json& j, const ::minter::explorer::validator_detailed_item& resp);
MINTER_TX_API void from_json(const nlohmann::json& j, ::minter::explorer::net_status& resp);
MINTER_TX_API void to_json(nlohmann::json& j, const ::minter::explorer::net_status& resp);
MINTER_TX_API void from_json(const nlohmann::json& j, ::minter::explorer::net_status_page& resp);
MINTER_TX_API void to_json(nlohmann::json& j, const ::minter::explorer::net_status_page& resp);
MINTER_TX_API void from_json(const nlohmann::json& j, ::minter::explorer::pool& resp);
MINTER_TX_API void to_json(nlohmann::json& j, const ::minter::explorer::pool& resp);
MINTER_TX_API void from_json(const nlohmann::json& j, ::minter::explorer::pool_provider& resp);
MINTER_TX_API void to_json(nlohmann::json& j, const ::minter::explorer::pool_provider& resp);
MINTER_TX_API void from_json(const nlohmann::json& j, ::minter::explorer::pool_route& resp);
MINTER_TX_API void to_json(nlohmann::json& j, const ::minter::explorer::pool_route& resp);

} // namespace explorer
} // namespace minter

#endif