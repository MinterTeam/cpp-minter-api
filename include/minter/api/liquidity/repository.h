/*!
 * minter-api.
 * repository.h
 *
 * \date 2019
 * \author Eduard Maximovich (edward.vstock@gmail.com)
 * \link   https://github.com/edwardstock
 */

#ifndef MINTER_LIQUIDITY_REPOSITORY_H
#define MINTER_LIQUIDITY_REPOSITORY_H

#include "base.h"
#include "minter/api/base_repository.h"
#include "results.hpp"

#include <minter/address.h>
#include <minter/minter_tx_config.h>
#include <minter/tx/utils.h>

using namespace minter::net;
using namespace minter;
using namespace minter::utils;

namespace minter {
namespace liquidity {

class repository : public virtual minter::net::base_repository {
public:
    std::string getBaseUrl() const override {
        return std::string(MINTER_LP_API);
    }

    TASK_RES(bip_price)
    get_price();
};

} // namespace liquidity
} // namespace minter

#endif //MINTER_LIQUIDITY_REPOSITORY_H
