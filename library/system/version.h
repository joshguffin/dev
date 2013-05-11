#ifndef system_version_h_INCLUDED
#define system_version_h_INCLUDED

#include <iostream>
#include <sstream>

/* Implementation: create a file called version.cpp in the application directory
 * as below and use the macro PRINT_BUILD_STRING somewhere, possibly in main().

// ----------------------------- Begin version.cpp -----------------------------
#include "system/version.h"

CREATE_BUILD_STRING
// ------------------------------ End version.cpp ------------------------------
*/

namespace SystemLib {
namespace BuildString {

std::string Build;

} // end of namespace BuildString
} // end of namespace SystemLib

#ifdef __GIT_VERSION
#define GIT_VERSIONING_STREAM __TIME__ << ", git version " << __GIT_VERSION
#else
#define GIT_VERSIONING_STREAM __TIME__
#endif

#define CREATE_BUILD_STRING \
   std::string
   std::stringstream ss;    \
   ss << "Built " << __DATE__ << " (" << GIT_VERSIONING_STREAM << ")"; \
   SystemLib::BuildString::Build = ss.str();

#define PRINT_BUILD_STRING \
   std::cout << SystemLib::BuildString::Build << std::endl;

#endif // system_version_h_INCLUDED
