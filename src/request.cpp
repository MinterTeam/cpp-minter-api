/*!
 * miledger.
 * request.cpp
 *
 * \date 2021
 * \author Eduard Maximovich (edward.vstock@gmail.com)
 * \link   https://github.com/edwardstock
 */

#include "minter/api/request.h"

#include <iomanip>
#include <toolbox/strings.hpp>
#include <toolbox/strings/regex.h>

// REQUEST
minter::api::base_request::base_request()
    : io_container(),
      m_ssl(false),
      m_method(method::get),
      m_proto("http"),
      m_host(""),
      m_port("80"),
      m_path("/") {
}

minter::api::base_request::base_request(const std::string& url)
    : io_container(),
      m_ssl(false),
      m_method(method::get),
      m_proto("http"),
      m_host(""),
      m_port("80"),
      m_path("/") {
    parse_url(url);
}

minter::api::base_request::base_request(const std::string& url, uint16_t port)
    : io_container(),
      m_ssl(false),
      m_method(method::get),
      m_proto("http"),
      m_host(""),
      m_path("/") {

    m_port = std::to_string(port);
    parse_url(url);
}

minter::api::base_request::base_request(const std::string& url, minter::api::base_request::method method)
    : io_container(),
      m_ssl(false),
      m_method(method),
      m_proto("http"),
      m_host(""),
      m_port("80"),
      m_path("/") {
    parse_url(url);
}

void minter::api::base_request::parse_url(const std::string& url) {
    std::string urlParseRegex =
        R"(([a-zA-Z]+)\:\/\/([a-zA-Z0-9\.\-_]+)?\:?([0-9]{1,5})?(\/[a-zA-Z0-9\/\+\-\.\%\/_]*)?\??([a-zA-Z0-9\-_\+\=\&\%\.]*))";

    if (!toolbox::strings::matches_pattern(urlParseRegex, url)) {
        return;
    }

    auto res = toolbox::strings::find_pattern(rxns::regex(urlParseRegex), url);

    m_proto = res[1];
    m_host = res[2];
    std::string port = res[3];
    m_path = res[4];
    std::string paramsString = res[5];

    if (toolbox::strings::equals_icase(m_proto, "https")) {
        m_port = "443";
        m_ssl = true;
    } else if (toolbox::strings::equals_icase(m_proto, "ftp")) {
        m_port = "20";
        m_ssl = false;
    }

    if (!port.empty()) {
        m_port = port;
    }

    if (!paramsString.empty()) {
        auto kvs = toolbox::strings::split(paramsString, '&');
        for (auto& item : kvs) {
            auto kv = toolbox::strings::split_pair(item, '=');
            m_params.push_back({kv.first, kv.second});
        }
    }
}

void minter::api::base_request::parse_query(const std::string& query_string) {
    std::string query = query_string;
    if (query[0] == '?') {
        query = query.substr(1, query.length());
    }

    std::vector<std::string> pairs = toolbox::strings::split(query, "&");

    for (const auto& param : pairs) {
        add_query(toolbox::strings::split_pair(param, "="));
    }
}

minter::api::base_request::method minter::api::base_request::method_from_string(const std::string& method_name) {
    using toolbox::strings::equals_icase;

    if (equals_icase(method_name, "POST")) {
        return minter::api::http_method::post;
    } else if (equals_icase(method_name, "PUT")) {
        return minter::api::http_method::put;
    } else if (equals_icase(method_name, "DELETE")) {
        return minter::api::http_method::delete_;
    } else if (equals_icase(method_name, "HEAD")) {
        return minter::api::http_method::head;
    }

    return method::get;
}

std::string minter::api::base_request::method_to_string(minter::api::base_request::method methodName) {
    std::string out;

    switch (methodName) {
    case method::post:
        out = "POST";
        break;
    case method::put:
        out = "PUT";
        break;
    case method::delete_:
        out = "DELETE";
        break;
    case method::head:
        out = "HEAD";
        break;
    case method::get:
        out = "GET";
        break;

    default:
        out = "UnsupportedMethod";
    }

    return out;
}

void minter::api::base_request::set_method(minter::api::base_request::method method) {
    this->m_method = method;
}

