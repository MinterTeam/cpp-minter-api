/*!
 * minter-api.
 * repository
 *
 * \date 15.05.19
 * \author Eduard Maximovich (edward.vstock@gmail.com)
 * \link   https://github.com/edwardstock
 */

#ifndef MINTER_GATE_REPOSITORY_H
#define MINTER_GATE_REPOSITORY_H

#include "base.h"
#include "minter/api/base_repository.h"
#include "results.hpp"

#include <bip3x/utils.h>
#include <memory>
#include <minter/minter_tx_config.h>
#include <minter/tx/utils.h>
#include <nlohmann/json.hpp>
#include <sstream>

using namespace minter::net;
using namespace minter;
using namespace minter::utils;

namespace minter {
namespace gate {

struct tx_init_data {
    dev::bigint nonce;
    dev::bigint gas = dev::bigint("1");
};

class repository : public virtual minter::net::base_repository {
public:
    std::string getBaseUrl() const override {
        return std::string(MINTER_GATE_API);
    }

    TASK_RES(gas_value)
    get_min_gas();
    TASK_RES(tx_count_value)
    get_tx_count(const address_t& address);
    TASK_RES(commission_value)
    get_tx_commission_value(const dev::bytes_data& tx_sign);
    TASK_RES(exchange_buy_value)
    get_exchange_buy_currency(const std::string& coin_to_sell, const dev::bigdec18& value_to_buy, const std::string& coin_to_buy);
    TASK_RES(exchange_sell_value)
    get_exchange_sell_currency(const std::string& coin_to_sell, const dev::bigdec18& value_to_sell, const std::string& coin_to_buy);
    TASK_RES(tx_send_result)
    send_tx(const dev::bytes_data& tx_sign);

    /// \brief Get initial data for transaction construction: nonce and gas price
    /// \param address address to fetch values
    /// \param error pass bool value to check error
    /// \return non
    tx_init_data get_tx_init_data(const minter::address_t& address, bool& error);
};

} // namespace gate
} // namespace minter

#endif //MINTER_GATE_REPOSITORY_H
