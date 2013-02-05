#include "system/common.h"

// library headers
#include "twsapi/common.h"
#include "system/twsclientbase.h"

#define PRINT(x) ' ' << #x << '=' << x

const int SLEEP_BETWEEN_PINGS = 30; // seconds

///////////////////////////////////////////////////////////
// member funcs
TwsClientBase::TwsClientBase(bool print)
	: LogWrapper(print)
	, client_(new TwsSocket(*this))
{
}

TwsClientBase::~TwsClientBase()
{
}

TwsSocket&
TwsClientBase::socket()
{
   return *client_;
}

bool
TwsClientBase::connect(const std::string& host, unsigned int port)
{
   if (client_->isConnected())
      return true;

   bool bRes = client_->connect(host, port);

   if (LogWrapper::print()) {
      if (bRes)
         cout << "TwsClientBase::connect: connected to " << host << ':' << port << endl;
      else
         cout << "TwsClientBase::connect: failed to connect to " << host << ':' << port << endl;
   }

   return bRes;
}

bool
TwsClientBase::isConnected() const
{
   return client_->isConnected();
}

void
TwsClientBase::processMessages()
{
   client_->processMessages();
}

void
TwsClientBase::error(const int id, const int errorCode, const std::string errorString)
{
   LogWrapper::error(id, errorCode, errorString);

   if (id == -1 && errorCode == 1100) // if "Connectivity between IB and TWS has been lost"
      client_->disconnect();
}

