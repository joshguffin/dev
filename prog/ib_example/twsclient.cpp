
// library headers
#include "ib/IBString.h"
#include "ib/Contract.h"
#include "ib/Order.h"

// local headers
#include "twssocket.h"
#include "twsclient.h"

#include <iostream>
using std::cout;
using std::endl;

#define PRINT(x) ' ' << #x << '=' << x

const int SLEEP_BETWEEN_PINGS = 30; // seconds

///////////////////////////////////////////////////////////
// member funcs
TwsClient::TwsClient()
	: client_(new TwsSocket(*this))
	, oid_(0)
{
}

TwsClient::~TwsClient()
{
}

bool
TwsClient::connect(const std::string& host, unsigned int port)
{
   if (client_->isConnected())
      return true;

   bool bRes = client_->connect(host, port);

   if (bRes)
      cout << "TwsClient::connect: connected to " << host << ':' << port << endl;
   else
      cout << "TwsClient::connect: failed to connect to " << host << ':' << port << endl;

   return bRes;
}

bool
TwsClient::isConnected() const
{
   return client_->isConnected();
}

void
TwsClient::processMessages()
{
   client_->processMessages();
}

void
TwsClient::placeOrder()
{
   Contract contract;
   Order order;

   contract.symbol   = "AAPL";
   contract.secType  = "STK";
   contract.exchange = "SMART";
   contract.currency = "USD";

   order.action        = "BUY";
   order.totalQuantity = 1000;
   order.orderType     = "LMT";
   order.lmtPrice      = 0.01;

   printf("Placing Order %ld: %s %ld %s at %f\n", oid_, order.action.c_str(), order.totalQuantity, contract.symbol.c_str(), order.lmtPrice);

   //client_->placeOrder(oid_, contract, order);
   client_->reqMktData(1, contract, "221,165,236,258", false);
}

void
TwsClient::cancelOrder()
{
   printf("Cancelling Order %ld\n", oid_);

   client_->cancelOrder(oid_);
}

///////////////////////////////////////////////////////////////////
// events
void
TwsClient::orderStatus(OrderId orderId,
                       const std::string& status,
                       int filled,
                       int remaining,
                       double avgFillPrice,
                       int permId,
                       int parentId,
                       double lastFillPrice,
                       int clientId,
                       const std::string& whyHeld)

{

   cout
      << "TwsClient::orderStatus: "
      << PRINT(orderId)
      << PRINT(status)
      << PRINT(filled)
      << PRINT(remaining)
      << PRINT(avgFillPrice)
      << PRINT(permId)
      << PRINT(parentId)
      << PRINT(lastFillPrice)
      << PRINT(clientId)
      << PRINT(whyHeld)
      << endl;
}

void
TwsClient::nextValidId(OrderId orderId)
{
   oid_ = orderId;
}

void
TwsClient::currentTime(long time)
{
   time_t t = (time_t)time;
   struct tm * timeinfo = localtime (&t);
   printf("The current date/time is: %s", asctime(timeinfo));
}

void
TwsClient::error(const int id, const int errorCode, const std::string errorString)
{
   cout
      << "TwsClient::error: "
      << PRINT(id)
      << PRINT(errorCode)
      << PRINT(errorString)
      << endl;

   if (id == -1 && errorCode == 1100) // if "Connectivity between IB and TWS has been lost"
      client_->disconnect();
}

void
TwsClient::tickPrice(TickerId tickerId,
                     TickType field,
                     double price,
                     int canAutoExecute)
{
   cout
      << "TwsClient::tickPrice: "
      << PRINT(tickerId)
      << PRINT(field)
      << PRINT(price)
      << PRINT(canAutoExecute)
      << endl;
}

void
TwsClient::tickSize(TickerId tickerId, TickType field, int size)
{
   cout
      << "TwsClient::tickSize: "
      << PRINT(tickerId)
      << PRINT(field)
      << PRINT(size)
      << endl;
}

