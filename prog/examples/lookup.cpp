#include "system/common.h"
#include "system/fuse.h"

#include <iostream>

using namespace SystemLib;

int
main(int argc, char** argv)
{
   std::vector<std::string> args(argv, argv + argc);

   if (args.size() < 2) {
      cout << "Usage: " << args[0] << " <symbol>" << endl;
      return EXIT_FAILURE;
   }

	unsigned int port = 4001;
   std::string host("127.0.0.1");

   TwsSystem& system = TwsSystem::Instance();
   system.host(host);
   system.port(port);
   system.logging(true);
   system.connect();

   Contract::Security::Type stock = Contract::Security::STK;
   system.requestDetails(args[1], stock);

   while (system.isConnected())
      system.processMessages();

   return 0;
}

