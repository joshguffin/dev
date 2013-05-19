#ifndef string_ansishellcolors_h_INCLUDED
#define string_ansishellcolors_h_INCLUDED

#include <string>
#include <iostream>
#include <sstream>
#include "base/headermacros.h"

/**
 * Use this class like:
 *
 * using namespace StringLib;
 * cout << Color("Hello world!", Color::Red) << endl;
 *
 */

namespace StringLib {

//==============================================================================
// Color declaration
//==============================================================================

#define Fields(F) \
   F(Black)       \
   F(Red)         \
   F(Green)       \
   F(Yellow)      \
   F(Blue)        \
   F(Magenta)     \
   F(Cyan)        \
   F(White)       \
   F(BoldBlack)   \
   F(BoldRed)     \
   F(BoldGreen)   \
   F(BoldYellow)  \
   F(BoldBlue)    \
   F(BoldMagenta) \
   F(BoldCyan)    \
   F(BoldWhite)

struct Color
{
public:

   friend std::ostream& operator<<(std::ostream&, const Color&);

   IMPLEMENT_ENUM_IMPL(COMPACT, Value, Fields);
   Color(const std::string&, Value);

private:

   std::string value_;
   Value color_;
};

IMPLEMENT_ENUM_PRINT(Color::Value, Color::ToString)

#undef Fields
//==============================================================================
// Color implementation
//==============================================================================

inline
Color::Color(const std::string& value, Value color)
   : value_(value)
   , color_(color)
{
}

inline std::ostream&
operator<<(std::ostream& os, const Color& color)
{
   os << "\e[";

#define HANDLE(Col, Val) \
   case Color::Col: os << Val << "m"; break; \
   case Color::Bold##Col: os << "1;" << Val << "m"; break;

   switch (color.color_) {
      HANDLE(Black   , 30);
      HANDLE(Red     , 31);
      HANDLE(Green   , 32);
      HANDLE(Yellow  , 33);
      HANDLE(Blue    , 34);
      HANDLE(Magenta , 35);
      HANDLE(Cyan    , 36);
      HANDLE(White   , 37);
      default:
      os << "0m";
   }
#undef HANDLE

   return os << color.value_ << "\e[0m";
}

} // end of namespace StringLib

#endif // string_ansishellcolors_h_INCLUDED
