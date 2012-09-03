#ifndef util_environment_h_INCLUDED
#define util_environment_h_INCLUDED

#include <stdlib.h>

class Environment
{
   static std::string Get(const std::string& var)
   { return std::string(getenv(var.c_str())); }

   static std::string DataArea()
   { return Environment::Get("DATA_AREA"); }
};

#endif // util_environment_h_INCLUDED
