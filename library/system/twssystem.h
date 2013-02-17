#ifndef system_twssystem_h_INCLUDED
#define system_twssystem_h_INCLUDED

#include "system/accountwrapper.h"
#include "system/twssocket.h"

#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/scoped_ptr.hpp>
#include <memory>
#include <stdio.h>

namespace SystemLib {

class TwsSystem : public AccountWrapper
{
public:

   static TwsSystem& Instance();

   void logging(bool);
	void processMessages();

   IMPLEMENT_ACCESSORS(unsigned int           , port);
   IMPLEMENT_ACCESSORS(const std::string&     , host);
   IMPLEMENT_ACCESSORS(const TwsApi::OrderId& , oid);

   void updateClock();

public:

   bool connect();
	bool isConnected() const;

private:

	TwsSystem();
	~TwsSystem();

	virtual void error(const int id, const int errorCode, const std::string&);
   virtual void nextValidId(TwsApi::OrderId);

   virtual TwsSocket& client() const { return *client_; }

private:

   std::string  host_;
   unsigned int port_;

   TwsApi::OrderId oid_;
	boost::scoped_ptr<TwsSocket> client_;

   boost::posix_time::ptime now_;
   boost::posix_time::ptime const start_;
   time_t time_;
};

} // end of namespace SystemLib

#endif // system_twssystem_h_INCLUDED
