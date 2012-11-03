#include "posixtestclient.h"

#include "eposixclientsocket.h"
#include "eposixclientsocketplatform.h"

#include "ib/IBString.h"
#include "ib/Contract.h"
#include "ib/Order.h"

#include <iostream>
using std::cout;
using std::endl;

#define PRINT(x) ' ' << #x << '=' << x

const int PING_DEADLINE = 2; // seconds
const int SLEEP_BETWEEN_PINGS = 30; // seconds

///////////////////////////////////////////////////////////
// member funcs
PosixTestClient::PosixTestClient()
	: client_(new EPosixClientSocket(this))
	, state_(ST_CONNECT)
	, sleepDeadline_(0)
	, oid_(0)
{
}

PosixTestClient::~PosixTestClient()
{
}

bool
PosixTestClient::connect(const char *host, unsigned int port, int clientId)
{
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
PosixTestClient::disconnect() const
{
	client_->eDisconnect();

	printf ("Disconnected\n");
}

bool
PosixTestClient::isConnected() const
{
	return client_->isConnected();
}

void
PosixTestClient::processMessages()
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

	if (client_->fd() >= 0 ) {

		FD_ZERO(&readSet);
		errorSet = writeSet = readSet;

		FD_SET(client_->fd(), &readSet);

		if (!client_->isOutBufferEmpty())
			FD_SET(client_->fd(), &writeSet);

		FD_CLR(client_->fd(), &errorSet);

		int ret = select(client_->fd() + 1, &readSet, &writeSet, &errorSet, &tval);

		if (ret == 0) { // timeout
			return;
		}

		if (ret < 0) {	// error
			disconnect();
			return;
		}

		if (client_->fd() < 0)
			return;

		if (FD_ISSET(client_->fd(), &errorSet)) {
			// error on socket
			client_->onError();
		}

		if (client_->fd() < 0)
			return;

		if (FD_ISSET(client_->fd(), &writeSet)) {
			// socket is ready for writing
			client_->onSend();
		}

		if (client_->fd() < 0)
			return;

		if (FD_ISSET(client_->fd(), &readSet)) {
			// socket is ready for reading
			client_->onReceive();
		}
	}
}

//////////////////////////////////////////////////////////////////
// methods
void
PosixTestClient::reqCurrentTime()
{
	printf("Requesting Current Time\n");

	// set ping deadline to "now + n seconds"
	sleepDeadline_ = time(NULL) + PING_DEADLINE;

	state_ = ST_PING_ACK;

	client_->reqCurrentTime();
}

void
PosixTestClient::placeOrder()
{
	Contract contract;
	Order order;

	contract.symbol = "MSFT";
	contract.secType = "STK";
	contract.exchange = "SMART";
	contract.currency = "USD";

	order.action = "BUY";
	order.totalQuantity = 1000;
	order.orderType = "LMT";
	order.lmtPrice = 0.01;

	printf("Placing Order %ld: %s %ld %s at %f\n", oid_, order.action.c_str(), order.totalQuantity, contract.symbol.c_str(), order.lmtPrice);

	state_ = ST_PLACEORDER_ACK;

	client_->placeOrder(oid_, contract, order);
}

void
PosixTestClient::cancelOrder()
{
	printf("Cancelling Order %ld\n", oid_);

	state_ = ST_CANCELORDER_ACK;

	client_->cancelOrder(oid_);
}

