#ifndef timer_h_INCLUDED
#define timer_h_INCLUDED

#include <ctime>

namespace boost { namespace posix_time {
   class ptime;
}}

namespace SystemLib {

   const char* SecondPrecisionTime();
   const char* MicrosecondPrecisionTime();
   const char* MillisecondPrecisionTime();
   const char* yyyymmddString();
   int         yyyymmdd();

   boost::posix_time::ptime midnight();
   boost::posix_time::ptime midnightTomorrow();

   time_t to_time_t(const boost::posix_time::ptime&);

} // end of namespace SystemLib


#endif // timer_h_INCLUDED

