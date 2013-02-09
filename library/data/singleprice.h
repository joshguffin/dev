#ifndef data_singleprice_h_INCLUDED
#define data_singleprice_h_INCLUDED

#include <iostream>

namespace DataLib {

class SinglePrice
{

public:

   SinglePrice();
   SinglePrice(double);

   IMPLEMENT_ACCESSORS(double , price);

   bool valid() const;

private:

   double price_;
};

#define IMPLEMENT_SINGLE_PRICE_CLASS(Name)       \
   struct Name : public SinglePrice              \
   {                                             \
      Name() {}                                  \
      Name(double price) : SinglePrice(price) {} \
   };

IMPLEMENT_SINGLE_PRICE_CLASS(Close);
IMPLEMENT_SINGLE_PRICE_CLASS(Open);
IMPLEMENT_SINGLE_PRICE_CLASS(Mark);

inline std::ostream&
operator<<(std::ostream& os, const SinglePrice& data)
{
   return os << data.price();
}


} // end of namespace DataLib

#endif // data_singleprice_h_INCLUDED
