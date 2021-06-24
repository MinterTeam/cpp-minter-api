/*!
 * minter_api.
 * explorer_repository.cpp
 *
 * \date 2019
 * \author Eduard Maximovich (edward.vstock@gmail.com)
 * \link   https://github.com/edwardstock
 */

#include "minter/api/explorer/explorer_repo.h"
#include "minter/api/explorer/explorer_results.h"
using namespace minter::explorer;
using namespace minter::api;

repository::repository() = default;
repository::~repository() = default;

std::string repository::get_base_url() const {
    return {MINTER_EXPLORER_API};
}

TASK_RES(balance_items)
repository::get_balance(const minter::address_t& address, bool withSum) const {
    auto req = create_request();
    req.add_path("addresses");
    req.add_path(address.to_string());

    if (withSum) {
        req.add_query(kv{"withSum", "true"});
    }

    return MAKE_TASK(balance_items, req);
}

TASK_RES(tx_list_t)
repository::get_transactions(const minter::address_t& address, uint32_t page, uint32_t limit, repository::tx_send_type send_type) const {
    auto req = create_request();
    req.add_path("addresses");
    req.add_path(address.to_string());
    req.add_path("transactions");

    req.add_query(kvd{"page", page});
    req.add_query(kvd{"limit", limit});

    if (send_type == incoming) {
        req.add_query({"send_type", "incoming"});
    } else if (send_type == outgoing) {
        req.add_query({"send_type", "outcoming"});
    }

    return MAKE_TASK(tx_list_t, req);
}

TASK_RES(tx_list_t)
repository::get_transactions(const get_transactions_opt& opts) const {
    auto req = create_request();
    req.add_path("transactions");
    if (opts.page) {
        req.add_query(kvd("page", opts.page));
    }
    if (opts.start_block) {
        req.add_query(kv("start_block", (minter::utils::to_string(opts.start_block))));
    }
    if (opts.end_block) {
        req.add_query(kv("end_block", (minter::utils::to_string(opts.end_block))));
    }
    if (!opts.addresses.empty()) {
        for (const auto& addr : opts.addresses) {
            req.add_query(kv("addresses[]", (addr.to_string())));
        }
    }

    return MAKE_TASK(tx_list_t, req);
}

TASK_RES(transaction_item)
repository::get_transaction(const minter::hash_t& hash) const {
    auto req = create_request();
    req.add_path("transactions");
    req.add_path((hash.to_string()));

    return MAKE_TASK(transaction_item, req);
}

TASK_RES(transaction_item)
repository::get_transaction(const minter::address_t& address, dev::bigint block_number) const {
    auto req = create_request();
    req.add_path("addresses");
    req.add_path((address.to_string()));
    req.add_path("transactions");

    req.add_query(kvd("start_block", block_number));
    req.add_query(kvd("end_block", block_number));

    return MAKE_TASK(transaction_item, req);
    //    return MAKE_TASK(tx_list_t, req)
    //        .map([](result<tx_list_t> source) {
    //            result<transaction_item> out;
    //            out.error = source.error;
    //            if (source.data.empty()) {
    //                out.error.code = 404;
    //                out.error.message = "Not found";
    //            } else {
    //                out.data = source.data.at(0);
    //            }
    //            return out;
    //        });
}

TASK_RES(delegations_result_t)
repository::get_delegated(const std::string& address) const {
    auto req = create_request();
    req.add_path("addresses");
    req.add_path((address));
    req.add_path("delegations");

    return MAKE_TASK(delegations_result_t, req);
}

TASK_RES(reward_list_t)
repository::get_rewards(const minter::address_t& address,
                        repository::reward_period period,
                        const std::string& start_time,
                        const std::string& end_time) {
    auto req = create_request();
    req.add_path("addresses");
    req.add_path((address.to_string()));
    req.add_path("statistics/rewards");

    if (period != none) {
        req.add_query({"scale", m_reward_scales[period]});
    }
    if (!start_time.empty()) {
        req.add_query({"startTime", (start_time)});
    }
    if (!end_time.empty()) {
        req.add_query({"endTime", (end_time)});
    }

    return MAKE_TASK(reward_list_t, req);
}

TASK_RES(validator_list_t)
repository::get_validators() const {
    auto req = create_request();
    req.add_path("validators");

    return MAKE_TASK(validator_list_t, req);
}

TASK_RES(validator_detailed_item)
repository::get_validator(const minter::pubkey_t& pubkey) const {
    auto req = create_request();
    req.add_path("validators");
    req.add_path((pubkey.to_string()));

    return MAKE_TASK(validator_detailed_item, req);
}

TASK_RES(tx_list_t)
repository::get_validator_transactions(const minter::pubkey_t& pubkey, const get_transactions_opt& opts) const {
    auto req = create_request();
    req.add_path("validators");
    req.add_path((pubkey.to_string()));
    req.add_path("transactions");

    if (opts.page) {
        req.add_query(kvd("page", opts.page));
    }
    if (opts.start_block) {
        req.add_query(kv("start_block", (minter::utils::to_string(opts.start_block))));
    }
    if (opts.end_block) {
        req.add_query(kv("end_block", (minter::utils::to_string(opts.end_block))));
    }

    return MAKE_TASK(tx_list_t, req);
}

