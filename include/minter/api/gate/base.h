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

#include <unordered_map>

namespace minter {
namespace gate {

struct error_result {
    int code = 0;
    std::string message;
    std::unordered_map<std::string, std::string> data;
};

struct result {
    error_result error;

    [[nodiscard]] bool is_ok() const {
        return error.code == 0 && error.message.empty();
    }
};

enum estimate_swap_from {
    optimal,
    bancor,
    pool
};
NLOHMANN_JSON_SERIALIZE_ENUM(minter::gate::estimate_swap_from, {{minter::gate::estimate_swap_from::optimal, "optimal"},
                                                                {minter::gate::estimate_swap_from::bancor, "bancor"},
                                                                {minter::gate::estimate_swap_from::pool, "pool"}})

MINTER_TX_API void from_json(const nlohmann::json& j, minter::gate::error_result& res);
MINTER_TX_API void to_json(nlohmann::json& j, const minter::gate::error_result& resp);
MINTER_TX_API void from_json(const nlohmann::json& j, minter::gate::result& res);
MINTER_TX_API void to_json(nlohmann::json& j, const minter::gate::result& resp);

} // namespace gate
} // namespace minter

#endif // MINTER_GATE_BASE_H
