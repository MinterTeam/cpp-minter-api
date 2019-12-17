/*!
 * minter-api.
 * base
 *
 * \author Eduard Maximovich (edward.vstock@gmail.com)
 * \link   https://github.com/edwardstock
 */

#ifndef MINTER_LIQUIDITY_BASE_H
#define MINTER_LIQUIDITY_BASE_H

#include "minter/api/resp_gen.h"

namespace minter {
namespace liquidity {

CREATE_RESP2(
    error_result,
    int, code,
    std::string, message)

template<class T>
struct result {
    T data;
    error_result error;
};

} // namespace liquidity
} // namespace minter

namespace nlohmann {
template<typename T>
struct adl_serializer<minter::liquidity::result<T>> {
    static void from_json(const json& j, minter::liquidity::result<T>& res) {
        if (j.find("data") != j.end())
            j.at("data").get_to<T>(res.data);
        if (j.find("error") != j.end())
            j.at("error").get_to<minter::liquidity::error_result>(res.error);
    }

    static void to_json(json& j, const minter::liquidity::result<T>& res) {
    }
};
} // namespace nlohmann

#endif //MINTER_LIQUIDITY_BASE_H
