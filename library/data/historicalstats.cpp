#include "system/common.h"
#include "data/historicalstats.h"

namespace DataLib {

HistoricalStats::HistoricalStats()
   : hi13wk_(-1.0)
   , hi26wk_(-1.0)
   , hi52wk_(-1.0)
   , lo13wk_(-1.0)
   , lo26wk_(-1.0)
   , lo52wk_(-1.0)
   , averageVolume_(-1)
{}

bool
HistoricalStats::valid() const
{
   return (hi13wk_ >= 0.0 &&
           hi26wk_ >= 0.0 &&
           hi52wk_ >= 0.0 &&
           lo13wk_ >= 0.0 &&
           lo26wk_ >= 0.0 &&
           lo52wk_ >= 0.0 &&
           averageVolume_ >= 0);
}

} // end of namespace DataLib

