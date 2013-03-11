#include "timer.h"

#include <boost/date_time/posix_time/posix_time_types.hpp>
#include <boost/date_time/posix_time/time_formatters.hpp>
#include <stdio.h>

namespace SystemLib {

using namespace boost::posix_time;
using namespace boost::gregorian;

const char*
MillisecondPrecisionTimestamp()
{
   ptime now = microsec_clock::local_time();
   time_duration tod = now.time_of_day();

   double timestamp = to_fractional_timestamp(now);

   static char buffer[14];
   sprintf(&buffer[0], "%.3lf", timestamp);

   return buffer;
}

const char*
MicrosecondPrecisionTimestamp()
{
   ptime now = microsec_clock::local_time();
   time_duration tod = now.time_of_day();

   double timestamp = to_fractional_timestamp(now);

   static char buffer[17];
   sprintf(&buffer[0], "%.6lf", timestamp);

   return buffer;
}

const char*
MillisecondPrecisionTime()
{
   ptime now = microsec_clock::local_time();
   time_duration tod = now.time_of_day();

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
   ptime now = microsec_clock::local_time();
   time_duration tod = now.time_of_day();

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
   ptime now = second_clock::local_time();
   time_duration tod = now.time_of_day();

   static char buffer[9];
   sprintf(buffer, "%02d:%02d:%02d", tod.hours(), tod.minutes(), tod.seconds());

   return buffer;
}

const char*
yyyymmddString()
{
   ptime now  = second_clock::local_time();
   date today = now.date();

   int year  = static_cast<int>(today.year());
   int month = static_cast<int>(today.month());
   int day   = static_cast<int>(today.day());

   static char buffer[9];
   sprintf(buffer, "%d%02d%02d", year, month, day);

   return buffer;
}

int
yyyymmdd()
{
   ptime now  = second_clock::local_time();
   date today = now.date();

   int yyyymmdd_value = today.day();
   yyyymmdd_value += today.month() * 100;
   yyyymmdd_value += today.year()  * 10000;

   return yyyymmdd_value;
}

time_t
to_time_t(const boost::posix_time::ptime& time)
{
   static ptime epoch(date(1970,1,1));
   time_duration duration = time - epoch;
   return static_cast<time_t>(duration.total_seconds());
}

double
to_fractional_timestamp(const boost::posix_time::ptime& time)
{
   static ptime epoch(date(1970,1,1));
   time_duration duration = time - epoch;
   return static_cast<double>(duration.total_microseconds()) / 1E6;
}

timeval
to_timeval(const boost::posix_time::time_duration& length)
{
   struct timeval tv;

   tv.tv_sec  = length.total_seconds();
   tv.tv_usec = length.total_microseconds() - 1000000L * tv.tv_sec;

   return tv;
}

boost::posix_time::ptime
from_fractional_timestamp(double timestamp)
{
   static ptime epoch(date(1970,1,1));
   return epoch + microseconds(timestamp * 1E6);
}

boost::posix_time::ptime
midnight()
{
   ptime now  = second_clock::local_time();
   date today = now.date();

   ptime  today_midnight(today);
   return today_midnight;
}

boost::posix_time::ptime
midnightTomorrow()
{
   ptime now     = second_clock::local_time();
   date today    = now.date();
   date tomorrow = today + days(1);

   ptime  tomorrow_midnight(tomorrow);
   return tomorrow_midnight;
}

} // end of namespace SystemLib