void
TwsClient::tickOptionComputation(TickerId tickerId,
                                 TickType tickType,
                                 double impliedVol,
                                 double delta,
                                 double optPrice,
                                 double pvDividend,
                                 double gamma,
                                 double vega,
                                 double theta,
                                 double undPrice)
{
   cout
      << "TwsClient::tickOptionComputation: "
      << PRINT(tickerId)
      << PRINT(tickType)
      << PRINT(impliedVol)
      << PRINT(delta)
      << PRINT(optPrice)
      << PRINT(pvDividend)
      << PRINT(gamma)
      << PRINT(vega)
      << PRINT(theta)
      << PRINT(undPrice)
      << endl;
}

void
TwsClient::tickGeneric(TickerId tickerId, TickType tickType, double value)
{
   cout
      << "TwsClient::tickGeneric: "
      << PRINT(tickerId)
      << PRINT(tickType)
      << PRINT(value)
      << endl;
}

void
TwsClient::tickString(TickerId tickerId, TickType tickType, const std::string& value)
{
   cout
      << "TwsClient::tickString: "
      << PRINT(tickerId)
      << PRINT(tickType)
      << PRINT(value)
      << endl;
}

void
TwsClient::tickEFP(TickerId tickerId,
                   TickType tickType,
                   double basisPoints,
                   const std::string& formattedBasisPoints,
                   double totalDividends,
                   int holdDays,
                   const std::string& futureExpiry,
                   double dividendImpact,
                   double dividendsToExpiry)
{
   cout
      << "TwsClient::tickEFP: "
      << PRINT(tickerId)
      << PRINT(tickType)
      << PRINT(basisPoints)
      << PRINT(formattedBasisPoints)
      << PRINT(totalDividends)
      << PRINT(holdDays)
      << PRINT(futureExpiry)
      << PRINT(dividendImpact)
      << PRINT(dividendsToExpiry)
      << endl;
}

void
TwsClient::openOrder(OrderId orderId,
                     const Contract& c,
                     const Order& o,
                     const OrderState& ostate)
{
   cout
      << "TwsClient::openOrder: "
      << PRINT(orderId)
      << endl;
}

void
TwsClient::openOrderEnd()
{}

void
TwsClient::winError(const std::string& str, int lastError)
{
   cout
      << "TwsClient::winError: "
      << PRINT(str)
      << PRINT(lastError)
      << endl;
}

void
TwsClient::connectionClosed()
{}

void
TwsClient::updateAccountValue(const std::string& key,
                              const std::string& val,
                              const std::string& currency,
                              const std::string& accountName)
{
   cout
      << "TwsClient::updateAccountValue: "
      << PRINT(key)
      << PRINT(val)
      << PRINT(currency)
      << PRINT(accountName)
      << endl;
}

void
TwsClient::updatePortfolio(const Contract& contract,
                           int position,
                           double marketPrice,
                           double marketValue,
                           double averageCost,
                           double unrealizedPNL,
                           double realizedPNL,
                           const std::string& accountName)
{
   cout
      << "TwsClient::updatePortfolio: "
      << PRINT(position)
      << PRINT(marketPrice)
      << PRINT(marketValue)
      << PRINT(averageCost)
      << PRINT(unrealizedPNL)
      << PRINT(realizedPNL)
      << PRINT(accountName)
      << endl;
}

void
TwsClient::updateAccountTime(const std::string& timeStamp)
{
   cout
      << "TwsClient::updateAccountTime: "
      << PRINT(timeStamp)
      << endl;
}

void
TwsClient::accountDownloadEnd(const std::string& accountName)
{
   cout
      << "TwsClient::accountDownloadEnd: "
      << PRINT(accountName)
      << endl;
}

void
TwsClient::contractDetails(int reqId, const ContractDetails& contractDetails)
{
   cout
      << "TwsClient::contractDetails: "
      << PRINT(reqId)
      << endl;
}

void
TwsClient::bondContractDetails(int reqId, const ContractDetails& contractDetails)
{
   cout
      << "TwsClient::bondContractDetails: "
      << PRINT(reqId)
      << endl;
}

void
TwsClient::contractDetailsEnd(int reqId)
{
   cout
      << "TwsClient::contractDetailsEnd: "
      << PRINT(reqId)
      << endl;
}

void
TwsClient::execDetails(int reqId, const Contract& contract, const Execution& execution)
{
   cout
      << "TwsClient::execDetails: "
      << PRINT(reqId)
      << endl;
}

void
TwsClient::execDetailsEnd(int reqId)
{
   cout
      << "TwsClient::execDetailsEnd: "
      << PRINT(reqId)
      << endl;
}


