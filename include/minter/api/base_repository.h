/*!
 * minter-api.
 * base_repository.h
 *
 * \date 2019
 * \author Eduard Maximovich (edward.vstock@gmail.com)
 * \link   https://github.com/edwardstock
 */

#ifndef MINTER_BASE_REPOSITORY_H
#define MINTER_BASE_REPOSITORY_H

#include "minter/api/minter_api_config.h"
#include "request.h"

#include <chrono>
#include <cpr/cpr.h>
#include <fmt/format.h>
#include <iostream>
#include <memory>
#include <nlohmann/json.hpp>
#include <rxcpp/rx-observable.hpp>
#include <string>
#include <unordered_map>
#include <utility>

namespace minter {
namespace api {

class base_repository {
public:
    virtual std::string get_base_url() const = 0;

    minter::api::request create_request() const {
        return minter::api::request(get_base_url());
    }

    template<class T>
    rxcpp::observable<T> defer_task(minter::api::request&& req) const {
        return rxcpp::observable<>::create<T>([req](rxcpp::subscriber<T> emitter) {
            cpr::Response resp;
            cpr::Session session;

#ifdef _MSC_VER
            session.SetVerifySsl(cpr::VerifySsl(false));
#endif

            session.SetUrl(cpr::Url(req.get_url_string()));
            cpr::Header headers;
            for (const auto& h : req.get_headers()) {
                headers.insert(std::pair<std::string, std::string>(h.first, h.second));
            }

            switch (req.get_method()) {
            case minter::api::request::method::get: {
                curl_easy_setopt(session.GetCurlHolder()->handle, CURLOPT_NOSIGNAL, 1);
                resp = session.Get();
            } break;
            case minter::api::request::method::post:
                session.SetBody(cpr::Body(req.get_body()));
                curl_easy_setopt(session.GetCurlHolder()->handle, CURLOPT_NOSIGNAL, 1);
                resp = session.Post();
                break;
            default:
                emitter.on_error(
                    std::make_exception_ptr(
                        std::runtime_error("Unsupported HTTP method")));
                // nothing yet
                break;
            }

            if (resp.error && resp.text.empty()) {
                emitter.on_error(std::make_exception_ptr(
                    std::runtime_error(fmt::format("Unable to proceed request {0}: [{1}] {2}", req.get_url_string(), resp.error.code, resp.error.message))));
                return;
            }

            nlohmann::json val;

            try {
                //                std::cerr << "Raw response: " << resp.text << std::endl;
                val = nlohmann::json::parse(resp.text);
            } catch (const std::exception& e) {
                emitter.on_error(std::make_exception_ptr(std::runtime_error(e.what())));
                return;
            } catch (...) {
                emitter.on_error(std::current_exception());
                return;
            }

            T res = val.get<T>();

            emitter.on_next(res);
            emitter.on_completed();
        });
    }
};

/// \brief Wrapper for result shared pointer
#define TASK_RES(type) rxcpp::observable<result<type>>
#define TASK_RES_ROOT(type) rxcpp::observable<type>

#define MAKE_TASK(type, req) defer_task<result<type>>(std::move(req))
#define MAKE_TASK_ROOT(type, req) defer_task<type>(std::move(req))

} // namespace api
} // namespace minter

#endif // MINTER_BASE_REPOSITORY_H
