#ifndef twsapi_stream_h_INCLUDED
#define twsapi_stream_h_INCLUDED

namespace TwsApi {

inline std::ostream&
operator<<(std::ostream& os, const Contract& contract)
{
   os << contract.conId
      << ' ' << contract.symbol
      << ' ' << contract.secType
      << ' ' << contract.expiry
      << ' ' << contract.strike
      << ' ' << contract.right
      << ' ' << contract.multiplier
      << ' ' << contract.exchange
      << ' ' << contract.primaryExchange
      << ' ' << contract.currency
      << ' ' << contract.localSymbol
      << ' ' << contract.includeExpired
      << ' ' << contract.secIdType
      << ' ' << contract.secId;
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

} // end of namespace TwsApi

#endif // twsapi_stream_h_INCLUDED
