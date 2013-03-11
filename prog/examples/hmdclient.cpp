#include "system/common.h"
#include "system/fuse.h"

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

   DelayedOrder order(args[1], atof(args[2].c_str()), atoi(args[3].c_str()));

   FuseBase* fuse = Fuse::Create(boost::posix_time::seconds(1), order, &DelayedOrder::place);
   fuse->activate();

   while (system.isConnected())
      system.processMessages();

   delete fuse;
   return 0;
}

