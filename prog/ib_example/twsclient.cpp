#include "system/common.h"

// library headers
#include "twsapi/common.h"

// local headers
#include "twsclient.h"

#define PRINT(x) ' ' << #x << '=' << x

const int SLEEP_BETWEEN_PINGS = 30; // seconds

///////////////////////////////////////////////////////////
// member funcs
TwsClient::TwsClient()
	: oid_(0)
{
}

TwsClient::~TwsClient()
{
}

void
TwsClient::processMessages()
{
   TwsClientBase::processMessages();

   static int i = 0;
   if (i == 2) {
      Contract contract;

      contract.symbol   = "AAPL";
      contract.secType  = "STK";
      contract.exchange = "SMART";
      contract.currency = "USD";
      socket().reqMktData(1, contract, "221,165,236,258", false);
   }

   i++;
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

   cout
      << "Placing order " << oid_
      << ' ' << order.action.c_str()
      << ' ' << contract.symbol.c_str()
      << ' ' << order.totalQuantity
      << '@' << order.lmtPrice
      << endl;

   //client_->placeOrder(oid_, contract, order);
   socket().reqMktData(1, contract, "221,165,236,258", false);
}

void
TwsClient::cancelOrder()
{
   cout << "Cancelling Order " << oid_ << endl;

   socket().cancelOrder(oid_);
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
      socket().disconnect();
}

void
TwsClient::nextValidId(OrderId orderId)
{
   oid_ = orderId;
}

void
TwsClient::tickPrice(TickerId tickerId,
                     TickType type,
                     double price,
                     int canAutoExecute)
{
   cout
      << "TwsClient::tickPrice: "
      << PRINT(tickerId)
      << PRINT(type)
      << PRINT(price)
      << PRINT(canAutoExecute)
      << endl;
}

void
TwsClient::tickSize(TickerId tickerId, TickType type, int size)
{
   cout
      << "TwsClient::tickSize: "
      << PRINT(tickerId)
      << PRINT(type)
      << PRINT(size)
      << endl;
}

void
TwsClient::tickGeneric(TickerId tickerId, TickType type, double value)
{
   cout
      << "TwsClient::tickGeneric: "
      << PRINT(tickerId)
      << PRINT(type)
      << PRINT(value)
      << endl;
}

void
TwsClient::tickString(TickerId tickerId, TickType type, const std::string& value)
{
   cout
      << "TwsClient::tickString: "
      << PRINT(tickerId)
      << PRINT(type)
      << PRINT(value)
      << endl;
}

