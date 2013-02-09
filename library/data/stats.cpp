#include "system/common.h"
#include "data/stats.h"

namespace DataLib {

Stats::Stats()
   : high_(-1.0)
   , low_(-1.0)
   , tradeRate_(-1.0)
   , tradeCount_(-1.0)
   , volumeRate_(-1.0)
   , realTimeVolume_(-1.0)
   , volume_(-1)
{}

bool
Stats::valid() const
{
   return (high_       >= 0.0 &&
           low_        >= 0.0 &&
           volume_     >= 0   &&
           tradeRate_  >= 0.0 &&
           tradeCount_ >= 0.0 &&
           volumeRate_ >= 0.0 &&
           realTimeVolume_ >= 0.0);
}

} // end of namespace DataLib
