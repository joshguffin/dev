#ifndef system_log_h_INCLUDED
#define system_log_h_INCLUDED

#define LOG   SystemLib::Log::Instance()
#define endm  SystemLib::Log::EndMsg;

#define FATAL SystemLib::Log::Fatal
#define ERROR SystemLib::Log::Error
#define WARN  SystemLib::Log::Warning
#define INFO  SystemLib::Log::Info

#include "include/headermacros.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

using std::cout;
using std::endl;

namespace SystemLib {

class Log
{

public:

   template <typename T> friend Log& operator<<(Log&, const T&);

#define FieldsMacro(F) \
   F(Fatal) \
   F(Warning) \
   F(Normal) \
   F(Info) \
   F(Debug)
   IMPLEMENT_COMPACT_ENUM_WRAPPER_IN_CLASS(Level, FieldsMacro);
#undef FieldsMacro

   class EndMessage{};
   static EndMessage EndMsg;

public:

   static Log& Instance();
   Log& operator()(Level::Type); // use as log(WARN) << "Message" << endl;

private:

   Log();
   bool requiresConsoleDisplay(bool) const;

private:

   bool fileFlushing_;

   Level::Type filter_;
   Level::Type current_;
   std::fstream file_;
};

template <typename T>
inline Log&
operator<<(Log& log, const T& value)
{
   if (log.current_ >= log.filter_)
      return log;

   bool fileOpen = log.file_.is_open();

   if (fileOpen)
      log.file_ << value;

   if (log.requiresConsoleDisplay(fileOpen))
      cout << value;

   return log;
}

template <>
Log&
operator<<(Log& log, const Log::EndMessage&)
{
   log << '\n';
   cout << std::flush;
   if (log.fileFlushing_)
      log.file_ << std::flush;

   return log;
}

} // end of namespace SystemLib

#endif // log_h_INCLUDED

