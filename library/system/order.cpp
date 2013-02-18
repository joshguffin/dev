#include "system/common.h"
#include "system/order.h"

namespace SystemLib {

Order::Order(const TwsApi::Contract& contract, float price, int size)
   : contract_(contract)
   , price_(price)
   , size_(size)
   , oid_(-1)
{
}

Order::Order(const std::string& symbol, float price, int size)
   : price_(price)
   , size_(size)
{
   contract_.symbol   = symbol;
   contract_.secType  = "STK";
   contract_.exchange = "SMART";
   contract_.currency = "USD";
   //client().placeOrder(oid_, con, ord);
}

TwsApi::Order
Order::twsOrder() const
{
   TwsApi::Order order;
   order.action        = size_ > 0 ? "BUY" : "SELL";
   order.totalQuantity = std::abs(size_);
   order.orderType     = "LMT";
   order.lmtPrice      = price_;

   return order;
}

std::ostream&
operator<<(std::ostream& os, const Order& order)
{
   os << order.contract() << ' ' << order.size() << '@' << order.price();
   return os;
}


} // end of namespace SystemLib
