/*!
 * minter_api.
 * gate_base.cpp
 *
 * \date 2021
 * \author Eduard Maximovich (edward.vstock@gmail.com)
 * \link   https://github.com/edwardstock
 */

#include "minter/api/gate/base.h"

void minter::gate::from_json(const nlohmann::json& j, error_result& res) {

    using field_type = std::unordered_map<std::string, std::string>;
    std::cout << j.dump() << std::endl;
    if (j.find("code") != j.end() && !j.at("code").is_null()) {
        auto codeValue = j.at("code");
        if (codeValue.is_number_integer()) {
            res.code = codeValue.get<int>();
        } else if (codeValue.is_string()) {
            auto codeS = codeValue.get<std::string>();
            res.code = std::stoi(codeS);
        } else {
            res.code = 0;
        }
    }

    JSON_GET_TO(message, std::string, res.message);

    if (res.message.empty() && j.find("log") != j.end() && !j.at("log").is_null() && j.at("log").is_string()) {
        res.message = j.at("log").get<std::string>();
    }

    JSON_GET_TO(data, field_type, res.data);
}

void minter::gate::to_json(nlohmann::json&, const minter::gate::error_result&) {
}

void minter::gate::from_json(const nlohmann::json& j, minter::gate::result& res) {
    JSON_GET_TO(error, minter::gate::error_result, res.error);

    if (j.find("code") != j.end() && !j.at("code").is_null()) {
        auto codeValue = j.at("code");
        if (codeValue.is_number_integer()) {
            res.error.code = codeValue.get<int>();
        } else if (codeValue.is_string()) {
            auto codeS = codeValue.get<std::string>();
            res.error.code = std::stoi(codeS);
        } else {
            res.error.code = 0;
        }
    }
    if (j.find("log") != j.end() && !j.at("log").is_null() && j.at("log").is_string()) {
        res.error.message = j.at("log").get<std::string>();
    }
}
void minter::gate::to_json(nlohmann::json&, const minter::gate::result&) {
}
