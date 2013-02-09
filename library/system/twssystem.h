#ifndef system_twssystem_h_INCLUDED
#define system_twssystem_h_INCLUDED

#include "system/logwrapper.h"
#include "system/twssocket.h"

#include <boost/scoped_ptr.hpp>
#include <memory>
#include <stdio.h>

class Request;

class TwsSystem : public LogWrapper
{
public:

   static TwsSystem& Instance();

   void logging(bool);
	void processMessages();

   IMPLEMENT_ACCESSORS(unsigned int       , port);
   IMPLEMENT_ACCESSORS(const std::string& , host);
   IMPLEMENT_ACCESSORS(const OrderId&     , oid);

   TwsSocket& socket();

   int requestMarketData(const Request&) const;
   void cancelMarketData(const Request&) const;

public:

   bool connect();
	bool isConnected() const;

private:

	TwsSystem();
	~TwsSystem();

	virtual void error(const int id, const int errorCode, const std::string&);
   virtual void nextValidId(OrderId);
	virtual void tickGeneric(TickerId tickerId, TickType tickType, double value);
	virtual void tickPrice(TickerId tickerId, TickType field, double price, int canAutoExecute);
	virtual void tickSize(TickerId tickerId, TickType field, int size);
	virtual void tickString(TickerId tickerId, TickType tickType, const std::string& value);

private:

   std::string  host_;
   unsigned int port_;

   OrderId oid_;
	boost::scoped_ptr<TwsSocket> client_;
};

#endif // system_twssystem_h_INCLUDED
