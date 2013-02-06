#include "system/common.h"

#include <iostream>
using std::cout;
using std::endl;

const unsigned MAX_ATTEMPTS = 50;
const unsigned SLEEP_TIME = 10;

void
request()
{
   static bool requested = false;
   if (requested)
      return;

   requested = true;

   Contract contract;
   contract.symbol   = "AAPL";
   contract.secType  = "STK";
   contract.exchange = "SMART";
   contract.currency = "USD";
   TwsSystem::Instance().socket().reqMktData(1, contract, "221,165,236,258", false);
}

void
placeOrder()
{
   static bool placed = false;

   if (placed)
      return;

   placed = true;

   Contract contract;
   Order order;

   contract.symbol   = "AAPL";
   contract.secType  = "STK";
   contract.exchange = "SMART";
   contract.currency = "USD";

   order.action        = "BUY";
   order.totalQuantity = 1000;
   order.orderType     = "LMT";
   order.lmtPrice      = 0.01;

   const OrderId& oid = TwsSystem::Instance().oid();
   cout
      << "Placing order " << oid
      << ' ' << order.action.c_str()
      << ' ' << contract.symbol.c_str()
      << ' ' << order.totalQuantity
      << '@' << order.lmtPrice
      << endl;

   TwsSystem::Instance().socket().placeOrder(oid, contract, order);
}

int
main(int argc, char** argv)
{
   std::string host(argc > 1 ? argv[1] : "127.0.0.1");
	unsigned int port = 4001;

   TwsSystem& system = TwsSystem::Instance();
   system.host(host);
   system.port(port);
   system.logging(true);

	unsigned attempt = 0;

   cout << "Start of POSIX Socket Client Test" << endl;

	for (;;) {
		++attempt;
		cout << "Attempt " << attempt << " of " << MAX_ATTEMPTS << endl;

      system.connect();

		while (system.isConnected()) {
			system.processMessages();
         request();
         placeOrder();
      }

		if (attempt >= MAX_ATTEMPTS)
			break;

		cout << "Sleeping " << SLEEP_TIME << " seconds before next attempt" << endl;
		sleep(SLEEP_TIME);
	}

   return 0;
}

