#include "system/udpserver.h"
#include <vector>
#include <string>
#include <iostream>
using std::cout;
using std::endl;

int
main(int argc, char** argv)
{
   std::vector<std::string> args(argv, argv + argc);

   if (args.size() < 2) {
      cout << "Usage: " << args[0] << " <port>" << endl;
      return EXIT_FAILURE;
   }

   unsigned short port = atoi(args[1].c_str());
   UdpServer server(port);

   while (true)
      server.processMessages();

   return 0;
}
