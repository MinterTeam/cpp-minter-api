/*!
 * minter-api.
 * base_repository.cpp
 *
 * \date 2019
 * \author Eduard Maximovich (edward.vstock@gmail.com)
 * \link   https://github.com/edwardstock
 */

#include "minter/api/base_repository.h"

minter::net::base_repository::base_repository() {
}
minter::net::base_repository::~base_repository() {
}
std::string minter::net::base_repository::getBaseUrl() const {
    return std::string();
}
