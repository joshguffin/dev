#include "system/common.h"
#include "data/bidask.h"

namespace DataLib {

BidAsk::BidAsk()
   : bid_(-1.0)
   , ask_(-1.0)
   , bidSize_(-1)
   , askSize_(-1)
{}

BidAsk::BidAsk(double bid, double ask, int bidSize, int askSize)
   : bid_(bid)
   , ask_(ask)
   , bidSize_(bidSize)
   , askSize_(askSize)
{}

bool
BidAsk::valid() const
{
   return bid_ > 0.0 && ask_ > 0.0 && bidSize_ > 0 && askSize_ > 0;
}

} // end of namespace DataLib
