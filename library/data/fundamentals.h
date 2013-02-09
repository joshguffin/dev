#ifndef data_fundamentals_h_INCLUDED
#define data_fundamentals_h_INCLUDED

namespace DataLib {

class Fundamentals
{

public:

   IMPLEMENT_ACCESSORS(const std::string& , vals);

private:

   std::string vals_;
};

} // end of namespace DataLib

#endif // data_fundamentals_h_INCLUDED
