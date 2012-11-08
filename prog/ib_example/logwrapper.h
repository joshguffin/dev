#ifndef logwrapper_h_INCLUDED
#define logwrapper_h_INCLUDED

#include "twsapi/EWrapper.h"

using namespace TwsApi;

class LogWrapper : public EWrapper
{
	virtual void accountDownloadEnd(const std::string& accountName);
	virtual void bondContractDetails(int reqId, const ContractDetails& contractDetails);
	virtual void connectionClosed();
	virtual void contractDetails(int reqId, const ContractDetails& contractDetails);
	virtual void contractDetailsEnd(int reqId);
	virtual void currentTime(long time);
	virtual void deltaNeutralValidation(int reqId, const UnderComp& underComp);
	virtual void execDetails(int reqId, const Contract& contract, const Execution& execution);
	virtual void execDetailsEnd(int reqId);
	virtual void fundamentalData(TickerId reqId, const std::string& data);
	virtual void historicalData(TickerId reqId, const std::string& date, double open, double high, double low, double close, int volume, int barCount, double WAP, int hasGaps);
	virtual void managedAccounts(const std::string& accountsList);
	virtual void marketDataType(TickerId reqId, int marketDataType);
	virtual void openOrder(OrderId orderId, const Contract&, const Order&, const OrderState&);
	virtual void openOrderEnd();
	virtual void orderStatus(OrderId orderId, const std::string &status, int filled, int remaining, double avgFillPrice, int permId, int parentId, double lastFillPrice, int clientId, const std::string& whyHeld);
	virtual void realtimeBar(TickerId reqId, long time, double open, double high, double low, double close, long volume, double wap, int count);
	virtual void receiveFA(faDataType pFaDataType, const std::string& cxml);
	virtual void scannerData(int reqId, int rank, const ContractDetails &contractDetails, const std::string &distance, const std::string &benchmark, const std::string &projection, const std::string &legsStr);
	virtual void scannerDataEnd(int reqId);
	virtual void scannerParameters(const std::string &xml);
	virtual void tickEFP(TickerId tickerId, TickType tickType, double basisPoints, const std::string& formattedBasisPoints, double totalDividends, int holdDays, const std::string& futureExpiry, double dividendImpact, double dividendsToExpiry);
	virtual void tickOptionComputation(TickerId tickerId, TickType tickType, double impliedVol, double delta, double optPrice, double pvDividend, double gamma, double vega, double theta, double undPrice);
	virtual void tickSnapshotEnd(int reqId);
	virtual void updateAccountTime(const std::string& timeStamp);
	virtual void updateAccountValue(const std::string& key, const std::string& val, const std::string& currency, const std::string& accountName);
	virtual void updateMktDepth(TickerId id, int position, int operation, int side, double price, int size);
	virtual void updateMktDepthL2(TickerId id, int position, std::string marketMaker, int operation, int side, double price, int size);
	virtual void updateNewsBulletin(int msgId, int msgType, const std::string& newsMessage, const std::string& originExch);
	virtual void updatePortfolio(const Contract& contract, int position, double marketPrice, double marketValue, double averageCost, double unrealizedPNL, double realizedPNL, const std::string& accountName);
	virtual void winError(const std::string &str, int lastError);
};

#endif // logwrapper_h_INCLUDED
