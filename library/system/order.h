#ifndef system_order_h_INCLUDED
#define system_order_h_INCLUDED

#include "twsapi/common.h"

namespace SystemLib {

class Order
{

public:

   Order(const TwsApi::Contract&, float, int);
   Order(const std::string& symbol, float, int);

   TwsApi::Order twsOrder() const;
   IMPLEMENT_ACCESSOR(const TwsApi::Contract&, contract);
   IMPLEMENT_ACCESSOR(float, price);
   IMPLEMENT_ACCESSOR(int, size);

private:

   float price_;
   int size_;

   TwsApi::OrderId oid_;
   TwsApi::Contract contract_;
   TwsApi::OrderState state_;
};

std::ostream& operator<<(std::ostream&, const Order&);

} // end of namespace SystemLib

#endif // system_order_h_INCLUDED
