/*!
 * minter_api.
 * explorer_test.cpp
 *
 * \date 2019
 * \author Eduard Maximovich (edward.vstock@gmail.com)
 * \link   https://github.com/edwardstock
 */

#include <boost/asio/io_context.hpp>
#include <gtest/gtest.h>
#include <minter/api/explorer/repository.h>
#include <minter/api/gate/repository.h>

TEST(Explorer, TxByHash) {
    minter::hash_t hash("Mtd7a9ed0b72543cbf83d54fbfe944c3cad85a1716b54dd07ff02fa43e20885baf");
    namespace exp = minter::explorer;

    exp::repository repo;

    //https://texasnet.explorer-api.minter.network/api/v1/addresses/Mxbdc645ef3c5c00b670b4bf0e7123a8edc033a6cf/transactions?startblock=75725&endblock=75725
    minter::net::task_ptr<exp::result<exp::transaction_item>> tx_get_task;

    tx_get_task = repo.get_transaction(minter::address_t("Mxbdc645ef3c5c00b670b4bf0e7123a8edc033a6cf"), dev::bigint("75725"));

    //    tx_get_task = repo
    tx_get_task
        ->error([](httb::response resp, exp::result<exp::transaction_item> result) {
            if (!result.error.message.empty()) {
                std::cerr << result.error.message << std::endl;
            } else {
                std::cerr << resp.status_message << std::endl;
                std::cerr << resp.get_body() << std::endl;
            }
        })
        ->success([](exp::result<exp::transaction_item> result) {
            auto tx = result.data;
            std::cout << tx.hash << std::endl;
            std::cout << tx.timestamp << std::endl;
            std::cout << tx.block << std::endl;
            std::cout << tx.type << std::endl;
            std::cout << tx.from << std::endl;
            if (tx.type == minter::tx_type_val::send_coin) {
                exp::tx_send_result* sendResult = (exp::tx_send_result*) tx.data.get();
                std::cout << "Send Coin:\n";
                std::cout << "  " << sendResult->coin << std::endl;
                std::cout << "  " << sendResult->to << std::endl;
                std::cout << "  " << sendResult->value << std::endl;
            }
            std::cout << tx.fee << std::endl;
            std::cout << tx.nonce << std::endl;
            std::cout << tx.payload << std::endl;
        });

    tx_get_task->execute();
}

TEST(Explorer, Status) {
    namespace exp = minter::explorer;
    exp::repository exp_repo;

    auto task = exp_repo
                    .get_status()
                    ->error([](httb::response resp, exp::result<exp::net_status> result) {
                        if (!result.error.message.empty()) {
                            std::cerr << result.error.message << std::endl;
                        } else {
                            std::cerr << resp.status_message << std::endl;
                            std::cerr << resp.get_body() << std::endl;
                        }
                    })
                    ->success([](exp::result<exp::net_status> result) {
                        nlohmann::json j = result.data;
                        std::cout << j.dump() << std::endl;
                    });

    task->execute();
}

TEST(Explorer, StatusPage) {
    namespace exp = minter::explorer;
    exp::repository exp_repo;

    auto task = exp_repo
                    .get_status_page()
                    ->error([](httb::response resp, exp::result<exp::net_status_page> result) {
                        if (!result.error.message.empty()) {
                            std::cerr << result.error.message << std::endl;
                        } else {
                            std::cerr << resp.status_message << std::endl;
                            std::cerr << resp.get_body() << std::endl;
                        }
                    })
                    ->success([](exp::result<exp::net_status_page> result) {
                        nlohmann::json j = result.data;
                        std::cout << j.dump() << std::endl;
                    });

    task->execute();
}

TEST(Explorer, GateBalance) {

    namespace exp = minter::explorer;
    namespace gate = minter::gate;

    boost::asio::io_context ctx(2);

    exp::repository exp_repo;
    gate::repository gate_repo;

    minter::address_t address("Mx8b47278483c9bc2918e261fddf2f0357c91d039e");
    auto balance_task = exp_repo
                            .get_balance(address)
                            ->error([](httb::response resp, exp::result<exp::balance_items> result) {
                                if (!result.error.message.empty()) {
                                    std::cerr << result.error.message << std::endl;
                                } else {
                                    std::cerr << resp.status_message << std::endl;
                                    std::cerr << resp.get_body() << std::endl;
                                }
                            })
                            ->success([](exp::result<exp::balance_items> result) {
                                for (const auto& item : result.data.balances) {
                                    std::cout << item.coin << ": " << minter::utils::to_string(item.amount) << std::endl;
                                }
                            });

    auto nonce_task = gate_repo
                          .get_tx_count(address)
                          ->error([](httb::response resp, gate::result<gate::tx_count_value> result) {
                              if (!result.error.log.empty()) {
                                  std::cerr << result.error.log << std::endl;
                              } else {
                                  std::cerr << resp.status_message << std::endl;
                                  std::cerr << resp.get_body() << std::endl;
                              }
                          })
                          ->success([](gate::result<gate::tx_count_value> result) {
                              std::cout << "Nonce: " << result.data.count << std::endl;
                          });

    balance_task->execute(ctx);
    nonce_task->execute(ctx);

    ctx.run();
}
