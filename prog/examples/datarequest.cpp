#include "system/common.h"
#include "system/request.h"

#include <iostream>
using std::cout;
using std::endl;
using namespace SystemLib;

class Item : public Request::Consumer
{

public:
   Item(const RequestKey& key) : Request::Consumer(key) {}
   virtual ~Item() {}

   virtual void handle(const DataLib::BidAsk& data) { cout << "BidAsk" << ' ' << data << endl; }
   virtual void handle(const DataLib::Last&   data) { cout << "Last"   << ' ' << data << endl; }
   virtual void handle(const DataLib::Mark&   data) { cout << "Mark"   << ' ' << data << endl; }
   virtual void handle(const DataLib::Open&   data) { cout << "Open"   << ' ' << data << endl; }
   virtual void handle(const DataLib::Close&  data) { cout << "Close"  << ' ' << data << endl; }
   virtual void handle(const DataLib::State&  data) { cout << "State"  << ' ' << data << endl; }
   virtual void handle(const DataLib::Stats&  data) { cout << "Stats"  << ' ' << data << endl; }
   virtual void handle(const DataLib::HistoricalStats& data) { cout << "HistoricalStats" << ' ' << data << endl; }
   virtual void handle(const DataLib::Fundamentals&    data) { cout << "Fundamentals"    << ' ' << data << endl; }
   virtual void handle(const Request::Failure& data)         { cout << "Failure"         << ' ' << data << endl; }
};

int
main(int argc, char** argv)
{
   if (argc < 2) {
      cout << "Usage: " << argv[0] << " <symbol>" << endl;
      return EXIT_FAILURE;
   }

   std::string host("127.0.0.1");
	unsigned int port = 4001;

   TwsSystem& system = TwsSystem::Instance();
   system.host(host);
   system.port(port);
   system.logging(true);
   system.connect();

   RequestKey key(argv[1]);
   Item request(key);

   while (system.isConnected())
      system.processMessages();

   return 0;
}

