#ifndef string_ansishellcolors_h_INCLUDED
#define string_ansishellcolors_h_INCLUDED

#include <string>

namespace StringLib {

class ColorWrapper
{

public:

   enum Decorator {
      Black   = 30,
      Red     = 31,
      Green   = 32,
      Yellow  = 33,
      Blue    = 34,
      Magenta = 35,
      Cyan    = 36,
      White   = 37,
   };

public:

   ColorWrapper();

   IMPLEMENT_ACCESSOR(const std::string& , string);
   void clearDecorations() { decorators_ = ""; };

private:

   static const std::string EscapeStartPre;
   static const std::string EscapeStartPost;
   static const std::string EscapeDisableColors;

   std::string decorators_;
   std::string string_;

   bool escaped_;

   friend ColorWrapper& operator<<(ColorWrapper&, const std::string&);
   friend ColorWrapper& operator<<(ColorWrapper&, ColorWrapper::Decorator&);
   friend std::ostream& operator<<(std::ostream&, const ColorWrapper&);
};

inline ColorWrapper&
operator<<(ColorWrapper& cw, const std::string& str)
{
   cw.string_ += str;
   return cw;
}

} // end of namespace StringLib

#endif // string_ansishellcolors_h_INCLUDED
