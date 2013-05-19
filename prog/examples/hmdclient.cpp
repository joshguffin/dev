#include "system/common.h"

#include <iostream>

using namespace SystemLib;

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

   while (system.carryOn())
      system.processMessages();

   return 0;
}

