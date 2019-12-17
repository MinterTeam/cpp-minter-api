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
