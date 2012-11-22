#ifndef ibwrap_marketdatastore_h_INCLUDED
#define ibwrap_marketdatastore_h_INCLUDED

#include "twsapi/common.h"

#include <boost/unordered_map.hpp>
#include <boost/shared_ptr.hpp>

class MarketData;
typedef boost::shared_ptr<MarketData> MarketDataPtr;

class MarketDataStore
{


   boost::unordered_map<TwsApi::Contract, MarketData> contractToData_;
   boost::unordered_map<unsigned, MarketData> tickToData_;
};

size_t hash_value(const TwsApi::Contract&);

#endif // ibwrap_marketdatastore_h_INCLUDED
