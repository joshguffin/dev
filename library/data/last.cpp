#include "system/common.h"
#include "data/last.h"

#include <cstdlib>

namespace DataLib {

Last::Last()
   : price_(-1.0)
   , size_(-1)
   , time_(-1.0)
{}

Last::Last(double price, int size, time_t time)
   : price_(price)
   , size_(size)
   , time_(time)
{}

Last::Last(double price, int size, double time)
   : price_(price)
   , size_(size)
   , time_(time)
{}

bool
Last::valid() const
{
   return price_ > 0.0 && size_ > -1  && time_ > 0.0;
}

// possibly fractional timestamp
void
Last::setTime(const std::string& timestamp)
{
   char * test = NULL;
   double val = strtod(timestamp.c_str(), &test);
   if (test)
      time_ = val;
}

} // end of namespace DataLib
