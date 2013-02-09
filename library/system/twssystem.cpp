#include "system/common.h"

// library headers
#include "twsapi/common.h"
#include "system/request.h"

TwsSystem&
TwsSystem::Instance()
{
   static TwsSystem system;
   return system;
}

TwsSystem::TwsSystem()
	: LogWrapper(false)
   , host_("127.0.0.1")
   , port_(4001)
   , oid_(1)
	, client_(new TwsSocket(*this))
{
}

TwsSystem::~TwsSystem()
{
}

void
TwsSystem::logging(bool state)
{
   LogWrapper::print(state);
}

// eventually this will go away
TwsSocket&
TwsSystem::socket()
{
   return *client_;
}

bool
TwsSystem::connect()
{
   if (client_->isConnected())
      return true;

   bool success = client_->connect(host_, port_);

   if (LogWrapper::print()) {
      if (success)
         cout << "TwsSystem::connect: connected to " << host_ << ':' << port_ << endl;
      else
         cout << "TwsSystem::connect: failed to connect to " << host_ << ':' << port_ << endl;
   }

   return success;
}

bool
TwsSystem::isConnected() const
{
   return client_->isConnected();
}

void
TwsSystem::processMessages()
{
   client_->processMessages();
}

void
TwsSystem::error(const int id, const int errorCode, const std::string& errorString)
{
   LogWrapper::error(id, errorCode, errorString);

   if (id == -1 && errorCode == 1100) // if "Connectivity between IB and TWS has been lost"
      client_->disconnect();
}

void
TwsSystem::nextValidId(TwsApi::OrderId orderId)
{
   oid_ = orderId;
   LogWrapper::nextValidId(orderId);
}



// --- Market data -------------------------------------------------------------

int
TwsSystem::requestMarketData(const Request& request) const
{
   static int id = 0;
   const TwsApi::Contract& contract = request.contract();
   client_->reqMktData(++id, contract, "104,165,221,236", false);
   return id;
}

void
TwsSystem::cancelMarketData(const Request& request) const
{
   client_->cancelMktData(request.tid());
}

void
TwsSystem::tickPrice(TwsApi::TickerId id, TwsApi::TickType type, double value, int autoex)
{
   Request::Tick(id, type, value);
}

void
TwsSystem::tickSize(TwsApi::TickerId id, TwsApi::TickType type, int value)
{
   Request::Tick(id, type, value);
}

void
TwsSystem::tickGeneric(TwsApi::TickerId id, TwsApi::TickType type, double value)
{
   Request::Tick(id, type, value);
}

void
TwsSystem::tickString(TwsApi::TickerId id, TwsApi::TickType type, const std::string& value)
{
   cout << "String: " << id << ' ' << type << ' ' << value << endl;
   Request::Tick(id, type, value);
}

