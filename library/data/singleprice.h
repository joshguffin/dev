#ifndef data_singleprice_h_INCLUDED
#define data_singleprice_h_INCLUDED

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

#define IMPLEMENT_SINGLE_PRICE_CLASS(Name, RequestString)    \
   struct Name : public SinglePrice                          \
   {                                                         \
      Name() {}                                              \
      Name(double price) : SinglePrice(price) {}             \
      static std::string Request() { return RequestString; } \
   };

IMPLEMENT_SINGLE_PRICE_CLASS(Close, "");
IMPLEMENT_SINGLE_PRICE_CLASS(Open , "");
IMPLEMENT_SINGLE_PRICE_CLASS(Mark , "221");

} // end of namespace DataLib

#endif // data_singleprice_h_INCLUDED
