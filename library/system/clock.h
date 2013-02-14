#ifndef system_clock_h_INCLUDED
#define system_clock_h_INCLUDED

#include "system/duration.h"

#include <boost/chrono/clock_string.hpp>
#include <boost/chrono.hpp>

class Clock
{
public:
    typedef Duration                             rep;
    typedef boost::micro                         period;
    typedef boost::chrono::duration<rep, period> duration;
    typedef boost::chrono::time_point<Clock>     time_point;

    static time_point Now()
    {
        timespec ts;
        ::clock_gettime( CLOCK_REALTIME, &ts );

        Duration duros(ts.tv_sec, ts.tv_nsec/1000);
        return time_point(duration(duros));
    }
};

namespace boost { namespace chrono {

template<class CharT>
struct clock_string<Clock, CharT>
{
   static std::basic_string<CharT> name()
   {
      static const CharT u[] =
      { 's', 'y', 's', 't', 'e', 'm', '_', 'c', 'l', 'o', 'c', 'k' };
      static const std::basic_string<CharT> str(u, u + sizeof(u) / sizeof(u[0]));
      return str;
   }

   static std::basic_string<CharT> since()
   {
      static const CharT
         u[] =
         { ' ', 's', 'i', 'n', 'c', 'e', ' ', 'J', 'a', 'n', ' ', '1', ',', ' ', '1', '9', '7', '0' };
      static const std::basic_string<CharT> str(u, u + sizeof(u) / sizeof(u[0]));
      return str;
   }
};

}} // end of namespace boost::chrono

#endif // system_clock_h_INCLUDED
