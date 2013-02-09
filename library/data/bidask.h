#ifndef data_bidask_h_INCLUDED
#define data_bidask_h_INCLUDED

#include <iostream>

namespace DataLib {

class BidAsk
{

public:

   BidAsk();
   BidAsk(double, double, int, int);

   IMPLEMENT_ACCESSORS(double , bid);
   IMPLEMENT_ACCESSORS(double , ask);
   IMPLEMENT_ACCESSORS(int   , bidSize);
   IMPLEMENT_ACCESSORS(int   , askSize);

   bool valid() const;

private:

   double bid_;
   double ask_;
   int    bidSize_;
   int    askSize_;
};

inline std::ostream&
operator<<(std::ostream& os, const BidAsk& data)
{
   os << data.bid()
      << ' ' << data.ask()
      << ' ' << data.bidSize()
      << ' ' << data.askSize();
   return os;
}

} // end of namespace DataLib

#endif // data_bidask_h_INCLUDED
