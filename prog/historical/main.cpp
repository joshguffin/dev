#include "hmdclient.h"

#include <iostream>
using std::cout;
using std::endl;

int
main(int argc, char** argv)
{
   std::string bars(argc > 1 ? argv[1] : "30 mins");
   std::string host("127.0.0.1");
	unsigned int port = 4001;

   HmdClient client;
   client.connect(host, port);
   if (!client.isConnected()) {
      cout << "Unable to connect to " << host << ':' << port << endl;
      exit(1);
   }

   client.request("AAPL", bars);

   while (client.isConnected() && !client.completed())
      client.processMessages();

   client.dump();

   return 0;
}