void minter::api::base_request::add_query(minter::api::kv&& keyValue) {
    m_params.push_back(std::move(keyValue));
}

void minter::api::base_request::add_query(kvd&& keyValue) {
    auto tmp = std::move(keyValue);
    std::stringstream ss;
    ss << tmp.second;

    add_query({tmp.first, ss.str()});
}

void minter::api::base_request::add_query(minter::api::kvf&& keyValue) {
    auto tmp = std::move(keyValue);
    std::stringstream ss;
    ss << std::fixed << std::setprecision(7) << tmp.second;

    add_query({tmp.first, ss.str()});
}

void minter::api::base_request::use_ssl(bool use) {
    m_ssl = use;
}

std::string minter::api::base_request::get_url_string() const {
    std::stringstream ss;

    ss << m_proto << "://";
    ss << m_host;
    if (m_port != "80" && m_port != "443") {
        ss << ":" << m_port;
    }

    if (!m_path.empty()) {
        ss << m_path;
    } else {
        ss << "/";
    }

    if (has_query()) {
        ss << get_query_string();
    }

    return std::string(ss.str());
}
minter::api::base_request::method minter::api::base_request::get_method() const {
    return m_method;
}

std::string minter::api::base_request::get_method_str() const {
    return method_to_string(get_method());
}

bool minter::api::base_request::has_query() const {
    return !m_params.empty();
}

bool minter::api::base_request::has_query(const std::string& key, bool icase) const {
    using toolbox::strings::equals_icase;
    const auto& cmp = [icase](const std::string& lhs, const std::string& rhs) {
        if (icase) {
            return equals_icase(lhs, rhs);
        } else {
            return lhs == rhs;
        }
    };

    for (const auto& param : m_params) {
        if (cmp(param.first, key)) {
            return true;
        }
    }

    return false;
}

std::string minter::api::base_request::get_query_value(const std::string& key, bool icase) const {
    using toolbox::strings::equals_icase;
    const auto& cmp = [icase](const std::string& lhs, const std::string& rhs) {
        if (icase) {
            return equals_icase(lhs, rhs);
        } else {
            return lhs == rhs;
        }
    };
    for (const auto& param : m_params) {
        if (cmp(param.first, key)) {
            return param.second;
        }
    }

    return std::string();
}

#ifdef HAVE_CXX_OPTIONAL
std::optional<minter::api::kv> minter::api::base_request::find_query(const std::string& key, bool icase) const {
    std::optional<minter::api::kv> out;
    using toolbox::strings::equals_icase;
    const auto& cmp = [icase](const std::string& lhs, const std::string& rhs) {
        if (icase) {
            return equals_icase(lhs, rhs);
        } else {
            return lhs == rhs;
        }
    };
    for (const auto& param : m_params) {
        if (cmp(param.first, key)) {
            out = param;
            break;
        }
    }

    return out;
}
#else
minter::api::kv minter::api::base_request::find_query(const std::string& key, bool icase) const {
    minter::api::kv out;
    using toolbox::strings::equals_icase;
    const auto& cmp = [icase](const std::string& lhs, const std::string& rhs) {
        if (icase) {
            return equals_icase(lhs, rhs);
        } else {
            return lhs == rhs;
        }
    };
    for (const auto& param : m_params) {
        if (cmp(param.first, key)) {
            out = param;
            break;
        }
    }

    return out;
}
#endif

void minter::api::base_request::set_query(const std::string& key, const std::string& value, bool icase) {
    using toolbox::strings::equals_icase;
    const auto& cmp = [icase](const std::string& lhs, const std::string& rhs) {
        if (icase) {
            return equals_icase(lhs, rhs);
        } else {
            return lhs == rhs;
        }
    };
    for (auto& param : m_params) {
        if (cmp(param.first, key)) {
            param.second = value;
        }
    }
}

void minter::api::base_request::set_query(const minter::api::kv& kv, bool icase) {
    set_query(kv.first, kv.second, icase);
}

