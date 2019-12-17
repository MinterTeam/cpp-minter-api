/*!
 * minter-api.
 * base
 *
 * \date 16.05.19
 * \author Eduard Maximovich (edward.vstock@gmail.com)
 * \link   https://github.com/edwardstock
 */

#ifndef MINTER_GATE_BASE_H
#define MINTER_GATE_BASE_H

#include "minter/api/resp_gen.h"

namespace minter {
namespace gate {

CREATE_RESP4(
    error_result,
    int, code,
    std::string, log,
    std::string, value,
    std::string, coin)

template<class T>
struct result {
    T data;
    error_result error;
};

} // namespace gate
} // namespace minter

namespace nlohmann {
template<typename T>
struct adl_serializer<minter::gate::result<T>> {
    static void from_json(const json& j, minter::gate::result<T>& res) {
        if (j.find("data") != j.end())
            j.at("data").get_to<T>(res.data);
        if (j.find("error") != j.end())
            j.at("error").get_to<minter::gate::error_result>(res.error);
    }

    static void to_json(json& j, const minter::gate::result<T>& res) {
    }
};
} // namespace nlohmann

#endif //MINTER_GATE_BASE_H
