#include "timer.h"

#include <boost/date_time/posix_time/posix_time_types.hpp>
#include <boost/date_time/posix_time/time_formatters.hpp>
#include <stdio.h>

namespace SystemLib {

using namespace boost::posix_time;

const char*
MillisecondPrecisionTime()
{
   ptime time        = microsec_clock::local_time();
   time_duration tod = time.time_of_day();

   static char buffer[13];

   sprintf(&buffer[0],
           "%02d:%02d:%02d.%03ld",
           tod.hours(),
           tod.minutes(),
           tod.seconds(),
           tod.fractional_seconds() / 1000);

   return buffer;
}

const char*
MicrosecondPrecisionTime()
{
   ptime time        = microsec_clock::local_time();
   time_duration tod = time.time_of_day();

   static char buffer[16];

   sprintf(&buffer[0],
           "%02d:%02d:%02d.%06ld",
           tod.hours(),
           tod.minutes(),
           tod.seconds(),
           tod.fractional_seconds());

   return buffer;
}

const char*
SecondPrecisionTime()
{
   time_t now = time(NULL);
   struct tm timeval;
   localtime_r(&now, &timeval);

   static char buffer[9];
   sprintf(buffer, "%02d:%02d:%02d", timeval.tm_hour, timeval.tm_min, timeval.tm_sec);

   return buffer;
}

const char*
YYYYMMDD()
{
   time_t now = time(NULL);
   struct tm timeval;
   localtime_r(&now, &timeval);
   static char buffer[9];
   sprintf(buffer, "%d%02d%02d", timeval.tm_year, timeval.tm_mon, timeval.tm_mday);

   return buffer;
}

} // end of namespace SystemLib
