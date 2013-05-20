#ifndef system_comboorder_h_INCLUDED
#define system_comboorder_h_INCLUDED

#include <string>
#include "system/combo.h"

namespace SystemLib {

class Combo;
class ComboOrder
{

public:

   ComboOrder(const Combo&, float, int);
   ComboOrder(const std::string& key, float, int);

   TwsApi::Order twsOrder() const;
   IMPLEMENT_ACCESSOR(float, price);
   IMPLEMENT_ACCESSOR(int, size);

private:

   float price_;
   int size_;

   TwsApi::OrderId oid_;
   TwsApi::OrderState state_;

   Combo contract_;
};

std::ostream& operator<<(std::ostream&, const Order&);

} // end of namespace SystemLib

#endif // system_comboorder_h_INCLUDED
