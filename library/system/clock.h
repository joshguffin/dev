#ifndef system_clock_h_INCLUDED
#define system_clock_h_INCLUDED

/*

#include <boost/date_time/posix_time/posix_time_types.hpp>
#include <boost/date_time/posix_time/time_formatters.hpp>

class Clock
{
public:

   typedef boost::posix_time::ptime    TimeStamp;
   typedef boost::posix_time::duration Duration;

   IMPLEMENT_ACCESSOR(const TimeStamp& , now);
   IMPLEMENT_ACCESSOR(time_t           , time);

public:

   //
   static const char* SecondPrecisionTime();
   static const char* MicrosecondPrecisionTime();
   static const char* MillisecondPrecisionTime();
   static const char* MillisecondPrecisionTimestamp();

   // convert to/from formats
   static time_t  ToTimeT(const TimeStamp&);
   static timeval ToTimeval(const TimeStamp&);
   static double  ToFractionalTimestamp(const TimeStamp&);

   static TimeStamp FromTimeT(time_t);
   static TimeStamp FromTimeval(const timeval&);
   static TimeStamp FromFractionalTimestamp(double);

   // Convenience accessors
   static Timestamp Midnight();
   static Timestamp MidnightTomorrow();

   static std::string YYYYMMDD();
   static int         YYYYMMDD();

private:

   boost::posix_time::ptime trueStartup_;
   boost::posix_time::ptime fakeStartup_;
   boost::posix_time::ptime now_;
   time_t time_;

   bool adjustmentExists_;
   boost::posix_time::duration offset_;
};

*/

#endif // system_clock_h_INCLUDED
