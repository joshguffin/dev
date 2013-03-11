#include "system/common.h"
#include "system/datawrapper.h"
#include "system/request.h"
#include "system/hmdrequest.h"

namespace SystemLib {

DataWrapper::DataWrapper()
   : LogWrapper(true)
   , tid_(0)
{}

TwsApi::TickerId
DataWrapper::requestMarketData(const Request& request)
{
   const TwsApi::Contract& contract = request.contract();
   client().reqMktData(++tid_, contract, "104,165,221,236", false);
   return tid_;
}

void
DataWrapper::cancelMarketData(const Request& request) const
{
   client().cancelMktData(request.tid());
}

TwsApi::TickerId
DataWrapper::requestHistoricalData(const HmdRequest& request)
{
   /*
   TwsApi::Contract contract;

   contract.symbol   = symbol;
   contract.secType  = "STK";
   contract.exchange = "SMART";
   contract.currency = "USD";

   std::string endDate  = "20121117 12:00:01";
   std::string duration = "1 D";
   std::string query    = "TRADES";
   //std::string barSize  = "10";
   bool        rthOnly  = false;
   int outputDateFormat = 2;

   socket().reqHistoricalData(id_,
                              contract,
                              endDate,
                              duration,
                              barSize,
                              query,
                              rthOnly,
                              outputDateFormat);
*/
   return 0;
}

void
DataWrapper::tickPrice(TwsApi::TickerId id, TwsApi::TickType type, double value, int autoex)
{
   Request::Tick(id, type, value);
}

void
DataWrapper::tickSize(TwsApi::TickerId id, TwsApi::TickType type, int value)
{
   Request::Tick(id, type, value);
}

void
DataWrapper::tickGeneric(TwsApi::TickerId id, TwsApi::TickType type, double value)
{
   Request::Tick(id, type, value);
}

void
DataWrapper::tickString(TwsApi::TickerId id, TwsApi::TickType type, const std::string& value)
{
   Request::Tick(id, type, value);
}

void
DataWrapper::failed(TwsApi::TickerId id, const std::string& reason, int code)
{
   Request::Failure fail(reason, code);
   Request::Tick(id, fail);
}

// --- historical data ---------------------------------------------------------

void
DataWrapper::historicalData(TwsApi::TickerId id,
                            const std::string& date,
                            double open,
                            double high,
                            double low,
                            double close,
                            int volume,
                            int barCount,
                            double WAP,
                            int hasGaps)
{
   time_t time = atoi(date.c_str());
   if (time != 0) {
      DataLib::HmdBar bar(time, open, high, low, close, volume, barCount, WAP, hasGaps);
      HmdRequest::Tick(id, bar);
   }
   else if (date.substr(0,8) == "finished")
      HmdRequest::Done(id);
}


void
DataWrapper::scannerData(int reqId,
                         int rank,
                         const TwsApi::ContractDetails& contractDetails,
                         const std::string& distance,
                         const std::string& benchmark,
                         const std::string& projection,
                         const std::string& legsStr)
{
   LogWrapper::scannerData(reqId, rank, contractDetails, distance, benchmark,
                           projection, legsStr);
}

void
DataWrapper::scannerDataEnd(int reqId)
{
   cout << "DataWrapper::scannerDataEnd(" << reqId << ')' << endl;
}

void
DataWrapper::scannerParameters(const std::string& xml)
{
   cout << "DataWrapper::scannerParameters: " << xml << endl;
}




} // end of namespace SystemLib
