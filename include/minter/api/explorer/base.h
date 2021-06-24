/*!
 * minter-api.
 * explorer_result.h
 *
 * \date 2019
 * \author Eduard Maximovich (edward.vstock@gmail.com)
 * \link   https://github.com/edwardstock
 */

#ifndef MINTER_EXPLORER_BASE_H
#define MINTER_EXPLORER_BASE_H

#include "minter/api/resp_gen.h"

#include <minter/address.h>
#include <minter/hash.h>
#include <minter/minter_tx_config.h>
#include <minter/public_key.h>
#include <minter/tx/tx_type.h>
#include <nlohmann/json.hpp>
#include <string>
#include <unordered_map>
#include <vector>

namespace minter {
namespace explorer {

using field_map = std::unordered_map<std::string, std::string>;

NLOHMANN_JSON_SERIALIZE_ENUM(minter::tx_type_val, {{minter::tx_type_val::send_coin, minter::tx_type_val::send_coin},
                                                   {minter::tx_type_val::sell_coin, minter::tx_type_val::sell_coin},
                                                   {minter::tx_type_val::buy_coin, minter::tx_type_val::buy_coin},
                                                   {minter::tx_type_val::create_coin, minter::tx_type_val::create_coin},
                                                   {minter::tx_type_val::declare_candidacy, minter::tx_type_val::declare_candidacy},
                                                   {minter::tx_type_val::delegate, minter::tx_type_val::delegate},
                                                   {minter::tx_type_val::unbond, minter::tx_type_val::unbond},
                                                   {minter::tx_type_val::redeem_check, minter::tx_type_val::redeem_check},
                                                   {minter::tx_type_val::set_candidate_on, minter::tx_type_val::set_candidate_on},
                                                   {minter::tx_type_val::set_candidate_off, minter::tx_type_val::set_candidate_off},
                                                   {minter::tx_type_val::create_multisig, minter::tx_type_val::create_multisig},
                                                   {minter::tx_type_val::multisend, minter::tx_type_val::multisend},
                                                   {minter::tx_type_val::edit_candidate, minter::tx_type_val::edit_candidate},
                                                   {minter::tx_type_val::set_halt_block, minter::tx_type_val::set_halt_block},
                                                   {minter::tx_type_val::recreate_coin, minter::tx_type_val::recreate_coin},
                                                   {minter::tx_type_val::edit_coin_owner, minter::tx_type_val::edit_coin_owner},
                                                   {minter::tx_type_val::edit_multisig, minter::tx_type_val::edit_multisig},
                                                   {minter::tx_type_val::price_vote, minter::tx_type_val::price_vote},
                                                   {minter::tx_type_val::edit_candidate_public_key, minter::tx_type_val::edit_candidate_public_key},
                                                   {minter::tx_type_val::add_liquidity, minter::tx_type_val::add_liquidity},
                                                   {minter::tx_type_val::remove_liquidity, minter::tx_type_val::remove_liquidity},
                                                   {minter::tx_type_val::sell_swap_pool, minter::tx_type_val::sell_swap_pool},
                                                   {minter::tx_type_val::buy_swap_pool, minter::tx_type_val::buy_swap_pool},
                                                   {minter::tx_type_val::sell_all_swap_pool, minter::tx_type_val::sell_all_swap_pool},
                                                   {minter::tx_type_val::edit_candidate_commission, minter::tx_type_val::edit_candidate_commission},
                                                   {minter::tx_type_val::mint_token, minter::tx_type_val::mint_token},
                                                   {minter::tx_type_val::burn_token, minter::tx_type_val::burn_token},
                                                   {minter::tx_type_val::create_token, minter::tx_type_val::create_token},
                                                   {minter::tx_type_val::recreate_token, minter::tx_type_val::recreate_token},
                                                   {minter::tx_type_val::vote_commission, minter::tx_type_val::vote_commission},
                                                   {minter::tx_type_val::vote_update, minter::tx_type_val::vote_update},
                                                   {minter::tx_type_val::create_swap_pool, minter::tx_type_val::create_swap_pool}})

CREATE_RESP3(error_result,
             int, code,
             std::string, message,
             field_map, fields)

CREATE_RESP4(links_result,
             std::string, first,
             std::string, last,
             std::string, prev,
             std::string, next)

CREATE_RESP5(meta_result,
             uint64_t, current_page,
             uint64_t, last_page,
             std::string, path,
             uint32_t, per_page,
             uint64_t, total)

template<class T>
struct result {
    T data;
    error_result error;
    links_result links;
    meta_result meta;
};

struct tx_result {
    virtual ~tx_result() = default;
};

struct get_transactions_opt {
    size_t page = 0;
    std::vector<minter::address_t> addresses;
    dev::bigint start_block = dev::bigint("0");
    dev::bigint end_block = dev::bigint("0");
};

// COIN TYPE
enum coin_type {
    coin,
    token,
    pool_token
};

NLOHMANN_JSON_SERIALIZE_ENUM(minter::explorer::coin_type, {
                                                              {minter::explorer::coin_type::coin, "coin"},
                                                              {minter::explorer::coin_type::token, "token"},
                                                              {minter::explorer::coin_type::pool_token, "pool_token"},
                                                          })

CREATE_RESP3(coin_item_base,
             dev::bigint, id,
             std::string, symbol,
             coin_type, type)

} // namespace explorer
} // namespace minter

namespace nlohmann {
template<typename T>
struct adl_serializer<minter::explorer::result<T>> {
    static void from_json(const json& j, minter::explorer::result<T>& res) {
        if (j.find("data") != j.end())
            j.at("data").get_to<T>(res.data);
        if (j.find("error") != j.end()) {
            j.at("error").get_to<minter::explorer::error_result>(res.error);
        } else {
            res.error.code = 0;
        }
        if (j.find("links") != j.end()) {
            j.at("links").get_to<minter::explorer::links_result>(res.links);
        }

        if (j.find("meta") != j.end()) {
            j.at("meta").get_to<minter::explorer::meta_result>(res.meta);
        } else {
            res.meta.current_page = 0;
            res.meta.last_page = 0;
            res.meta.per_page = 0;
            res.meta.total = 0;
        }
    }

    static void to_json(json&, const minter::explorer::result<T>&) {
    }
};
} // namespace nlohmann

#endif //MINTER_EXPLORER_BASE_H