///////////////////////////////////////////////////////////////////
// events
void
PosixTestClient::orderStatus(OrderId orderId,
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
PosixTestClient::nextValidId(OrderId orderId)
{
	oid_ = orderId;

	state_ = ST_PLACEORDER;
}

void
PosixTestClient::currentTime(long time)
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
PosixTestClient::error(const int id, const int errorCode, const std::string errorString)
{
	if (id == -1 && errorCode == 1100) // if "Connectivity between IB and TWS has been lost"
		disconnect();
}

void
PosixTestClient::tickPrice(TickerId tickerId,
                           TickType field,
                           double price,
                           int canAutoExecute)
{
   cout
      << "PosixTestClient::tickPrice: "
      << PRINT(tickerId)
      << PRINT(field)
      << PRINT(price)
      << PRINT(canAutoExecute)
      << endl;
}

void
PosixTestClient::tickSize(TickerId tickerId, TickType field, int size)
{
   cout
      << "PosixTestClient::tickSize: "
      << PRINT(tickerId)
      << PRINT(field)
      << PRINT(size)
      << endl;
}

void
PosixTestClient::tickOptionComputation(TickerId tickerId,
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
      << "PosixTestClient::tickOptionComputation: "
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
PosixTestClient::tickGeneric(TickerId tickerId, TickType tickType, double value)
{
   cout
      << "PosixTestClient::tickGeneric: "
      << PRINT(tickerId)
      << PRINT(tickType)
      << PRINT(value)
      << endl;
}

void
PosixTestClient::tickString(TickerId tickerId, TickType tickType, const std::string& value)
{
   cout
      << "PosixTestClient::tickString: "
      << PRINT(tickerId)
      << PRINT(tickType)
      << PRINT(value)
      << endl;
}

void
PosixTestClient::tickEFP(TickerId tickerId,
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
      << "PosixTestClient::tickEFP: "
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
PosixTestClient::openOrder(OrderId orderId,
                           const Contract& c,
                           const Order& o,
                           const OrderState& ostate)
{
   cout
      << "PosixTestClient::openOrder: "
      << PRINT(orderId)
      << endl;
}

void
PosixTestClient::openOrderEnd()
{}

void
PosixTestClient::winError(const std::string& str, int lastError)
{
   cout
      << "PosixTestClient::winError: "
      << PRINT(str)
      << PRINT(lastError)
      << endl;
}

void
PosixTestClient::connectionClosed()
{}

void
PosixTestClient::updateAccountValue(const std::string& key,
                                    const std::string& val,
                                    const std::string& currency,
                                    const std::string& accountName)
{
   cout
      << "PosixTestClient::updateAccountValue: "
      << PRINT(key)
      << PRINT(val)
      << PRINT(currency)
      << PRINT(accountName)
      << endl;
}

void
PosixTestClient::updatePortfolio(const Contract& contract,
                                 int position,
                                 double marketPrice,
                                 double marketValue,
                                 double averageCost,
                                 double unrealizedPNL,
                                 double realizedPNL,
                                 const std::string& accountName)
{
   cout
      << "PosixTestClient::updatePortfolio: "
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
PosixTestClient::updateAccountTime(const std::string& timeStamp)
{
   cout
      << "PosixTestClient::updateAccountTime: "
      << PRINT(timeStamp)
      << endl;
}

void
PosixTestClient::accountDownloadEnd(const std::string& accountName)
{
   cout
      << "PosixTestClient::accountDownloadEnd: "
      << PRINT(accountName)
      << endl;
}

void
PosixTestClient::contractDetails(int reqId, const ContractDetails& contractDetails)
{
   cout
      << "PosixTestClient::contractDetails: "
      << PRINT(reqId)
      << endl;
}

void
PosixTestClient::bondContractDetails(int reqId, const ContractDetails& contractDetails)
{
   cout
      << "PosixTestClient::bondContractDetails: "
      << PRINT(reqId)
      << endl;
}

void
PosixTestClient::contractDetailsEnd(int reqId)
{
   cout
      << "PosixTestClient::contractDetailsEnd: "
      << PRINT(reqId)
      << endl;
}

void
PosixTestClient::execDetails(int reqId, const Contract& contract, const Execution& execution)
{
   cout
      << "PosixTestClient::execDetails: "
      << PRINT(reqId)
      << endl;
}

void
PosixTestClient::execDetailsEnd(int reqId)
{
   cout
      << "PosixTestClient::execDetailsEnd: "
      << PRINT(reqId)
      << endl;
}


void
PosixTestClient::updateMktDepth(TickerId id,
                                int position,
                                int operation,
                                int side,
                                double price,
                                int size)
{
   cout
      << "PosixTestClient::updateMktDepth: "
      << PRINT(id)
      << PRINT(position)
      << PRINT(operation)
      << PRINT(side)
      << PRINT(price)
      << PRINT(size)
      << endl;
}

void
PosixTestClient::updateMktDepthL2(TickerId id,
                                  int position,
                                  std::string marketMaker,
                                  int operation,
                                  int side,
                                  double price,
                                  int size)
{
   cout
      << "PosixTestClient::updateMktDepthL2: "
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
PosixTestClient::updateNewsBulletin(int msgId,
                                    int msgType,
                                    const std::string& newsMessage,
                                    const std::string& originExch)
{
   cout
      << "PosixTestClient::updateNewsBulletin: "
      << PRINT(msgId)
      << PRINT(msgType)
      << PRINT(newsMessage)
      << PRINT(originExch)
      << endl;
}

void
PosixTestClient::managedAccounts(const std::string& accountsList)
{
   cout
      << "PosixTestClient::managedAccounts: "
      << PRINT(accountsList)
      << endl;
}

void
PosixTestClient::receiveFA(faDataType pFaDataType, const std::string& cxml)
{
   cout
      << "PosixTestClient::receiveFA: "
      << PRINT(pFaDataType)
      << PRINT(cxml)
      << endl;
}

void
PosixTestClient::historicalData(TickerId reqId,
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
      << "PosixTestClient::historicalData: "
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
PosixTestClient::scannerParameters(const std::string& xml)
{
   cout
      << "PosixTestClient::scannerParameters: "
      << PRINT(xml)
      << endl;
}

void
PosixTestClient::scannerData(int reqId,
                             int rank,
                             const ContractDetails& contractDetails,
                             const std::string& distance,
                             const std::string& benchmark,
                             const std::string& projection,
                             const std::string& legsStr)
{
   cout
      << "PosixTestClient::scannerData: "
      << PRINT(reqId)
      << PRINT(rank)
      << PRINT(distance)
      << PRINT(benchmark)
      << PRINT(projection)
      << PRINT(legsStr)
      << endl;
}

void
PosixTestClient::scannerDataEnd(int reqId)
{
   cout
      << "PosixTestClient::scannerDataEnd: "
      << PRINT(reqId)
      << endl;
}

void
PosixTestClient::realtimeBar(TickerId reqId,
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
      << "PosixTestClient::realtimeBar: "
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
PosixTestClient::fundamentalData(TickerId reqId, const std::string& data)
{
   cout
      << "PosixTestClient::fundamentalData: "
      << PRINT(reqId)
      << PRINT(data)
      << endl;
}

void
PosixTestClient::deltaNeutralValidation(int reqId, const UnderComp& underComp)
{
   cout
      << "PosixTestClient::deltaNeutralValidation: "
      << PRINT(reqId)
      << endl;
}

void
PosixTestClient::tickSnapshotEnd(int reqId)
{
   cout
      << "PosixTestClient::tickSnapshotEnd: "
      << PRINT(reqId)
      << endl;
}

void
PosixTestClient::marketDataType(TickerId reqId, int marketDataType)
{
   cout
      << "PosixTestClient::marketDataType: "
      << PRINT(reqId)
      << PRINT(marketDataType)
      << endl;
}