void
TwsClient::updateMktDepth(TickerId id,
                          int position,
                          int operation,
                          int side,
                          double price,
                          int size)
{
   cout
      << "TwsClient::updateMktDepth: "
      << PRINT(id)
      << PRINT(position)
      << PRINT(operation)
      << PRINT(side)
      << PRINT(price)
      << PRINT(size)
      << endl;
}

void
TwsClient::updateMktDepthL2(TickerId id,
                            int position,
                            std::string marketMaker,
                            int operation,
                            int side,
                            double price,
                            int size)
{
   cout
      << "TwsClient::updateMktDepthL2: "
      << PRINT(id)
      << PRINT(position)
      << PRINT(marketMaker)
      << PRINT(operation)
      << PRINT(side)
      << PRINT(price)
      << PRINT(size)
      << endl;
}

void
TwsClient::updateNewsBulletin(int msgId,
                              int msgType,
                              const std::string& newsMessage,
                              const std::string& originExch)
{
   cout
      << "TwsClient::updateNewsBulletin: "
      << PRINT(msgId)
      << PRINT(msgType)
      << PRINT(newsMessage)
      << PRINT(originExch)
      << endl;
}

void
TwsClient::managedAccounts(const std::string& accountsList)
{
   cout
      << "TwsClient::managedAccounts: "
      << PRINT(accountsList)
      << endl;
}

void
TwsClient::receiveFA(faDataType pFaDataType, const std::string& cxml)
{
   cout
      << "TwsClient::receiveFA: "
      << PRINT(pFaDataType)
      << PRINT(cxml)
      << endl;
}

void
TwsClient::historicalData(TickerId reqId,
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
   cout
      << "TwsClient::historicalData: "
      << PRINT(reqId)
      << PRINT(date)
      << PRINT(open)
      << PRINT(high)
      << PRINT(low)
      << PRINT(close)
      << PRINT(volume)
      << PRINT(barCount)
      << PRINT(WAP)
      << PRINT(hasGaps)
      << endl;
}

void
TwsClient::scannerParameters(const std::string& xml)
{
   cout
      << "TwsClient::scannerParameters: "
      << PRINT(xml)
      << endl;
}

void
TwsClient::scannerData(int reqId,
                       int rank,
                       const ContractDetails& contractDetails,
                       const std::string& distance,
                       const std::string& benchmark,
                       const std::string& projection,
                       const std::string& legsStr)
{
   cout
      << "TwsClient::scannerData: "
      << PRINT(reqId)
      << PRINT(rank)
      << PRINT(distance)
      << PRINT(benchmark)
      << PRINT(projection)
      << PRINT(legsStr)
      << endl;
}

void
TwsClient::scannerDataEnd(int reqId)
{
   cout
      << "TwsClient::scannerDataEnd: "
      << PRINT(reqId)
      << endl;
}

void
TwsClient::realtimeBar(TickerId reqId,
                       long time,
                       double open,
                       double high,
                       double low,
                       double close,
                       long volume,
                       double wap,
                       int count)
{
   cout
      << "TwsClient::realtimeBar: "
      << PRINT(reqId)
      << PRINT(time)
      << PRINT(open)
      << PRINT(high)
      << PRINT(low)
      << PRINT(close)
      << PRINT(volume)
      << PRINT(wap)
      << PRINT(count)
      << endl;
}

void
TwsClient::fundamentalData(TickerId reqId, const std::string& data)
{
   cout
      << "TwsClient::fundamentalData: "
      << PRINT(reqId)
      << PRINT(data)
      << endl;
}

void
TwsClient::deltaNeutralValidation(int reqId, const UnderComp& underComp)
{
   cout
      << "TwsClient::deltaNeutralValidation: "
      << PRINT(reqId)
      << endl;
}

void
TwsClient::tickSnapshotEnd(int reqId)
{
   cout
      << "TwsClient::tickSnapshotEnd: "
      << PRINT(reqId)
      << endl;
}

void
TwsClient::marketDataType(TickerId reqId, int marketDataType)
{
   cout
      << "TwsClient::marketDataType: "
      << PRINT(reqId)
      << PRINT(marketDataType)
      << endl;
}

