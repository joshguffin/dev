#ifndef system_environment_h_INCLUDED
#define system_environment_h_INCLUDED

#include <stdlib.h>
#include <string>

namespace SystemLib { 

struct Environment
{
   static std::string Get(const std::string& var)
   {
      const char* val = getenv(var.c_str());
      if (!val)
         return "";
      return std::string(val);
   }

   static std::string DataArea()
   { return Environment::Get("DATA_AREA"); }

   static std::string DataArea(const std::string& path)
   { return Environment::Get("DATA_AREA") + "/" + path; }
};

} // end of namespace SystemLib

#endif // system_environment_h_INCLUDED
