#ifndef twsapi_stream_h_INCLUDED
#define twsapi_stream_h_INCLUDED

namespace TwsApi {

inline std::ostream&
operator<<(std::ostream& os, const Contract& contract)
{
   os << contract.conId
      << " " << contract.symbol
      << " " << contract.secType
      << " exp=" << contract.expiry
      << " " << contract.strike
      << " " << contract.right
      << " " << contract.multiplier
      << " " << contract.exchange
      << " " << contract.primaryExchange
      << " " << contract.currency
      << " " << contract.localSymbol
      << " " << contract.includeExpired
      << " " << contract.secIdType
      << " " << contract.secId;
   return os;
}

inline std::ostream&
operator<<(std::ostream& os, const ContractDetails& details)
{
   os << details.summary
      << ' ' << details.marketName
      << ' ' << details.tradingClass
      << ' ' << details.minTick
      << ' ' << details.orderTypes
      << ' ' << details.validExchanges
      << ' ' << details.priceMagnifier
      << ' ' << details.underConId
      << ' ' << details.longName
      << ' ' << details.contractMonth
      << ' ' << details.industry
      << ' ' << details.category
      << ' ' << details.subcategory
      << ' ' << details.timeZoneId
      << ' ' << details.tradingHours
      << ' ' << details.liquidHours;
   return os;
}

inline std::ostream&
operator<<(std::ostream& os, const OrderState& state)
{
   os << state.status
      << ' ' << state.warningText
      << ' ' << state.commission;

   return os;
}

#define PRINT(x) info << #x << x << StringLib::StringTable::endr;
inline std::ostream&
operator<<(std::ostream& os, const Order& order)
{
   StringLib::StringTable info;
   PRINT(order.orderId);
   PRINT(order.clientId);
   PRINT(order.permId);
   PRINT(order.action);
   PRINT(order.totalQuantity);
   PRINT(order.orderType);
   PRINT(order.lmtPrice);
   PRINT(order.auxPrice);
   PRINT(order.tif);
   PRINT(order.ocaGroup);
   PRINT(order.ocaType);
   PRINT(order.orderRef);
   PRINT(order.transmit);
   PRINT(order.parentId);
   PRINT(order.blockOrder);
   PRINT(order.sweepToFill);
   PRINT(order.displaySize);
   PRINT(order.triggerMethod);
   PRINT(order.outsideRth);
   PRINT(order.hidden);
   PRINT(order.goodAfterTime);
   PRINT(order.goodTillDate);
   PRINT(order.rule80A);
   PRINT(order.allOrNone);
   PRINT(order.minQty);
   PRINT(order.percentOffset);
   PRINT(order.overridePercentageConstraints);
   PRINT(order.trailStopPrice);;

   os << info;
   return os;
}
#undef PRINT

} // end of namespace TwsApi

#endif // twsapi_stream_h_INCLUDED
