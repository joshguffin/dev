#include "system/common.h"
#include "system/fuse.h"

#include <signal.h>

namespace SystemLib {

TwsSystem&
TwsSystem::Instance()
{
   static TwsSystem system;

   signal(SIGINT, TwsSystem::SignalHandler);

   return system;
}

void
TwsSystem::SignalHandler(int signum)
{
   static int catches = 0;
   ++catches;

   printf("\nCaught signal %d (#%d)\n", signum, catches);
   signal(SIGINT, TwsSystem::SignalHandler);
   TwsSystem::Instance().processMessages();

   // For whatever reason we're not getting back to the main loop
   if (catches == 3)
      exit(1);

   // ask the main loop to exit nicely
   SystemLib::TwsSystem::Instance().carryOn_ = false;
}

TwsSystem::TwsSystem()
   : host_("127.0.0.1")
   , port_(4001)
	, client_(new TwsSocket(*this))
   , now_  (boost::posix_time::microsec_clock::local_time())
   , start_(now_)
   , time_ (to_time_t(now_))
   , carryOn_(true)
{
   defaultInterval_.tv_sec  = 0;
   defaultInterval_.tv_usec = 1E5; // 1/10th of a seconds sleep time
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
TwsSystem::carryOn(bool state)
{
   carryOn_ = state;
}

bool
TwsSystem::carryOn() const
{
   if (!isConnected())
      return false;

   return carryOn_;
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

} // end of namespace SystemLib
