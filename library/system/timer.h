#ifndef timer_h_INCLUDED
#define timer_h_INCLUDED

#include <ctime>
#include <sys/time.h>

namespace boost { namespace posix_time {
   class ptime;
   class time_duration;
}}

namespace SystemLib {

   const char* SecondPrecisionTime();
   const char* MicrosecondPrecisionTime();
   const char* MillisecondPrecisionTime();
   const char* MillisecondPrecisionTimestamp();
   const char* yyyymmddString();
   int         yyyymmdd();

   boost::posix_time::ptime midnight();
   boost::posix_time::ptime midnightTomorrow();

   time_t  to_time_t (const boost::posix_time::ptime&);
   timeval to_timeval(const boost::posix_time::time_duration&);

   // convert from fractional timestamp to ptime (microsecond resolution)
   double to_fractional_timestamp(const boost::posix_time::ptime& time);
   boost::posix_time::ptime from_fractional_timestamp(double);

} // end of namespace SystemLib


#endif // timer_h_INCLUDED

