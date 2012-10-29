#ifndef system_log_ch_INCLUDED
#define system_log_ch_INCLUDED

#include "system/timer.h"
#include <stdlib.h>

namespace SystemLib {

template <typename T>
inline Log&
operator<<(Log& log, const T& value)
{
   if (log.current_ >= log.filter_)
      return log;

   bool fileOpen = log.file_.is_open();

   if (fileOpen)
      log.write(log.file_, value);

   if (log.requiresConsoleDisplay(fileOpen))
      log.write(cout, value);

   return log;
}

template <>
inline Log&
operator<<(Log& log, const Log::EndMessage&)
{
   bool fatal = log.current_ == Log::Level::Fatal;
   bool flush = log.fileFlushing_ || fatal;
   
   if (fatal)
      log << " (fatal!)";

   log << '\n';

   if (flush) {
      log.file_ << std::flush;
    
      if (log.requiresConsoleDisplay(log.file_.is_open()))
         cout << std::flush;
   }

   if (fatal)
      abort();

   log.beginningOfLine_ = true;
   return log;
}

template <typename T>
void
Log::write(std::ostream& os, const T& item)
{
   if (beginningOfLine_) {
      if (millisecondResolution_)
         os << MillisecondPrecisionTime() << ' ';
      else
         os << SecondPrecisionTime() << ' ';

      beginningOfLine_ = false;
   }

   os << item;
}


} // end of namespace SystemLib

#endif // system_log_ch_INCLUDED
