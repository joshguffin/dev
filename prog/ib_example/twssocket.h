#ifndef twssocket_h_INCLUDED
#define twssocket_h_INCLUDED

#include "twsapi/EClientSocketBase.h"

namespace TwsApi {
class EWrapper;
}

class TwsSocket : public TwsApi::EClientSocketBase
{
public:

	TwsSocket(TwsApi::EWrapper& ptr);
	~TwsSocket();

	bool isSocketOK() const;
   void processMessages();

   bool connect(const std::string& host, unsigned port);
   void disconnect();

private:

	virtual int send(const char* buf, size_t sz);
	virtual int receive(char* buf, size_t sz);

/*
	// override virtual funcs from EClient
	virtual int serverVersion();
	virtual IBString TwsConnectionTime();
	virtual void reqMktData(TickerId id, const Contract &contract, const IBString &genericTicks, bool snapshot);
	virtual void cancelMktData(TickerId id);
	virtual void placeOrder(OrderId id, const Contract &contract, const Order &order);
	virtual void cancelOrder(OrderId id) ;
	virtual void reqOpenOrders();
	virtual void reqAccountUpdates(bool subscribe, const IBString& acctCode);
	virtual void reqExecutions(int reqId, const ExecutionFilter& filter);
	virtual void reqIds(int numIds);
	virtual bool checkMessages();
	virtual void reqContractDetails(int reqId, const Contract &contract);
	virtual void reqMktDepth(TickerId tickerId, const Contract &contract, int numRows);
	virtual void cancelMktDepth(TickerId tickerId);
	virtual void reqNewsBulletins(bool allMsgs);
	virtual void cancelNewsBulletins();
	virtual void setServerLogLevel(int level);
	virtual void reqAutoOpenOrders(bool bAutoBind);
	virtual void reqAllOpenOrders();
	virtual void reqManagedAccts();
	virtual void requestFA(faDataType pFaDataType);
	virtual void replaceFA(faDataType pFaDataType, const IBString& cxml);
	virtual void reqHistoricalData(TickerId id, const Contract &contract, const IBString &endDateTime, const IBString &durationStr, const IBString & barSizeSetting, const IBString &whatToShow, int useRTH, int formatDate);
	virtual void exerciseOptions(TickerId tickerId, const Contract &contract, int exerciseAction, int exerciseQuantity, const IBString &account, int override);
	virtual void cancelHistoricalData(TickerId tickerId );
	virtual void reqRealTimeBars(TickerId id, const Contract &contract, int barSize, const IBString &whatToShow, bool useRTH);
	virtual void cancelRealTimeBars(TickerId tickerId );
	virtual void cancelScannerSubscription(int tickerId);
	virtual void reqScannerParameters();
	virtual void reqScannerSubscription(int tickerId, const ScannerSubscription &subscription);
	virtual void reqCurrentTime();
	virtual void reqFundamentalData(TickerId reqId, const Contract&, const IBString& reportType);
	virtual void cancelFundamentalData(TickerId reqId);
	virtual void calculateImpliedVolatility(TickerId reqId, const Contract &contract, double optionPrice, double underPrice);
	virtual void calculateOptionPrice(TickerId reqId, const Contract &contract, double volatility, double underPrice);
	virtual void cancelCalculateImpliedVolatility(TickerId reqId);
	virtual void cancelCalculateOptionPrice(TickerId reqId);
	virtual void reqGlobalCancel();
	virtual void reqMarketDataType(int marketDataType);
*/

	virtual bool eConnect(const char* host, unsigned int port, int clientId=0);
	virtual void eDisconnect();

private:

	// callback from socket
	void onReceive();
	void onSend();
	void onError();

public:
	// helper
	bool handleSocketError();

private:

   TwsApi::EWrapper& wrapper_;
	time_t sleepDeadline_;
	int fd_;
};

#endif // twssocket_h_INCLUDED
