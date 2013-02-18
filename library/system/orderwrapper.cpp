#include "system/common.h"
#include "system/orderwrapper.h"
#include "system/request.h"

namespace SystemLib {

/*
placeOrder()
cancelOrder()
reqOpenOrders()
reqAllOpenOrders()
reqAutoOpenOrders()
reqIDs()
exerciseOptions()
*/

OrderWrapper::OrderWrapper()
   : placeOrders_(false)
   , oid_(-1)
{
}

void
OrderWrapper::place(const SystemLib::Order& order)
{
   const TwsApi::Order&    twsOrder = order.twsOrder();
   const TwsApi::Contract& contract = order.contract();

   client().placeOrder(oid_, contract, twsOrder);
   oid_++;
}

void
OrderWrapper::nextValidId(TwsApi::OrderId orderId)
{
   oid_ = orderId;
}

void
OrderWrapper::openOrder(TwsApi::OrderId orderId,
                        const TwsApi::Contract& c,
                        const TwsApi::Order& o,
                        const TwsApi::OrderState& ostate)
{
   ids_.insert(orderId);
}

/*
void
OrderWrapper::openOrderEnd()
{
}

void
OrderWrapper::orderStatus(TwsApi::OrderId orderId,
                          const std::string& status,
                          int filled,
                          int remaining,
                          double avgFillPrice,
                          int permId,
                          int parentId,
                          double lastFillPrice,
                          int clientId,
                          const std::string& whyHeld)

{
}

void
OrderWrapper::execDetails(int reqId, const TwsApi::Contract& contract, const TwsApi::Execution& execution)
{
}

void
OrderWrapper::execDetailsEnd(int reqId)
{
}
*/

} // end of namespace SystemLib
