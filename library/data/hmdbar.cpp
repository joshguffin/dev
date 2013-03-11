#include "system/common.h"
#include "data/hmdbar.h"

namespace DataLib {

HmdBar::HmdBar(time_t date,
               double open,
               double high,
               double low,
               double close,
               int volume,
               int barcount,
               double WAP,
               bool hasGaps)
   : date_(date)
   , open_(open)
   , high_(high)
   , low_(low)
   , close_(close)
   , volume_(volume)
   , barcount_(barcount)
   , WAP_(WAP)
   , hasGaps_(hasGaps)
{}

std::ostream&
operator<<(std::ostream& os, const HmdBar& data)
{
   os << data.date()
      << ' ' << data.open()
      << ' ' << data.high()
      << ' ' << data.low()
      << ' ' << data.close()
      << ' ' << data.volume()
      << ' ' << data.barcount()
      << ' ' << data.WAP()
      << ' ' << data.hasGaps();
   return os;
}

} // end of namespace DataLib
