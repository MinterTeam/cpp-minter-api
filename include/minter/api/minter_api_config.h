/*!
 * minter_tx.
 * minter_tx_core.h
 *
 * \date 2019
 * \author Eduard Maximovich (edward.vstock@gmail.com)
 * \link   https://github.com/edwardstock
 */

#ifndef MINTER_TX_MINTER_TX_CORE_H
#define MINTER_TX_MINTER_TX_CORE_H

/* #undef MINTER_TX_EXPORTING */
/* #undef MINTER_EXPORT_SHARED */

#define MINTER_CHAIN_ID minter::chain_id::mainnet
#define MINTER_EXPLORER_API_V "v2"
#define MINTER_GATE_API_V "v2"
#define MINTER_DEFAULT_COIN "BIP"
#define MINTER_EXPLORER_API "https://explorer-api.minter.network/api/v2/"
#define MINTER_EXPLORER_FRONT "https://explorer.minter.network"
#define MINTER_EXPLORER_STATIC_URL "https://explorer-static.minter.network"
#define MINTER_GATE_API "https://gate-api.apps.minter.network/api/v2/"
#define MINTER_WS_URL "wss://explorer-rtm.apps.minter.network/connection/websocket"
#define MINTER_COIN_AVATAR_URL "https://my.apps.minter.network/api/v1/avatar/by/coin/"
#define MINTER_ADDRESS_AVATAR_URL "https://my.apps.minter.network/api/v1/avatar/by/address/"

#define HAVE_CXX_OPTIONAL

#ifdef MINTER_EXPORT_SHARED
#ifdef MINTER_TX_EXPORTING
#if _MSC_VER
#define MINTER_TX_API __declspec(dllexport)
#else
#define MINTER_TX_API __attribute__((visibility("default")))
#endif
#else
#if _MSC_VER
#define MINTER_TX_API __declspec(dllimport)
#else
#define MINTER_TX_API
#endif
#endif
#else
#define MINTER_TX_API
#endif // MINTER_EXPORT_SHARED

#endif //MINTER_TX_MINTER_TX_CORE_H
