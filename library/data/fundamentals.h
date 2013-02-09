#ifndef data_fundamentals_h_INCLUDED
#define data_fundamentals_h_INCLUDED

#include <iostream>

namespace DataLib {

class Fundamentals
{

public:

   IMPLEMENT_ACCESSORS(const std::string& , vals);

private:

   std::string vals_;
};

inline std::ostream&
operator<<(std::ostream& os, const Fundamentals& data)
{
   return os << data.vals();
}

} // end of namespace DataLib

#endif // data_fundamentals_h_INCLUDED
