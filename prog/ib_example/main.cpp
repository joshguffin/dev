#include "posixtestclient.h"
#include <boost/program_options.hpp>
#include <stdio.h>

const unsigned MAX_ATTEMPTS = 50;
const unsigned SLEEP_TIME = 10;

using namespace boost::program_options;

int main(int argc, char** argv)
{
   options_description desc("Allowed command-line options");
   desc.add_options()
      ("help", "Display this help information")
      ("host", boost::program_options::value<std::string>(), "host to connect to");

   variables_map m;
   store(parse_command_line(argc, argv, desc), m);
   notify(m);



	const char* host = argc > 1 ? argv[1] : "";
	unsigned int port = 4001;
	int clientId = 0;

	unsigned attempt = 0;
	printf( "Start of POSIX Socket Client Test %u\n", attempt);

	for (;;) {
		++attempt;
		printf( "Attempt %u of %u\n", attempt, MAX_ATTEMPTS);

		TwsClient client;

		client.connect( host, port, clientId);

		while( client.isConnected()) {
			client.processMessages();
		}

		if( attempt >= MAX_ATTEMPTS) {
			break;
		}

		printf( "Sleeping %u seconds before next attempt\n", SLEEP_TIME);
		sleep( SLEEP_TIME);
	}

	printf ( "End of POSIX Socket Client Test\n");
}

