#include "system/common.h"
#include "data/last.h"

namespace DataLib {

Last::Last()
   : price_(-1.0)
   , size_(-1)
   , time_(-1)
{}

Last::Last(double price, int size, time_t time)
   : price_(price)
   , size_(size)
   , time_(time)
{}

bool
Last::valid() const
{
   return price_ > 0.0 && size_ > -1 && time_ > -1;
}

void
Last::setTime(const std::string& timestamp)
{
   cout << "Last: time is " << timestamp << endl;
}

} // end of namespace DataLib
