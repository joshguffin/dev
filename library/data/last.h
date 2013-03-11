#ifndef data_last_h_INCLUDED
#define data_last_h_INCLUDED

#include <boost/date_time/posix_time/posix_time.hpp>
#include <iostream>

namespace DataLib {

class Last
{

public:

   Last();
   Last(double, int, time_t);
   Last(double, int, double);

   IMPLEMENT_ACCESSORS(double , price);
   IMPLEMENT_ACCESSORS(int    , size);
   IMPLEMENT_ACCESSORS(double , time);

   bool valid() const;
   void setTime(const std::string&);

private:

   double price_;
   int    size_;
   double time_;
};

inline std::ostream&
operator<<(std::ostream& os, const Last& data)
{
   return os << data.price() << ' ' << data.size() << ' ' << data.time();
}

inline std::istream&
operator<<(std::istream& is, Last& data)
{
   double px;
   int    sz;
   double timestamp;

   is >> px >> sz >> timestamp;

   data.price(px);
   data.size(sz);
   data.time(timestamp);

   return is;
}

} // end of namespace DataLib

#endif // data_last_h_INCLUDED
