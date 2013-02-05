#include "system/common.h"
#include "twsapi/common.h"

// library headers

// local headers
#include "hmdclient.h"

#define PRINT(x) ' ' << #x << '=' << x

TickerId HmdClient::NextClientId_ = 0;

///////////////////////////////////////////////////////////
// member funcs
HmdClient::HmdClient()
   : TwsClientBase(false)
	, requested_(false)
   , completed_(false)
	, id_(++NextClientId_)
{
}

HmdClient::~HmdClient()
{
   socket().cancelHistoricalData(0);
}

void
HmdClient::request(const std::string& symbol, const std::string& barSize)
{
   Contract contract;

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
}

void
HmdClient::error(const int id, const int errorCode, const std::string errorString)
{
   cerr
      << "HmdClient::error:"
      << PRINT(id)
      << PRINT(errorCode)
      << PRINT(errorString)
      << endl;

   if (id == -1 && errorCode == 1100) // if "Connectivity between IB and TWS has been lost"
      socket().disconnect();
   if (errorCode == 162)
      socket().disconnect();
}

void
HmdClient::dump() const
{
   std::vector<DataPoint>::const_iterator it  = data_.begin();
   std::vector<DataPoint>::const_iterator end = data_.end();

   while (it != end)
      cout << *it++ << endl;
}

void
HmdClient::historicalData(TickerId reqId,
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
      DataPoint pt(time, open, high, low, close, volume, barCount, WAP, hasGaps);
      data_.push_back(pt);
   }
   else if (date.substr(0,8) == "finished")
      completed_ = true;
}


void
HmdClient::scannerData(int reqId,
                       int rank,
                       const ContractDetails& contractDetails,
                       const std::string& distance,
                       const std::string& benchmark,
                       const std::string& projection,
                       const std::string& legsStr)
{
   cout
      << "HmdClient::scannerData(" << reqId << "): "
      << PRINT(rank)
      << PRINT(contractDetails)
      << PRINT(distance)
      << PRINT(benchmark)
      << PRINT(projection)
      << PRINT(legsStr)
      << endl;
}

void
HmdClient::scannerDataEnd(int reqId)
{
   cout << "HmdClient::scannerDataEnd(" << reqId << ')' << endl;
}

void
HmdClient::scannerParameters(const std::string& xml)
{
   cout << "HmdClient::scannerParameters: " << xml << endl;
}
