/*!
 * minter_api.
 * explorer_repository.cpp
 *
 * \date 2019
 * \author Eduard Maximovich (edward.vstock@gmail.com)
 * \link   https://github.com/edwardstock
 */

#include "minter/api/explorer/repository.h"

#include <minter/tx/utils.h>
using namespace minter::explorer;

repository::repository()
    : base_repository() {
}

repository::~repository() {
}

TASK_RES(balance_items)
repository::get_balance(const address_t& address, bool withSum) const {
    auto req = newRequest();
    req.add_path("addresses");
    req.add_path(address.to_string());

    if (withSum) {
        req.add_query(httb::kv{"withSum", "true"});
    }

    return MAKE_TASK(balance_items, req);
}

TASK_RES(tx_list_t)
repository::get_transactions(const address_t& address, uint32_t page, uint32_t limit) const {
    auto req = newRequest();
    req.add_path("addresses");
    req.add_path(address.to_string());
    req.add_path("transactions");

    req.add_query(httb::kvd{"page", page});
    req.add_query(httb::kvd{"limit", limit});

    return MAKE_TASK(tx_list_t, req);
}

TASK_RES(tx_list_t)
repository::get_transactions(const get_transactions_opt& opts) const {
    auto req = newRequest();
    req.add_path("transactions");
    if (opts.page) {
        req.add_query(httb::kvd("page", opts.page));
    }
    if (opts.start_block) {
        req.add_query(httb::kv("startblock", minter::utils::to_string(opts.start_block)));
    }
    if (opts.end_block) {
        req.add_query(httb::kv("endblock", minter::utils::to_string(opts.end_block)));
    }
    if (!opts.addresses.empty()) {
        for (const auto& addr : opts.addresses) {
            req.add_query(httb::kv("addresses[]", addr.to_string()));
        }
    }

    return MAKE_TASK(tx_list_t, req);
}

TASK_RES(transaction_item)
repository::get_transaction(const minter::hash_t& hash) const {
    auto req = newRequest();
    req.add_path("transactions");
    req.add_path(hash.to_string());

    return MAKE_TASK(transaction_item, req);
}

TASK_RES(transaction_item)
repository::get_transaction(const address_t& address, dev::bigint block_number) const {
    auto req = newRequest();
    req.add_path("addresses");
    req.add_path(address.to_string());
    req.add_path("transactions");

    req.add_query(httb::kvd("startblock", block_number));
    req.add_query(httb::kvd("endblock", block_number));

    return MAKE_MAP_TASK(tx_list_t, transaction_item, req, [](result<tx_list_t> source) {
        result<transaction_item> out;
        out.error = source.error;
        if (source.data.empty()) {
            out.error.code = 404;
            out.error.message = "Not found";
        } else {
            out.data = source.data.at(0);
        }

        return out;
    });
}

TASK_RES(delegations_result_t)
repository::get_delegated(const std::string& address) const {
    auto req = newRequest();
    req.add_path("addresses");
    req.add_path(address);
    req.add_path("delegations");

    return MAKE_TASK(delegations_result_t, req);
}

TASK_RES(reward_list_t)
repository::get_rewards(const address_t& address,
                        repository::reward_period period,
                        const std::string& start_time,
                        const std::string& end_time) {
    auto req = newRequest();
    req.add_path("addresses");
    req.add_path(address.to_string());
    req.add_path("statistics/rewards");

    if (period != none) {
        req.add_query({"scale", m_reward_scales[period]});
    }
    if (!start_time.empty()) {
        req.add_query({"startTime", start_time});
    }
    if (!end_time.empty()) {
        req.add_query({"endTime", end_time});
    }

    return MAKE_TASK(reward_list_t, req);
}

TASK_RES(validator_list_t)
repository::get_validators() const {
    auto req = newRequest();
    req.add_path("validators");

    return MAKE_TASK(validator_list_t, req);
}

TASK_RES(validator_detailed_item)
repository::get_validator(const minter::pubkey_t& pubkey) const {
    auto req = newRequest();
    req.add_path("validators");
    req.add_path(pubkey.to_string());

    return MAKE_TASK(validator_detailed_item, req);
}

TASK_RES(tx_list_t)
repository::get_validator_transactions(const pubkey_t& pubkey, const explorer::get_transactions_opt& opts) const {
    auto req = newRequest();
    req.add_path("validators");
    req.add_path(pubkey.to_string());
    req.add_path("transactions");

    if (opts.page) {
        req.add_query(httb::kvd("page", opts.page));
    }
    if (opts.start_block) {
        req.add_query(httb::kv("startblock", minter::utils::to_string(opts.start_block)));
    }
    if (opts.end_block) {
        req.add_query(httb::kv("endblock", minter::utils::to_string(opts.end_block)));
    }

    return MAKE_TASK(tx_list_t, req);
}

TASK_RES(net_status)
repository::get_status() const {
    auto req = newRequest();
    req.add_path("status");

    return MAKE_TASK(net_status, req);
}

TASK_RES(net_status_page)
repository::get_status_page() const {
    auto req = newRequest();
    req.add_path("status-page");

    return MAKE_TASK(net_status_page, req);
}