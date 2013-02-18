#ifndef system_orderwrapper_h_INCLUDED
#define system_orderwrapper_h_INCLUDED

#include "system/accountwrapper.h"
#include "system/order.h"

namespace SystemLib {

class OrderWrapper : public AccountWrapper
{

public:

   OrderWrapper();

   void place(const SystemLib::Order&);

private:

   virtual void nextValidId(TwsApi::OrderId orderId);
	virtual void   openOrder(TwsApi::OrderId orderId, const TwsApi::Contract&, const TwsApi::Order&, const TwsApi::OrderState&);
   /*
	virtual void orderStatus(TwsApi::OrderId orderId, const std::string& status, int filled, int remaining, double avgFillPrice, int permId, int parentId, double lastFillPrice, int clientId, const std::string& whyHeld);
	virtual void openOrderEnd();

	virtual void execDetails(int reqId, const TwsApi::Contract& contract, const TwsApi::Execution& execution);
	virtual void execDetailsEnd(int reqId);
   */


private:

   struct TwsOrder {
      const TwsApi::Contract   contract;
      const TwsApi::Order      order;
      const TwsApi::OrderState state;
   };

   std::set<TwsApi::OrderId> ids_;

   bool placeOrders_;
   TwsApi::OrderId oid_;
};

} // end of namespace SystemLib

#endif // system_orderwrapper_h_INCLUDED
