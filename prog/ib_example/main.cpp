#include "system/common.h"
#include "system/request.h"

#include <iostream>
using std::cout;
using std::endl;

const unsigned MAX_ATTEMPTS = 50;
const unsigned SLEEP_TIME = 10;

class Item : public Request::Consumer
{

public:
   Item(const RequestKey& key) : Request::Consumer(key) {}
   virtual ~Item() {}

#define DEFINE_HANDLE(Type) virtual void handle(const DataLib::Type& data) { cout << #Type << ' ' << data << endl; }
   DEFINE_HANDLE(BidAsk);
   DEFINE_HANDLE(Last);
   DEFINE_HANDLE(Mark);
   DEFINE_HANDLE(Open);
   DEFINE_HANDLE(Close);
   DEFINE_HANDLE(State);
   DEFINE_HANDLE(Stats);

   DEFINE_HANDLE(HistoricalStats);
   DEFINE_HANDLE(Fundamentals);
#undef DEFINE_HANDLE
};

void
placeOrder()
{
   static bool placed = false;

   if (placed)
      return;

   placed = true;

   TwsApi::Contract contract;
   TwsApi::Order order;

   contract.symbol   = "AAPL";
   contract.secType  = "STK";
   contract.exchange = "SMART";
   contract.currency = "USD";

   order.action        = "BUY";
   order.totalQuantity = 1000;
   order.orderType     = "LMT";
   order.lmtPrice      = 0.01;

   const TwsApi::OrderId& oid = TwsSystem::Instance().oid();
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

   Item* item = NULL;
   int i = 0;
	for (;;) {
		++attempt;
		cout << "Attempt " << attempt << " of " << MAX_ATTEMPTS << endl;

      system.connect();

		while (system.isConnected()) {
			system.processMessages();

         if (!item && i < 3) {
            RequestKey key("AAPL");
            item = new Item(key);
         }

         if (++i == 3) {
            delete item;
            item = NULL;
         }
         //placeOrder();
      }

		if (attempt >= MAX_ATTEMPTS)
			break;

		cout << "Sleeping " << SLEEP_TIME << " seconds before next attempt" << endl;
		sleep(SLEEP_TIME);
	}

   return 0;
}

