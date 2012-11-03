#include "twsclient.h"

#include <iostream>
using std::cout;
using std::endl;

const unsigned MAX_ATTEMPTS = 50;
const unsigned SLEEP_TIME = 10;

int
main(int argc, char** argv)
{
   std::string host(argc > 1 ? argv[1] : "127.0.0.1");
	unsigned int port = 4001;

	unsigned attempt = 0;

   cout << "Start of POSIX Socket Client Test" << endl;

	for (;;) {
		++attempt;
		cout << "Attempt " << attempt << " of " << MAX_ATTEMPTS << endl;
		TwsClient client;

		client.connect(host, port);

		while (client.isConnected())
			client.processMessages();

		if (attempt >= MAX_ATTEMPTS)
			break;

		cout << "Sleeping " << SLEEP_TIME << " seconds before next attempt" << endl;
		sleep(SLEEP_TIME);
	}

   return 0;
}

