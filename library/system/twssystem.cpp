#include "system/common.h"
#include "system/fuse.h"

namespace SystemLib {

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
   , now_  (boost::posix_time::microsec_clock::local_time())
   , start_(now_)
   , time_ (to_time_t(now_))
{
}

TwsSystem::~TwsSystem()
{
}

const boost::posix_time::ptime&
TwsSystem::Now()
{
   return Instance().now_;
}

const boost::posix_time::ptime&
TwsSystem::now() const
{
   return now_;
}

const boost::posix_time::ptime&
TwsSystem::updateNow()
{
   now_  = boost::posix_time::microsec_clock::local_time();
   time_ = to_time_t(now_);
   return now_;
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
   FuseBase::ProcessQueue();

   static const boost::posix_time::time_duration empty;
   boost::posix_time::time_duration next = FuseBase::NextFireTime();

   timeval interval = (next == empty
                       ? defaultInterval_
                       : to_timeval(next));

   client_->processMessages(interval);
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

   if (errorCode == 2105) {
      // HMDS data farm connection is broken:ushmds.us
   }
}

void
TwsSystem::nextValidId(TwsApi::OrderId orderId)
{
   oid_ = orderId;
   LogWrapper::nextValidId(orderId);
}

} // end of namespace SystemLib
