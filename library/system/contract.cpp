#include "system/common.h"
#include "system/contract.h"
#include "string/stringtable.h"

namespace SystemLib {

// specify a contract for a single security
Contract::Contract(const std::string& symbol,
                   const std::string& security)
   : symbol_(symbol)
   , exchange_("SMART")
   , securityType_(Security::FromString(security))
{
}

Contract::Contract(const TwsApi::ContractDetails& details)
   : conid_       (details.summary.conId)
   , symbol_      (details.summary.symbol)
   , currency_    (details.summary.currency)
   , primaryExchange_(details.summary.primaryExchange)
   , securityType_(Security::FromString(details.summary.secType))
{

   StringLib::StringTable info;
#define PRINT(x) info << #x << details.x << StringLib::StringTable::endr;
   PRINT(summary.conId);
   PRINT(summary.symbol);
   info << "Type" << Security::ToString(securityType_) << StringLib::StringTable::endr;
   PRINT(summary.currency);
   PRINT(summary.primaryExchange);
   PRINT(marketName);
   PRINT(tradingClass);
   PRINT(minTick);
   PRINT(orderTypes);
   PRINT(validExchanges);
   PRINT(priceMagnifier);
   PRINT(underConId);
   PRINT(longName);
   PRINT(industry);
   PRINT(category);
   PRINT(subcategory);
   PRINT(timeZoneId);
   PRINT(tradingHours);
   PRINT(liquidHours);
#undef PRINT

   cout << info << endl;
}

} // end of namespace SystemLib
