#ifndef system_datawrapper_h_INCLUDED
#define system_datawrapper_h_INCLUDED

#include "system/logwrapper.h"

class Request;

class DataWrapper : public LogWrapper
{

public:

   int requestMarketData(const Request&) const;
   void cancelMarketData(const Request&) const;

protected:

   DataWrapper() : LogWrapper(true) {}

   void failed(TwsApi::TickerId id, const std::string& reason, int code);

private:

	virtual void tickGeneric(TwsApi::TickerId, TwsApi::TickType, double value);
	virtual void tickPrice  (TwsApi::TickerId, TwsApi::TickType, double price, int canAutoExecute);
	virtual void tickSize   (TwsApi::TickerId, TwsApi::TickType, int size);
	virtual void tickString (TwsApi::TickerId, TwsApi::TickType, const std::string& value);
};

#endif // system_datawrapper_h_INCLUDED

