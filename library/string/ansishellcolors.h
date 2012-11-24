#ifndef string_ansishellcolors_h_INCLUDED
#define string_ansishellcolors_h_INCLUDED

#include <string>

namespace StringLib {

#define CREATE_COLOR(name, sequence) \
   std::ostream& name(std::ostream& os) { os << std::string("\033[") << std::string(#sequence); return os; }

CREATE_COLOR(resetColor , 0m);
CREATE_COLOR(bold       , 1m);
CREATE_COLOR(black      , 30m);
CREATE_COLOR(red        , 31m);
CREATE_COLOR(green      , 32m);
CREATE_COLOR(yellow     , 33m);
CREATE_COLOR(blue       , 34m);
CREATE_COLOR(magenta    , 35m);
CREATE_COLOR(cyan       , 36m);
CREATE_COLOR(white      , 37m);
CREATE_COLOR(empty      , 1m);

#undef CREATE_COLOR

} // end of namespace StringLib

#endif // string_ansishellcolors_h_INCLUDED
