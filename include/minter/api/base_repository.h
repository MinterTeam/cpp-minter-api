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

#include <boost/asio/io_context.hpp>
#include <chrono>
#include <future>
#include <httb/httb.h>
#include <memory>
#include <mutex>
#include <nlohmann/json.hpp>
#include <string>
#include <thread>
#include <unordered_map>
#include <utility>

namespace minter {
namespace net {

class base_repository {
public:
    using response_cb = std::function<void(httb::response)>;

    base_repository();
    virtual ~base_repository();

    virtual std::string getBaseUrl() const = 0;

    httb::request newRequest() const {
        return httb::request(getBaseUrl());
    }

private:
};

using on_progress = std::function<void()>;
template<typename T>
using on_success = std::function<void(T)>;
template<typename T>
using on_error = std::function<void(httb::response, T)>;
using on_complete = std::function<void()>;

template<typename T>
class response_task;

template<typename Source, typename T>
class convertible_response_task;

template<typename T>
using task_ptr = std::shared_ptr<response_task<T>>;

template<typename Source, typename T>
using task_conv_ptr = std::shared_ptr<convertible_response_task<Source, T>>;

template<typename T, typename... _Args>
inline task_ptr<T> make_task_ptr(_Args&&... __args) {
    return std::make_shared<response_task<T>>(std::forward<_Args>(__args)...);
}

template<typename Source, typename T, typename... _Args>
inline task_conv_ptr<Source, T> make_conv_task_ptr(_Args&&... __args) {
    return std::make_shared<convertible_response_task<Source, T>>(std::forward<_Args>(__args)...);
}

#define MAKE_TASK(type, req) make_task_ptr<result<type>>(std::move(req))
#define MAKE_MAP_TASK(stype, ttype, req, mapper) make_conv_task_ptr<result<stype>, result<ttype>>(std::move(req), mapper)
#define TASK_RES(type) task_ptr<result<type>>
#define TASK_MAP_RES(stype, ttype) task_conv_ptr<result<stype>, result<ttype>>

template<typename A, typename B>
using map_func_t = std::function<B(A)>;

template<typename T>
class response_task : public std::enable_shared_from_this<response_task<T>> {
public:
    response_task(httb::request&& req)
        : m_ctx(), m_request(std::move(req)) {
    }

    template<typename S>
    void execute(map_func_t<S, T> mapper) {
        client.execute_in_context(m_ctx, m_request, [this, mapper](httb::response resp) {
            nlohmann::json val = nlohmann::json::parse(resp.data);
            T res = mapper(val.get<S>());

            if (resp.success()) {
                if (m_on_success) {
                    m_on_success(res);
                }
            } else {
                if (m_on_error) {
                    m_on_error(resp, res);
                }
            }

            if (m_on_complete) {
                m_on_complete();
            }
        });

        if (m_on_progress) {
            m_on_progress();
        }

        m_ctx.run();
    }

    void execute() {
        client.execute_in_context(m_ctx, m_request, [this](httb::response resp) {
            nlohmann::json val = nlohmann::json::parse(resp.data);
            T res = value_from_json(val);

            if (resp.success()) {
                if (m_on_success) {
                    m_on_success(res);
                }
            } else {
                if (m_on_error) {
                    m_on_error(resp, res);
                }
            }

            if (m_on_complete) {
                m_on_complete();
            }
        });

        if (m_on_progress) {
            m_on_progress();
        }

        m_ctx.run();
    }

    std::shared_ptr<response_task<T>> execute(boost::asio::io_context& io_ctx) {
        client.execute_in_context(io_ctx, m_request, [this](httb::response resp) {
            nlohmann::json val = nlohmann::json::parse(resp.data);
            T res = val.get<T>();

            if (resp.success()) {
                if (m_on_success) {
                    m_on_success(res);
                }
            } else {
                if (m_on_error) {
                    m_on_error(resp, res);
                }
            }

            if (m_on_complete) {
                m_on_complete();
            }
        });

        if (m_on_progress) {
            m_on_progress();
        }

        return this->shared_from_this();
    }

    std::shared_ptr<response_task<T>> progress(const on_progress& cb) {
        m_on_progress = cb;
        return this->shared_from_this();
    }

    std::shared_ptr<response_task<T>> success(const on_success<T>& cb) {
        m_on_success = cb;
        return this->shared_from_this();
    }

    std::shared_ptr<response_task<T>> error(const on_error<T>& cb) {
        m_on_error = cb;
        return this->shared_from_this();
    }

    std::shared_ptr<response_task<T>> complete(const on_complete& cb) {
        m_on_complete = cb;
        return this->shared_from_this();
    }

    httb::request get_request() const {
        return m_request;
    }

    boost::asio::io_context& handle() {
        return m_ctx;
    }

protected:
    virtual T value_from_json(const nlohmann::json& j) {
        return j.get<T>();
    }

private:
    httb::client client;
    boost::asio::io_context m_ctx;
    httb::request m_request;
    on_progress m_on_progress;
    on_success<T> m_on_success;
    on_error<T> m_on_error;
    on_complete m_on_complete;
};

template<typename Source, typename T>
class convertible_response_task : public response_task<T> {
public:
    convertible_response_task(httb::request&& req, map_func_t<Source, T> mapper)
        : response_task<T>(std::move(req)),
          m_mapper(std::move(mapper)) {
    }

protected:
    T value_from_json(const nlohmann::json& j) {
        return m_mapper(j.get<Source>());
    }

private:
    map_func_t<Source, T> m_mapper;
};

template<typename A, typename B>
class pair_task {
public:
    pair_task(task_ptr<A> task_a, task_ptr<B> task_b)
        : resp_a(std::move(task_a)), resp_b(std::move(task_b)) {
    }

    void execute() {
        boost::asio::io_context ctx(2);
        resp_a->execute(ctx);
        resp_b->execute(ctx);

        ctx.run();
    }

private:
    task_ptr<A> resp_a;
    task_ptr<B> resp_b;
};

} // namespace net
} // namespace minter

#endif // MINTER_BASE_REPOSITORY_H
