#include "system/log.h"

namespace SystemLib {

Log::EndMessage Log::EndMsg;

Log&
Log::Instance()
{
   static Log instance;
   return instance;
}

Log&
Log::operator()(Level::Type level)
{
   current_ = level;
   return *this;
}

bool
Log::requiresConsoleDisplay(bool fileOpen) const
{
   return (!fileOpen ||
           current_ != Level::Warning &&
           current_ != Level::Info);
}

Log::Log()
   : fileFlushing_(true)
   , filter_(Level::Unknown)
   , current_(Level::Normal)
{}

} // end of namespace SystemLib
