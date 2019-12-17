/*!
 * minter_api.
 * lp_repository.cpp
 *
 * \date 2019
 * \author Eduard Maximovich (edward.vstock@gmail.com)
 * \link   https://github.com/edwardstock
 */

#include "minter/api/liquidity/repository.h"

using namespace minter::liquidity;

TASK_RES(bip_price)
repository::get_price() {
    auto req = newRequest();
    req.add_path("price");

    return MAKE_TASK(bip_price, req);
}
