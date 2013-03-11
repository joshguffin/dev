#ifndef system_datawrapper_h_INCLUDED
#define system_datawrapper_h_INCLUDED

#include "system/logwrapper.h"

namespace SystemLib {

class Request;
class HmdRequest;

class DataWrapper : public LogWrapper
{

public:

   TwsApi::TickerId requestMarketData(const Request&);
   TwsApi::TickerId requestHistoricalData(const HmdRequest&);
   void cancelMarketData(const Request&) const;

protected:

   DataWrapper();

   void failed(TwsApi::TickerId id, const std::string& reason, int code);

private:

   // live market data
	virtual void tickGeneric(TwsApi::TickerId, TwsApi::TickType, double value);
	virtual void tickPrice  (TwsApi::TickerId, TwsApi::TickType, double price, int canAutoExecute);
	virtual void tickSize   (TwsApi::TickerId, TwsApi::TickType, int size);
	virtual void tickString (TwsApi::TickerId, TwsApi::TickType, const std::string& value);

   // historical market data
	virtual void scannerData(int, int, const TwsApi::ContractDetails&, const std::string&, const std::string&, const std::string&, const std::string&);
	virtual void scannerDataEnd(int);
	virtual void scannerParameters(const std::string&);
	virtual void historicalData(TwsApi::TickerId, const std::string&, double, double, double, double, int, int, double, int);

   TwsApi::TickerId tid_;
};

} // end of namespace SystemLib

#endif // system_datawrapper_h_INCLUDED
