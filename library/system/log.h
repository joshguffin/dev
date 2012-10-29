#ifndef system_log_h_INCLUDED
#define system_log_h_INCLUDED

#define LOG   SystemLib::Log::Instance()
#define endm  SystemLib::Log::EndMsg;

#define FATAL SystemLib::Log::Level::Fatal
#define ERROR SystemLib::Log::Level::Error
#define WARN  SystemLib::Log::Level::Warning
#define INFO  SystemLib::Log::Level::Info

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

   // log levels in decreasing severity, increasing verbosity
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

   IMPLEMENT_ACCESSORS(bool , millisecondResolution);

private:

   Log();
   bool requiresConsoleDisplay(bool) const;

   template <typename T>
   void write(std::ostream&, const T&);

private:

   bool fileFlushing_;
   bool beginningOfLine_;
   bool millisecondResolution_;

   Level::Type filter_;
   Level::Type current_;
   std::ofstream file_;
};

} // end of namespace SystemLib

#include "system/log.ch"

#endif // log_h_INCLUDED

