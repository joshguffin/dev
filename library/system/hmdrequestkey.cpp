#include "system/common.h"
#include "system/hmdrequestkey.h"

namespace SystemLib {

HmdRequestKey::HmdRequestKey(const std::string& symbol)
{
   contract_.symbol   = symbol;
   contract_.secType  = "STK";
   contract_.exchange = "SMART";
   contract_.currency = "USD";
}

size_t
hash_value(const HmdRequestKey& key)
{
   std::size_t seed = 0;

   boost::hash<std::string> stringHash;

   const TwsApi::Contract& contract = key.contract();

   boost::hash_combine(seed, stringHash(contract.symbol));
   boost::hash_combine(seed, stringHash(contract.secType));
   boost::hash_combine(seed, stringHash(contract.exchange));
   boost::hash_combine(seed, stringHash(contract.currency));

   return seed;
}

bool
HmdRequestKey::operator==(const HmdRequestKey& key) const
{
   return key.contract_ == contract_;
}

std::ostream&
operator<<(std::ostream& os, const HmdRequestKey& key)
{
   return os << key.contract();
}

} // end of namespace SystemLib
