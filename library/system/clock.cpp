#include "clock.h"

#include <boost/date_time/posix_time/posix_time_types.hpp>
#include <boost/date_time/posix_time/time_formatters.hpp>
#include <stdio.h>
/*

namespace SystemLib {

using namespace boost::posix_time;
using namespace boost::gregorian;

Clock&
Clock::Instance()
{
   static Clock clock;
   return clock;
}

Clock::Clock()
   : trueStartup_(microsec_clock::local_time())
   , adjustmentExists_(false)
{
   readAdjustmentFile();
   timeAdjustment();
}

void
Clock::readAdjustmentFile()
{
   ptime now = microsec_clock::local_time();

   std::string fakeDateString = "20110102";
   std::string fakeTimeString = "12:30:02";

   time_duration duration = duration_from_string(fakeTimeString);

   fakeStartup_  = fakeDate(fakeDateString);
   fakeStartup_ += fakeTime(fakeTimeString);
}

Clock::TimeStamp
Clock::fakeDate(const std::string& date)
{

   bool invalidFakeTime
   int yyyymmdd = atoi(date.c_str());

   int days = yyyymmdd % 100;
   yyyymmdd -= days;
   yyyymmdd /= 100;

   int months = yyyymmdd % 100;
   yyyymmdd -= months;
   yyyymmdd /= 100;

   int years = yyyymmdd;

   return ptime(date(years, months, days));
}

void
Clock::timeAdjustment()
{
   now_ = microsec_clock::local_time();

   if (adjustmentExists_) {

      // set the date
      static ptime epoch(date(1970,1,1));

      now_ =
      time_duration duration = time - epoch;


      //
      int hours   = 12;
      int minutes = 5;
      int seconds = 3;
      Duration adjusted(hours, minutes, seconds);
      now_ -= adjusted;
   }

   time_ = ToTimeT(now_);
}

const char*
Clock::MillisecondPrecisionTimestamp()
{
   ptime now = microsec_clock::local_time();
   time_duration tod = now.time_of_day();

   double timestamp = to_fractional_timestamp(now);

   static char buffer[14];
   sprintf(&buffer[0], "%.3lf", timestamp);

   return buffer;
}

const char*
Clock::MicrosecondPrecisionTimestamp()
{
   ptime now = microsec_clock::local_time();
   time_duration tod = now.time_of_day();

   double timestamp = to_fractional_timestamp(now);

   static char buffer[17];
   sprintf(&buffer[0], "%.6lf", timestamp);

   return buffer;
}

const char*
Clock::MillisecondPrecisionTime()
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
Clock::MicrosecondPrecisionTime()
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
Clock::SecondPrecisionTime()
{
   ptime now = second_clock::local_time();
   time_duration tod = now.time_of_day();

   static char buffer[9];
   sprintf(buffer, "%02d:%02d:%02d", tod.hours(), tod.minutes(), tod.seconds());

   return buffer;
}

std::string
Clock::yyyymmddString()
{
   ptime now  = second_clock::local_time();
   date today = now.date();

   int year  = static_cast<int>(today.year());
   int month = static_cast<int>(today.month());
   int day   = static_cast<int>(today.day());

   static char buffer[9];
   sprintf(buffer, "%d%02d%02d", year, month, day);

   return std::string(buffer);
}

int
Clock::YYYYMMDD()
{
   ptime now  = second_clock::local_time();
   date today = now.date();

   int yyyymmdd_value;
   yyyymmdd_value  = today.day();
   yyyymmdd_value += today.month() * 100;
   yyyymmdd_value += today.year()  * 10000;

   return yyyymmdd_value;
}

time_t
Clock::ToTimeT(const TimeStamp& time)
{
   static ptime epoch(date(1970,1,1));
   time_duration duration = time - epoch;
   return static_cast<time_t>(duration.total_seconds());
}

double
Clock::ToFractionalTimestamp(const TimeStamp& time)
{
   static ptime epoch(date(1970,1,1));
   time_duration duration = time - epoch;
   return static_cast<double>(duration.total_microseconds()) / 1E6;
}

timeval
Clock::ToTimeval(const Duration& length)
{
   struct timeval tv;

   tv.tv_sec  = length.total_seconds();
   tv.tv_usec = length.total_microseconds() - 1000000L * tv.tv_sec;

   return tv;
}

Clock::TimeStamp
Clock::FromFractionalTimestamp(double timestamp)
{
   static ptime epoch(date(1970,1,1));
   return epoch + microseconds(timestamp * 1E6);
}

Clock::TimeStamp
Clock::Midnight()
{
   ptime now  = second_clock::local_time();
   date today = now.date();

   ptime  today_midnight(today);
   return today_midnight;
}

Clock::TimeStamp
Clock::MidnightTomorrow()
{
   ptime now     = second_clock::local_time();
   date today    = now.date();
   date tomorrow = today + days(1);

   ptime  tomorrow_midnight(tomorrow);
   return tomorrow_midnight;
}

} // end of namespace SystemLib
*/
