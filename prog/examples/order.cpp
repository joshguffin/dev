#include "system/common.h"
#include "system/fuse.h"

#include <iostream>

using namespace SystemLib;

SystemLib::Order
createOrder(const std::string& symbol, float price, int size)
{
   TwsApi::Contract contract;

   contract.symbol   = symbol;
   contract.secType  = "STK";
   contract.exchange = "SMART";
   contract.currency = "USD";

   return SystemLib::Order(contract, price, size);
}

class DelayedOrder
{
public:
   DelayedOrder(const std::string symbol, float price, int size)
      : symbol_(symbol)
      , price_(price)
      , size_(size)
   {}

   void place()
   {
      SystemLib::Order order = createOrder(symbol_, price_, size_);
      cout << "Placing " << order << endl;
      TwsSystem::Instance().place(order);
   }

private:

   std::string symbol_;
   float price_;
   int size_;
};

int
main(int argc, char** argv)
{
   std::vector<std::string> args(argv, argv + argc);

   if (args.size() < 4) {
      cout << "Usage: " << args[0] << " <symbol> <price> <size>" << endl;
      return EXIT_FAILURE;
   }

	unsigned int port = 4001;
   std::string host("127.0.0.1");

   TwsSystem& system = TwsSystem::Instance();
   system.host(host);
   system.port(port);
   system.logging(true);
   system.connect();

   DelayedOrder order(args[1], atof(args[2].c_str()), atoi(args[3].c_str()));

   FuseBase* fuse = Fuse::Create(boost::posix_time::seconds(1), order, &DelayedOrder::place);
   fuse->activate();

   while (system.isConnected())
      system.processMessages();

   delete fuse;
   return 0;
}

