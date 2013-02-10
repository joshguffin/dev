#include "system/common.h"

TwsSystem&
TwsSystem::Instance()
{
   static TwsSystem system;
   return system;
}

TwsSystem::TwsSystem()
   : host_("127.0.0.1")
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

   // if "Connectivity between IB and TWS has been lost"
   if (id == -1 && errorCode == 1100) {
      client_->disconnect();
      return;
   }

   if (errorCode == 200)
      DataWrapper::failed(id, errorString, errorCode);
}

void
TwsSystem::nextValidId(TwsApi::OrderId orderId)
{
   oid_ = orderId;
   LogWrapper::nextValidId(orderId);
}
