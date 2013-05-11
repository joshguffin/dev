#ifndef helpers_h_INCLUDED
#define helpers_h_INCLUDED

#include "string/stringtable.h"
#include "string/csv.h"

#include <iostream>

namespace TwsApi {

// === Contract helpers ========================================================

inline bool
operator==(const Contract& lhs, const Contract& rhs)
{
   return (lhs.conId           == rhs.conId           &&
           lhs.symbol          == rhs.symbol          &&
           lhs.secType         == rhs.secType         &&
           lhs.expiry          == rhs.expiry          &&
           lhs.strike          == rhs.strike          &&
           lhs.right           == rhs.right           &&
           lhs.multiplier      == rhs.multiplier      &&
           lhs.exchange        == rhs.exchange        &&
           lhs.primaryExchange == rhs.primaryExchange &&
           lhs.currency        == rhs.currency        &&
           lhs.localSymbol     == rhs.localSymbol     &&
           lhs.includeExpired  == rhs.includeExpired  &&
           lhs.secIdType       == rhs.secIdType       &&
           lhs.secId           == rhs.secId);
}

inline bool
operator!=(const Contract& lhs, const Contract& rhs)
{
   return !operator==(lhs, rhs);
}

#define COMPARE(Member)      \
if (lhs.Member < rhs.Member) \
   return true;              \
if (lhs.Member > rhs.Member) \
   return false;

inline bool
operator<(const Contract& lhs, const Contract& rhs)
{
   COMPARE(conId);
   COMPARE(symbol);
   COMPARE(secType);
   COMPARE(expiry);
   COMPARE(strike);
   COMPARE(right);
   COMPARE(multiplier);
   COMPARE(exchange);
   COMPARE(primaryExchange);
   COMPARE(currency);
   COMPARE(localSymbol);
   COMPARE(includeExpired);
   COMPARE(secIdType);
   COMPARE(secId);

   return false;
}
#undef COMPARE

inline void
contractSeparated(StringLib::CSV& csv, const TwsApi::Contract& contract)
{
   csv
      << contract.conId
      << contract.symbol
      << contract.secType
      << contract.expiry
      << contract.strike
      << contract.right
      << contract.multiplier
      << contract.exchange
      << contract.primaryExchange
      << contract.currency
      << contract.localSymbol
      << contract.includeExpired
      << contract.secIdType
      << contract.secId;
}

// appropriate for StringLib::CSV or StringLib::StringTable;
template <typename T>
inline void
contractHeaders(T& stream)
{
   stream
      << "Contract ID"
      << "Symbol"
      << "Security Type"
      << "Expiry"
      << "Strike"
      << "Right"
      << "Multiplier"
      << "Exchange"
      << "Primary Exchange"
      << "Currency"
      << "Local Symbol"
      << "Include Expired"
      << "Security Id Type"
      << "Security Id";
}

// === Order helpers ===========================================================

#define IMPLEMENT_ORDER_OPERATOR(Relation)            \
inline bool                                           \
operator Relation(const Order& lhs, const Order& rhs) \
{                                                     \
   return lhs.orderId Relation lhs.orderId;           \
}

IMPLEMENT_ORDER_OPERATOR(!=)
IMPLEMENT_ORDER_OPERATOR(==)
IMPLEMENT_ORDER_OPERATOR(<=)
IMPLEMENT_ORDER_OPERATOR(>=)
IMPLEMENT_ORDER_OPERATOR(<)
IMPLEMENT_ORDER_OPERATOR(>)
#undef IMPLEMENT_ORDER_OPERATOR

} // end of namespace TwsApi

#endif // helpers_h_INCLUDED
