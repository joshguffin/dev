#ifndef twsclient_h_INCLUDED
#define twsclient_h_INCLUDED

#include "ibwrap/twsclientbase.h"

#include <boost/scoped_ptr.hpp>
#include <memory>
#include <stdio.h>

class TwsClient : public TwsClientBase
{
public:

	TwsClient();
	~TwsClient();

	void processMessages();

private:

	void placeOrder();
	void cancelOrder();

private:

	virtual void nextValidId(OrderId orderId);

	// events
	virtual void tickGeneric(TickerId tickerId, TickType tickType, double value);
	virtual void tickPrice(TickerId tickerId, TickType field, double price, int canAutoExecute);
	virtual void tickSize(TickerId tickerId, TickType field, int size);
	virtual void tickString(TickerId tickerId, TickType tickType, const std::string& value);
	virtual void error(const int id, const int errorCode, const std::string errorString);

private:

	OrderId oid_;
};

#endif // twsclient_h_INCLUDED
