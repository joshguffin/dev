#ifndef system_twssystem_h_INCLUDED
#define system_twssystem_h_INCLUDED

#include "system/datawrapper.h"
#include "system/twssocket.h"

#include <boost/scoped_ptr.hpp>
#include <memory>
#include <stdio.h>

class TwsSystem : public DataWrapper
{
public:

   static TwsSystem& Instance();

   void logging(bool);
	void processMessages();

   IMPLEMENT_ACCESSORS(unsigned int           , port);
   IMPLEMENT_ACCESSORS(const std::string&     , host);
   IMPLEMENT_ACCESSORS(const TwsApi::OrderId& , oid);

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
};

#endif // system_twssystem_h_INCLUDED
