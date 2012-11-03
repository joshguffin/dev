
// library headers
#include "ib/IBString.h"
#include "ib/Contract.h"
#include "ib/Order.h"

// local headers
#include "eposixclientsocket.h"
#include "posixtestclient.h"

#include <iostream>
using std::cout;
using std::endl;

#define PRINT(x) ' ' << #x << '=' << x

const int PING_DEADLINE = 2; // seconds
const int SLEEP_BETWEEN_PINGS = 30; // seconds

///////////////////////////////////////////////////////////
// member funcs
TwsClient::TwsClient()
	: client_(new TwsSocket(*this))
	, state_(ST_CONNECT)
	, sleepDeadline_(0)
	, oid_(0)
{
}

TwsClient::~TwsClient()
{
}

bool
TwsClient::connect(const char *host, unsigned int port, int clientId)
{
   if (isConnected())
      return true;

   // trying to connect
   printf("Connecting to %s:%d clientId:%d\n", !(host && *host) ? "127.0.0.1" : host, port, clientId);

   bool bRes = client_->eConnect(host, port, clientId);

   if (bRes) {
      printf("Connected to %s:%d clientId:%d\n", !(host && *host) ? "127.0.0.1" : host, port, clientId);
   }
   else
      printf("Cannot connect to %s:%d clientId:%d\n", !(host && *host) ? "127.0.0.1" : host, port, clientId);

   return bRes;
}

void
TwsClient::disconnect() const
{
   client_->eDisconnect();

   printf ("Disconnected\n");
}

bool
TwsClient::isConnected() const
{
   return client_->isConnected();
}

void
TwsClient::processMessages()
{
   fd_set readSet, writeSet, errorSet;

   struct timeval tval;
   tval.tv_usec = 0;
   tval.tv_sec = 0;

   time_t now = time(NULL);

   switch (state_) {
      case ST_PLACEORDER:
         placeOrder();
         break;
      case ST_PLACEORDER_ACK:
         break;
      case ST_CANCELORDER:
         cancelOrder();
         break;
      case ST_CANCELORDER_ACK:
         break;
      case ST_PING:
         reqCurrentTime();
         break;
      case ST_PING_ACK:
         if (sleepDeadline_ < now) {
            disconnect();
            return;
         }
         break;
      case ST_IDLE:
         if (sleepDeadline_ < now) {
            state_ = ST_PING;
            return;
         }
         break;
   }

   if (sleepDeadline_ > 0) {
      // initialize timeout with sleepDeadline_ - now
      tval.tv_sec = sleepDeadline_ - now;
   }

   if (client_->fd() < 0 )
      return;

   FD_ZERO(&readSet);
   errorSet = writeSet = readSet;

   FD_SET(client_->fd(), &readSet);

   if (!client_->isOutBufferEmpty())
      FD_SET(client_->fd(), &writeSet);

   FD_CLR(client_->fd(), &errorSet);

   int ret = select(client_->fd() + 1, &readSet, &writeSet, &errorSet, &tval);

   // timeout
   if (ret == 0)
      return;

   if (ret < 0) {	// error
      disconnect();
      return;
   }

   if (client_->fd() < 0)
      return;

   int socketError = FD_ISSET(client_->fd(), &errorSet);
   if (socketError)
      client_->onError();

   if (client_->fd() < 0)
      return;

   int writeReady = FD_ISSET(client_->fd(), &writeSet);
   if (writeReady)
      client_->onSend();

   if (client_->fd() < 0)
      return;

   int readReady = FD_ISSET(client_->fd(), &readSet);
   if (readReady)
      client_->onReceive();
}

//////////////////////////////////////////////////////////////////
// methods
void
TwsClient::reqCurrentTime()
{
   printf("Requesting Current Time\n");

   // set ping deadline to "now + n seconds"
   sleepDeadline_ = time(NULL) + PING_DEADLINE;

   state_ = ST_PING_ACK;

   client_->reqCurrentTime();
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

   state_ = ST_PLACEORDER_ACK;

   //client_->placeOrder(oid_, contract, order);
   client_->reqMktData(1, contract, "221,165,236,258", false);
}

void
TwsClient::cancelOrder()
{
   printf("Cancelling Order %ld\n", oid_);

   state_ = ST_CANCELORDER_ACK;

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
   if (orderId == oid_) {
      if (state_ == ST_PLACEORDER_ACK && (status == "PreSubmitted" || status == "Submitted"))
         state_ = ST_CANCELORDER;

      if (state_ == ST_CANCELORDER_ACK && status == "Cancelled")
         state_ = ST_PING;

      printf("Order: id=%ld, status=%s\n", orderId, status.c_str());
   }
}

void
TwsClient::nextValidId(OrderId orderId)
{
   oid_ = orderId;

   state_ = ST_PLACEORDER;
}

void
TwsClient::currentTime(long time)
{
   if (state_ == ST_PING_ACK) {
      time_t t = (time_t)time;
      struct tm * timeinfo = localtime (&t);
      printf("The current date/time is: %s", asctime(timeinfo));

      time_t now = ::time(NULL);
      sleepDeadline_ = now + SLEEP_BETWEEN_PINGS;

      state_ = ST_IDLE;
   }
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
      disconnect();
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

