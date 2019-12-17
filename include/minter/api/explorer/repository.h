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

#include "minter/api/base_repository.h"
#include "results.hpp"

#include <iostream>
#include <memory>
#include <minter/address.h>
#include <nlohmann/json.hpp>
#include <thread>
#include <unordered_map>

using namespace minter::net;
using namespace minter;
using namespace minter::utils;

namespace minter {
namespace explorer {

using delegations_result_t = std::vector<delegated_item>;
using tx_list_t = std::vector<transaction_item>;
using reward_list_t = std::vector<reward_item>;
using validator_list_t = std::vector<validator_item>;

class repository : public virtual minter::net::base_repository {
public:
    enum reward_period {
        none,
        minute,
        hour,
        day
    };

    repository();
    ~repository() override;
    std::string getBaseUrl() const override {
        return std::string(MINTER_EXPLORER_API);
    }

    TASK_RES(balance_items)
    get_balance(const minter::address_t& address, bool withSum = false) const;
    TASK_RES(tx_list_t)
    get_transactions(const address_t& address, uint32_t page = 1, uint32_t limit = 10) const;
    TASK_RES(tx_list_t)
    get_transactions(const get_transactions_opt& opts) const;
    TASK_RES(transaction_item)
    get_transaction(const address_t& address, dev::bigint block_number) const;
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
    get_rewards(const address_t& address, reward_period period = day, const std::string& start_time = "", const std::string& end_time = "");

    TASK_RES(validator_list_t)
    get_validators() const;

    /// \brief Get validator information by public key
    /// \param pubkey
    /// \return
    TASK_RES(validator_detailed_item)
    get_validator(const minter::pubkey_t& pubkey) const;

    /// \brief Get validator's transactions with pagination
    /// \param pubkey validator public key
    /// \param opts this function doesn't use "addresses" options, only: page, start_block, end_block
    /// \return
    TASK_RES(tx_list_t)
    get_validator_transactions(const pubkey_t& pubkey, const get_transactions_opt& opts) const;

    TASK_RES(net_status)
    get_status() const;
    TASK_RES(net_status_page)
    get_status_page() const;

private:
    std::unordered_map<reward_period, std::string> m_reward_scales = {
        {minute, "minute"},
        {hour, "hour"},
        {day, "day"},
    };
};

} // namespace explorer
} // namespace minter

#endif //MINTER_REPOSITORY_H
