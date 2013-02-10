#ifndef system_logwrapper_h_INCLUDED
#define system_logwrapper_h_INCLUDED

#include "twsapi/common.h"

class TwsSocket;

class LogWrapper : public TwsApi::EWrapper
{

public:

   LogWrapper(bool print = true) : print_(print) {}

protected:

	virtual void accountDownloadEnd(const std::string& accountName);
	virtual void bondContractDetails(int reqId, const TwsApi::ContractDetails& contractDetails);
	virtual void connectionClosed();
	virtual void contractDetails(int reqId, const TwsApi::ContractDetails& contractDetails);
	virtual void contractDetailsEnd(int reqId);
	virtual void currentTime(long time);
	virtual void deltaNeutralValidation(int reqId, const TwsApi::UnderComp& underComp);
	virtual void error(const int id, const int errorCode, const std::string& errorString);
	virtual void execDetails(int reqId, const TwsApi::Contract& contract, const TwsApi::Execution& execution);
	virtual void execDetailsEnd(int reqId);
	virtual void fundamentalData(TwsApi::TickerId reqId, const std::string& data);
	virtual void historicalData(TwsApi::TickerId reqId, const std::string& date, double open, double high, double low, double close, int volume, int barCount, double WAP, int hasGaps);
	virtual void managedAccounts(const std::string& accountsList);
	virtual void marketDataType(TwsApi::TickerId reqId, int marketDataType);
	virtual void nextValidId(TwsApi::OrderId orderId);
	virtual void openOrder(TwsApi::OrderId orderId, const TwsApi::Contract&, const TwsApi::Order&, const TwsApi::OrderState&);
	virtual void openOrderEnd();
	virtual void orderStatus(TwsApi::OrderId orderId, const std::string &status, int filled, int remaining, double avgFillPrice, int permId, int parentId, double lastFillPrice, int clientId, const std::string& whyHeld);
	virtual void realtimeBar(TwsApi::TickerId reqId, long time, double open, double high, double low, double close, long volume, double wap, int count);
	virtual void receiveFA(TwsApi::faDataType pFaDataType, const std::string& cxml);
	virtual void scannerData(int reqId, int rank, const TwsApi::ContractDetails &contractDetails, const std::string &distance, const std::string &benchmark, const std::string &projection, const std::string &legsStr);
	virtual void scannerDataEnd(int reqId);
	virtual void scannerParameters(const std::string &xml);
	virtual void tickEFP(TwsApi::TickerId tickerId, TwsApi::TickType tickType, double basisPoints, const std::string& formattedBasisPoints, double totalDividends, int holdDays, const std::string& futureExpiry, double dividendImpact, double dividendsToExpiry);
	virtual void tickGeneric(TwsApi::TickerId tickerId, TwsApi::TickType tickType, double value);
	virtual void tickOptionComputation(TwsApi::TickerId tickerId, TwsApi::TickType tickType, double impliedVol, double delta, double optPrice, double pvDividend, double gamma, double vega, double theta, double undPrice);
	virtual void tickPrice(TwsApi::TickerId tickerId, TwsApi::TickType field, double price, int canAutoExecute);
	virtual void tickSize(TwsApi::TickerId tickerId, TwsApi::TickType field, int size);
	virtual void tickSnapshotEnd(int reqId);
	virtual void tickString(TwsApi::TickerId tickerId, TwsApi::TickType tickType, const std::string& value);
	virtual void updateAccountTime(const std::string& timeStamp);
	virtual void updateAccountValue(const std::string& key, const std::string& val, const std::string& currency, const std::string& accountName);
	virtual void updateMktDepth(TwsApi::TickerId id, int position, int operation, int side, double price, int size);
	virtual void updateMktDepthL2(TwsApi::TickerId id, int position, std::string marketMaker, int operation, int side, double price, int size);
	virtual void updateNewsBulletin(int msgId, int msgType, const std::string& newsMessage, const std::string& originExch);
	virtual void updatePortfolio(const TwsApi::Contract& contract, int position, double marketPrice, double marketValue, double averageCost, double unrealizedPNL, double realizedPNL, const std::string& accountName);
	virtual void winError(const std::string &str, int lastError);

   IMPLEMENT_ACCESSORS(bool, print);

   virtual TwsSocket& client() const = 0;

private:

   bool print_;
};

#endif // system_logwrapper_h_INCLUDED
