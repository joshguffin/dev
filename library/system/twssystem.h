#ifndef system_twssystem_h_INCLUDED
#define system_twssystem_h_INCLUDED

#include "system/orderwrapper.h"
#include "system/twssocket.h"

#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/scoped_ptr.hpp>
#include <memory>
#include <stdio.h>

namespace SystemLib {

class TwsSystem : public OrderWrapper
{
public:

   static TwsSystem& Instance();

   void logging(bool);
	void processMessages();

   IMPLEMENT_ACCESSORS(time_t             , time);
   IMPLEMENT_ACCESSORS(unsigned int       , port);
   IMPLEMENT_ACCESSORS(const std::string& , host);

   const boost::posix_time::ptime& updateNow();
   const boost::posix_time::ptime& now() const;

   static const boost::posix_time::ptime& Now();

public:

   bool connect();
	bool isConnected() const;

   virtual TwsSocket& client() const { return *client_; }

private:

	TwsSystem();
	~TwsSystem();

	virtual void error(const int id, const int errorCode, const std::string&);

private:

   std::string  host_;
   unsigned int port_;

	boost::scoped_ptr<TwsSocket> client_;

   boost::posix_time::ptime now_;
   boost::posix_time::ptime const start_;
   time_t time_;

   timeval defaultInterval_;
};

} // end of namespace SystemLib

#endif // system_twssystem_h_INCLUDED
