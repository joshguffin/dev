#include "string/ansishellcolors.h"
#include "string/integertostring.h"

namespace StringLib {

const std::string ColorWrapper::EscapeStartPre("\033[");
const std::string ColorWrapper::EscapeStartPost("m");
const std::string ColorWrapper::EscapeDisableColors("\033[0m");

ColorWrapper::ColorWrapper()
   : escaped_(false)
{}


ColorWrapper&
operator<<(ColorWrapper& cw, ColorWrapper::Decorator& decor)
{
   if (cw.decorators_.empty()) {
      cw.decorators_ += ColorWrapper::EscapeStartPre;
   }
   cw.decorators_ += IntegerToString(decor);

   //\033[01;38;5;160m

   /*
Black   40
Red     41
Green   42
Yellow  43
Blue    44
Magenta 45
Cyan    46
White   47
*/
   return cw;
}

std::ostream&
operator<<(std::ostream& os, const ColorWrapper& cw)
{
   if (cw.decorators_.empty())
      return os << cw.string();

   os << cw.decorators_ << cw.string_ << ColorWrapper::EscapeDisableColors;
   return os;
}


} // end of namespace StringLib
