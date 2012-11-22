#include "marketdatastore.h"
#include <boost/functional/hash.hpp>

size_t hash_value(const TwsApi::Contract& contract)
{
   boost::hash<std::string> stringHash;

   size_t h = 0;
   boost::hash_combine(h, stringHash(contract.symbol));
   boost::hash_combine(h, stringHash(contract.secType));
   boost::hash_combine(h, stringHash(contract.exchange));
   boost::hash_combine(h, stringHash(contract.currency));
   return h;
}


