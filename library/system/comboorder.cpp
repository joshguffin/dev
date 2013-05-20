#include "system/common.h"
#include "system/comboorder.h"

namespace SystemLib {

TwsApi::Order
ComboOrder::twsOrder() const
{
   TwsApi::Order order;
   order.action        = size_ > 0 ? "BUY" : "SELL";
   order.totalQuantity = std::abs(size_);
   order.orderType     = "LMT";
   order.lmtPrice      = price_;

   return order;
}

} // end of namespace SystemLib
