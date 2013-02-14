#include "system/common.h"
#include "system/request.h"

#include <iostream>

const unsigned MAX_ATTEMPTS = 50;
const unsigned SLEEP_TIME = 10;

using namespace SystemLib;

//==============================================================================
// AccountConsumer; receives account data from tws
//==============================================================================

class AccountConsumer : public AccountWrapper::Consumer
{

public:

   AccountConsumer() : done_(false) {}

   IMPLEMENT_ACCESSOR(bool , done);

private:

   virtual void update(const std::string& account,
                       const AccountWrapper::Portfolio& portfolio,
                       const std::string& timestamp);

   bool done_;
};

void
AccountConsumer::update(const std::string& account,
                        const AccountWrapper::Portfolio& portfolio,
                        const std::string& timestamp)
{
   AccountWrapper::Portfolio::const_iterator it  = portfolio.begin();

   StringLib::CSV headers;

   // dump headers
   headers << "Account" << "Update Time";
   TwsApi::contractHeaders(headers);
   AccountWrapper::Position::Headers(headers);
   cout << headers << endl;

   // write entries
   for (; it != portfolio.end(); ++it) {
      const TwsApi::Contract& contract    = it->first;
      const AccountWrapper::Position& pos = it->second;
      StringLib::CSV csv;
      csv << account << timestamp;
      contractSeparated(csv, contract);
      pos.dump(csv);
      cout << csv << endl;
   }

   done_ = true;
}

//==============================================================================
// main loop
//==============================================================================

int
main(int argc, char** argv)
{
	unsigned int port = argc > 1 ? atoi(argv[1]) : 4001;
   std::string host(argc > 2 ? argv[2] : "127.0.0.1");

   TwsSystem& system = TwsSystem::Instance();
   system.host(host);
   system.port(port);
   system.logging(false);

	unsigned attempt = 0;

   AccountConsumer ac;
	for (;;) {
		++attempt;
      system.connect();

		while (system.isConnected()) {
			system.processMessages();
         if (ac.done())
            return 0;
      }

		if (attempt >= MAX_ATTEMPTS)
			break;

		sleep(SLEEP_TIME);
	}

   return 0;
}

