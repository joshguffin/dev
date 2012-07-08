#ifndef posixtestclient_h__INCLUDED
#define posixtestclient_h__INCLUDED

#include "EWrapper.h"

#include <memory>

class EPosixClientSocket;

enum State {
	ST_CONNECT,
	ST_PLACEORDER,
	ST_PLACEORDER_ACK,
	ST_CANCELORDER,
	ST_CANCELORDER_ACK,
	ST_PING,
	ST_PING_ACK,
	ST_IDLE
};


class PosixTestClient : public EWrapper
{
public:

	PosixTestClient();
	~PosixTestClient();

	void processMessages();

public:

	bool connect(const char * host, unsigned int port, int clientId = 0);
	void disconnect() const;
	bool isConnected() const;

private:

   void reqCurrentTime();
   void placeOrder();
   void cancelOrder();

public:
   // events
   virtual void tickPrice(TickerId tickerId,
                          TickType field,
                          double price,
                          int canAutoExecute);
   virtual void tickSize(TickerId tickerId,
                         TickType field,
                         int size);
   virtual void tickOptionComputation(TickerId tickerId,
                                      TickType tickType,
                                      double impliedVol,
                                      double delta,
                                      double optPrice,
                                      double pvDividend,
                                      double gamma,
                                      double vega,
                                      double theta,
                                      double undPrice);
   virtual void tickGeneric(TickerId tickerId,
                            TickType tickType,
                            double value);
   virtual void tickString(TickerId tickerId,
                           TickType tickType,
                           const IBString& value);
   virtual void tickEFP(TickerId tickerId,
                        TickType tickType,
                        double basisPoints,
                        const IBString& formattedBasisPoints,
                        double totalDividends,
                        int holdDays,
                        const IBString& futureExpiry,
                        double dividendImpact,
                        double dividendsToExpiry);
   virtual void orderStatus(OrderId orderId,
                            const IBString &status,
                            int filled,
                            int remaining,
                            double avgFillPrice,
                            int permId,
                            int parentId,
                            double lastFillPrice,
                            int clientId,
                            const IBString& whyHeld);
   virtual void openOrder(OrderId orderId,
                          const Contract&,
                          const Order&,
                          const OrderState&);
   virtual void openOrderEnd();
   virtual void winError(const IBString &str,
                         int lastError);
   virtual void connectionClosed();
   virtual void updateAccountValue(const IBString& key,
                                   const IBString& val,
                                   const IBString& currency,
                                   const IBString& accountName);
   virtual void updatePortfolio(const Contract& contract,
                                int position,
                                double marketPrice,
                                double marketValue,
                                double averageCost,
                                double unrealizedPNL,
                                double realizedPNL,
                                const IBString& accountName);
   virtual void updateAccountTime(const IBString& timeStamp);
   virtual void accountDownloadEnd(const IBString& accountName);
   virtual void nextValidId(OrderId orderId);
   virtual void contractDetails(int reqId,
                                const ContractDetails& contractDetails);
   virtual void bondContractDetails(int reqId,
                                    const ContractDetails& contractDetails);
   virtual void contractDetailsEnd(int reqId);
   virtual void execDetails(int reqId,
                            const Contract& contract,
                            const Execution& execution);
   virtual void execDetailsEnd(int reqId);
   virtual void error(const int id,
                      const int errorCode,
                      const IBString errorString);
   virtual void updateMktDepth(TickerId id,
                               int position,
                               int operation,
                               int side,
                               double price,
                               int size);
   virtual void updateMktDepthL2(TickerId id,
                                 int position,
                                 IBString marketMaker,
                                 int operation,
                                 int side,
                                 double price,
                                 int size);
   virtual void updateNewsBulletin(int msgId,
                                   int msgType,
                                   const IBString& newsMessage,
                                   const IBString& originExch);
   virtual void managedAccounts(const IBString& accountsList);
   virtual void receiveFA(faDataType pFaDataType,
                          const IBString& cxml);
   virtual void historicalData(TickerId reqId,
                               const IBString& date,
                               double open,
                               double high,
                               double low,
                               double close,
                               int volume,
                               int barCount,
                               double WAP,
                               int hasGaps);
   virtual void scannerParameters(const IBString &xml);
   virtual void scannerData(int reqId,
                            int rank,
                            const ContractDetails &contractDetails,
                            const IBString &distance,
                            const IBString &benchmark,
                            const IBString &projection,
                            const IBString &legsStr);
   virtual void scannerDataEnd(int reqId);
   virtual void realtimeBar(TickerId reqId,
                            long time,
                            double open,
                            double high,
                            double low,
                            double close,
                            long volume,
                            double wap,
                            int count);
   virtual void currentTime(long time);
   virtual void fundamentalData(TickerId reqId, const IBString& data);
   virtual void deltaNeutralValidation(int reqId, const UnderComp& underComp);
   virtual void tickSnapshotEnd(int reqId);
   virtual void marketDataType(TickerId reqId, int marketDataType);
   virtual void commissionReport( const CommissionReport& commissionReport);

private:

	std::auto_ptr<EPosixClientSocket> m_pClient;
	State m_state;
	time_t m_sleepDeadline;

	OrderId m_orderId;
};

#endif