bool minter::api::base_request::remove_query_array(const std::string& key, size_t index, bool icase) {
    using toolbox::strings::equals_icase;
    const auto& cmp = [icase](const std::string& lhs, const std::string& rhs) {
        if (icase) {
            return equals_icase(lhs, rhs);
        } else {
            return lhs == rhs;
        }
    };

    size_t foundCount = 0;
    size_t erasedItems = 0;

    auto it = m_params.begin();
    while (it != m_params.end()) {
        if (cmp(it->first, key)) {
            if (foundCount == index) {
                it = m_params.erase(it);
                erasedItems++;
            } else {
                ++it;
            }
            foundCount++;
        } else {
            ++it;
        }
    }

    return erasedItems > 0;
}

bool minter::api::base_request::remove_query(const std::string& key, bool icase) {
    using toolbox::strings::equals_icase;
    const auto& cmp = [icase](const std::string& lhs, const std::string& rhs) {
        if (icase) {
            return equals_icase(lhs, rhs);
        } else {
            return lhs == rhs;
        }
    };

    int foundCount = 0;

    auto it = m_params.begin();
    while (it != m_params.end()) {
        if (cmp(it->first, key)) {
            it = m_params.erase(it);
            foundCount++;
        } else {
            ++it;
        }
    }

    return foundCount > 0;
}

void minter::api::base_request::clear_queries() {
    m_params.clear();
}

size_t minter::api::base_request::queries_size() const {
    return m_params.size();
}

std::vector<std::string> minter::api::base_request::get_query_array(const std::string& key, bool icase) const {
    std::vector<std::string> out;

    using toolbox::strings::equals_icase;
    const auto& cmp = [icase](const std::string& lhs, const std::string& rhs) {
        if (icase) {
            return equals_icase(lhs, rhs);
        } else {
            return lhs == rhs;
        }
    };

    for (const auto& param : m_params) {
        if (cmp(param.first, key)) {
            out.push_back(param.second);
        }
    }

    return out;
}

std::string minter::api::base_request::get_query_string() const {
    std::string combined;
    if (!m_params.empty()) {
        std::stringstream ss;
        std::vector<std::string> enc;
        for (auto& p : m_params) {
            ss << p.first << "=" << p.second;
            enc.push_back(ss.str());
            ss.str("");
            ss.clear();
        }
        std::string glued = toolbox::strings::glue("&", enc);
        combined += "?" + glued;
    }

    return combined;
}

const minter::api::kv_vector& minter::api::base_request::get_query_list() const {
    return m_params;
}

std::string minter::api::base_request::get_host() const {
    return m_host;
}

void minter::api::base_request::set_host(const std::string& hostname) {
    m_host = hostname;
}

uint16_t minter::api::base_request::get_port() const {
    const int port = std::stoi(m_port);

    return (uint16_t) port;
}

void minter::api::base_request::set_port(uint16_t portNumber) {
    m_port = std::to_string(portNumber);
}

std::string minter::api::base_request::get_port_str() const {
    return m_port;
}

std::string minter::api::base_request::get_proto_name() const {
    return m_proto;
}

void minter::api::base_request::set_proto_name(const std::string& protocolName) {
    m_proto = protocolName;
}

std::string minter::api::base_request::get_path() const {
    if (m_path.empty()) {
        return "/";
    }
    return m_path;
}

std::string minter::api::base_request::get_path_with_query() const {
    return get_path() + get_query_string();
}

void minter::api::base_request::set_path(const std::string& path) {
    if (m_path.length() == 0) {
        m_path = "/";
    } else if (m_path.length() > 0 && m_path[0] != '/') {
        m_path = "/" + m_path;
    }

    if (path.length() > 1 && path[0] != '/') {
        m_path = "/" + path;
    } else {
        m_path = path;
    }
}

void minter::api::base_request::add_path(const std::string& path) {
    if (path.length() == 0 || (path.length() == 1 && path[0] == '/')) {
        return;
    }

    if (m_path.length() == 0) {
        m_path = "/";
    }

    if (path[0] == '/') {
        if (m_path[m_path.length() - 1] == '/') {
            m_path += path.substr(1, path.length());
        } else {
            m_path += path;
        }
    } else {
        if (m_path[m_path.length() - 1] != '/') {
            m_path += '/' + path;
        } else {
            m_path += path;
        }
    }
}

bool minter::api::base_request::is_ssl() const {
    return m_ssl;
}
