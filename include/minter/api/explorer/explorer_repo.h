/*!
 * minter-api.
 * explorer_repository.h
 *
 * \date 2019
 * \author Eduard Maximovich (edward.vstock@gmail.com)
 * \link   https://github.com/edwardstock
 */

#ifndef MINTER_EXPLORER_REPOSITORY_H
#define MINTER_EXPLORER_REPOSITORY_H

#include "explorer_results.h"
#include "minter/api/base_repository.h"

#include <memory>
#include <minter/address.h>
#include <unordered_map>

using namespace minter;
using namespace minter::utils;

namespace minter {
namespace explorer {

struct enum_class_hasher {
    template<typename T>
    std::size_t operator()(T t) const {
        return static_cast<std::size_t>(t);
    }
};

using delegations_result_t = std::vector<delegated_item>;
using tx_list_t = std::vector<transaction_item>;
using reward_list_t = std::vector<reward_item>;
using validator_list_t = std::vector<validator_item>;
using pool_providers = std::vector<pool_provider>;

enum pool_swap_type {
    buy,
    sell
};

class repository : public virtual minter::api::base_repository {
public:
    enum reward_period : size_t {
        none,
        minute,
        hour,
        day
    };

    enum tx_send_type : size_t {
        no_type,
        incoming,
        outgoing
    };

    repository();
    ~repository();

    std::string get_base_url() const override;

    TASK_RES(balance_items)
    get_balance(const minter::address_t& address, bool withSum = false) const;
    TASK_RES(tx_list_t)
    get_transactions(const minter::address_t& address, uint32_t page = 1, uint32_t limit = 10, tx_send_type send_type = tx_send_type::no_type) const;
    TASK_RES(tx_list_t)
    get_transactions(const get_transactions_opt& opts) const;
    TASK_RES(transaction_item)
    get_transaction(const minter::address_t& address, dev::bigint block_number) const;
    TASK_RES(transaction_item)
    get_transaction(const minter::hash_t& hash) const;
    TASK_RES(delegations_result_t)
    get_delegated(const std::string& address) const;

    /// \brief
    /// \param address
    /// \param period  Chart scale. Possible variants: minute | hour | day. Default is day
    /// \param start_time Chart start time. Formats: YYYY-MM-DD | YYYY-MM-DD HH:MM:SS
    /// \param end_time Chart end time. Formats: YYYY-MM-DD | YYYY-MM-DD HH:MM:SS
    /// \return
    TASK_RES(reward_list_t)
    get_rewards(const minter::address_t& address, reward_period period = day, const std::string& start_time = "", const std::string& end_time = "");

    TASK_RES(validator_list_t)
    get_validators() const;

    /// \brief Get validator information by public key
    /// \param pubkey
    /// \return
    TASK_RES(validator_detailed_item)
    get_validator(const minter::pubkey_t& pubkey) const;

    /// \brief Get validator'header_s transactions with pagination
    /// \param pubkey validator public key
    /// \param opts this function doesn't use "addresses" options, only: page, start_block, end_block
    /// \return
    TASK_RES(tx_list_t)
    get_validator_transactions(const minter::pubkey_t& pubkey, const get_transactions_opt& opts) const;

    TASK_RES(net_status)
    get_status() const;
    TASK_RES(net_status_page)
    get_status_page() const;

    TASK_RES(std::vector<pool>)
    pools_list(uint32_t page = 0) const;

    TASK_RES(pool)
    get_pool(const std::string& coin0, const std::string& coin1) const;

    TASK_RES(pool)
    get_pool(const minter::explorer::coin_item_base& coin0, const minter::explorer::coin_item_base& coin1) const;

    TASK_RES_ROOT(pool_route)
    get_pool_route(
        const coin_item_base& coin0,
        const coin_item_base& coin1,
        const dev::bigdec18& amount,
        pool_swap_type swap_type) const;

    TASK_RES_ROOT(pool_route)
    get_pool_estimate(
        const coin_item_base& coin0,
        const coin_item_base& coin1,
        const dev::bigdec18& amount,
        pool_swap_type swap_type) const;

    TASK_RES(std::vector<pool_provider>)
    get_pool_providers(const std::string& coin0, const std::string& coin1) const;

    TASK_RES(pool_provider)
    get_pool_provider(const std::string& coin0, const std::string& coin1, const minter::address_t& address) const;

    TASK_RES(pool_providers)
    get_pool_providers(const minter::address_t& address) const;

    TASK_RES(std::vector<coin_item>)
    get_coins() const;

    TASK_RES(std::vector<coin_item>)
    search_coins(const std::string& symbol) const;

    TASK_RES(coin_item)
    get_coin_by_id(const dev::bigint& coin_id) const;

    TASK_RES(coin_item)
    get_coin_by_id(const std::string& coin_id) const;

private:
    std::unordered_map<reward_period, std::string, enum_class_hasher> m_reward_scales = {
        {minute, "minute"},
        {hour, "hour"},
        {day, "day"},
    };
};

} // namespace explorer
} // namespace minter

#endif // MINTER_REPOSITORY_H
