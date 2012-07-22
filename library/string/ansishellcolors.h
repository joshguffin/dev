#ifndef ansishellcolors_h_INCLUDED
#define ansishellcolors_h_INCLUDED

#include "includes/headermacros.h"

namespace StringLib {

const std::string EscapeStartPre("\033[");
const std::string EscapeStartPost("m");
const std::string EscapeDisableColors("\033[0m");

struct Name
{
   enum { FieldsMacro
};


class ColorWrapper
{

public:

   IMPLEMENT_ACCESSOR(const std::string& , string);


private:

   std::string string_;
};

inline std::ostream&
operator<<(std::ostream& os, const ColorWrapper& str)
{

}

\033[01;38;5;160m
Black   30 40
Red     31 41
Green   32 42
Yellow  33 43
Blue    34 44
Magenta 35 45
Cyan    36 46
White   37 47

} // end of namespace StringLib

#endif // ansishellcolors_h_INCLUDED
