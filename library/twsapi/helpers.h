#ifndef helpers_h_INCLUDED
#define helpers_h_INCLUDED

namespace TwsApi {

// === Contract helpers ========================================================

#define APPLY_TO_CONTRACT(Macro, C1, C2) \
      Macro(conId            , C1 , C2) && \
      Macro(symbol           , C1 , C2) && \
      Macro(secType          , C1 , C2) && \
      Macro(expiry           , C1 , C2) && \
      Macro(strike           , C1 , C2) && \
      Macro(right            , C1 , C2) && \
      Macro(multiplier       , C1 , C2) && \
      Macro(exchange         , C1 , C2) && \
      Macro(primaryExchange  , C1 , C2) && \
      Macro(currency         , C1 , C2) && \
      Macro(localSymbol      , C1 , C2) && \
      Macro(includeExpired   , C1 , C2) && \
      Macro(secIdType        , C1 , C2) && \
      Macro(secId            , C1 , C2) && \
      Macro(underComp        , C1 , C2) && \
      Macro(comboLegsDescrip , C1 , C2);

#define COMPARE(member, C1, C2) C1.member == C2.member
inline bool
operator==(const Contract& lhs, const Contract& rhs)
{
   return APPLY_TO_CONTRACT(COMPARE, lhs, rhs);
}
#undef COMPARE

#define COMPARE(member, C1, C2) C1.member < C2.member || C1.member == C2.member
inline bool
operator<(const Contract& lhs, const Contract& rhs)
{
   return APPLY_TO_CONTRACT(COMPARE, lhs, rhs);
}
#undef COMPARE
#undef APPLY_TO_CONTRACT

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