TASK_RES(net_status)
repository::get_status() const {
    auto req = create_request();
    req.add_path("status");

    return MAKE_TASK(net_status, req);
}

TASK_RES(net_status_page)
repository::get_status_page() const {
    auto req = create_request();
    req.add_path("status-page");

    return MAKE_TASK(net_status_page, req);
}

TASK_RES(std::vector<pool>)
repository::pools_list(uint32_t page) const {
    auto req = create_request();
    req.add_path("pools");
    if (page > 0) {
        req.add_query(kvd("page", page));
    }

    return MAKE_TASK(std::vector<pool>, req);
}

TASK_RES_ROOT(pool_route)
repository::get_pool_route(
    const coin_item_base& coin0,
    const coin_item_base& coin1,
    const dev::bigdec18& amount,
    pool_swap_type swap_type) const {

    auto req = create_request();
    req.add_path("pools/coins");
    req.add_path((minter::utils::to_string(coin0.id)));
    req.add_path((minter::utils::to_string(coin1.id)));
    req.add_path("route");

    req.add_query(kv("amount", (minter::utils::normalize_value(amount).str())));

    if (swap_type == buy) {
        req.add_query(kv("type", "output"));
    } else {
        req.add_query(kv("type", "input"));
    }

    return MAKE_TASK_ROOT(pool_route, req);
}
TASK_RES_ROOT(pool_route)
repository::get_pool_estimate(
    const coin_item_base& coin0,
    const coin_item_base& coin1,
    const dev::bigdec18& amount,
    pool_swap_type swap_type) const {

    auto req = create_request();
    req.add_path("pools/coins");
    req.add_path((minter::utils::to_string(coin0.id)));
    req.add_path((minter::utils::to_string(coin1.id)));
    req.add_path("estimate");

    req.add_query(kv("amount", (minter::utils::normalize_value(amount).str())));

    if (swap_type == buy) {
        req.add_query(std::pair<std::string, std::string>("type", "output"));
    } else {
        req.add_query(std::pair<std::string, std::string>("type", "input"));
    }

    return MAKE_TASK_ROOT(pool_route, req);
}

TASK_RES(pool)
repository::get_pool(const std::string& coin0, const std::string& coin1) const {
    auto req = create_request();
    req.add_path("pools/coins");
    req.add_path((coin0));
    req.add_path((coin1));

    return MAKE_TASK(pool, req);
}

TASK_RES(pool)
repository::get_pool(const coin_item_base& coin0, const coin_item_base& coin1) const {
    auto req = create_request();
    req.add_path("pools/coins");
    req.add_path((coin0.symbol));
    req.add_path((coin1.symbol));

    return MAKE_TASK(pool, req);
}

TASK_RES(pool_providers)
repository::get_pool_providers(const std::string& coin0, const std::string& coin1) const {
    auto req = create_request();
    req.add_path("pools/coins");
    req.add_path((coin0));
    req.add_path((coin1));
    req.add_path("providers");

    return MAKE_TASK(pool_providers, req);
}
TASK_RES(pool_provider)
repository::get_pool_provider(const std::string& coin0, const std::string& coin1, const minter::address_t& address) const {
    auto req = create_request();
    req.add_path("pools/coins");
    req.add_path((coin0));
    req.add_path((coin1));
    req.add_path("providers");
    req.add_path((address.to_string()));

    return MAKE_TASK(pool_provider, req);
}

TASK_RES(pool_providers)
repository::get_pool_providers(const minter::address_t& address) const {
    auto req = create_request();
    req.add_path("pools/providers");
    req.add_path((address.to_string()));

    return MAKE_TASK(pool_providers, req);
}

TASK_RES(std::vector<coin_item>)
repository::get_coins() const {
    auto req = create_request();
    req.add_path("coins");

    return MAKE_TASK(std::vector<coin_item>, req);
}

TASK_RES(std::vector<coin_item>)
repository::search_coins(const std::string& symbol) const {
    auto req = create_request();
    req.add_path("coins");

    req.add_query(kv("symbol", symbol));

    return MAKE_TASK(std::vector<coin_item>, req);
}

TASK_RES(coin_item)
repository::get_coin_by_id(const dev::bigint& coin_id) const {
    auto req = create_request();
    req.add_path("coins/id");
    req.add_path((minter::utils::to_string(coin_id)));

    return MAKE_TASK(coin_item, req);
}

TASK_RES(coin_item)
repository::get_coin_by_id(const std::string& coin_id) const {
    auto req = create_request();
    req.add_path("coins/id");
    req.add_path(coin_id);

    return MAKE_TASK(coin_item, req);
}