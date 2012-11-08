#include "system/common.h"

// library headers
#include "twsapi/IBString.h"
#include "twsapi/Contract.h"
#include "twsapi/Order.h"
#include "twsapi/EClientSocketBaseImpl.h"

// local headers
#include "twssocket.h"
#include "twsclient.h"

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

   static int i = 0;
   if (i == 2) {
      Contract contract;

      contract.symbol   = "AAPL";
      contract.secType  = "STK";
      contract.exchange = "SMART";
      contract.currency = "USD";
      client_->reqMktData(1, contract, "221,165,236,258", false);
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
   client_->reqMktData(1, contract, "221,165,236,258", false);
}

void
TwsClient::cancelOrder()
{
   cout << "Cancelling Order " << oid_ << endl;

   client_->cancelOrder(oid_);
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

