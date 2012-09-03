#include "util/commandline.h"

namespace UtilLib {

CommandLine&
CommandLine::Instance()
{
   static CommandLine instance;
   return instance;
}

void
CommandLine::Init(int argc, char** argv)
{
   Instance().arguments_ = Arguments(argv, argv + argc);
}

const std::string&
CommandLine::Find(const std::string& flag)
{
   static std::string empty;

   Arguments::const_iterator it  = Instance().arguments_.begin();
   Arguments::const_iterator end = Instance().arguments_.end();

   for (; it != end; ++it) {
      if (*it != flag) 
         continue;
      ++it;
      return (it == end ? empty : *it);
   }

   return empty;
}

bool
CommandLine::Present(const std::string& flag)
{
   Arguments::const_iterator it  = Instance().arguments_.begin();
   Arguments::const_iterator end = Instance().arguments_.end();

   for (; it != end; ++it) {
      if (*it == flag) 
         break;
   }

   return it != end;
}

} // end of namespace UtilLib
