#include "system/common.h"

// library headers
#include "twsapi/common.h"

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
	, client_(new TwsSocket(*this))
   , oid_(1);
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
TwsSystem::error(const int id, const int errorCode, const std::string errorString)
{
   LogWrapper::error(id, errorCode, errorString);

   if (id == -1 && errorCode == 1100) // if "Connectivity between IB and TWS has been lost"
      client_->disconnect();
}

void
TwsSystem::nextValidId(OrderId orderId)
{
   oid_ = orderId;
   LogWrapper::nextValidId(orderId);
}


