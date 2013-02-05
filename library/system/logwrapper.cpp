#include "system/common.h"
#include "system/logwrapper.h"

#define PRINT(x) ' ' << #x << '=' << x

void
LogWrapper::nextValidId(OrderId orderId)
{
   if (!print_)
      return;

   cout
      << "LogWrapper::nextValidId: "
      << PRINT(orderId)
      << endl;
}


void
LogWrapper::tickPrice(TickerId tickerId,
                     TickType type,
                     double price,
                     int canAutoExecute)
{
   if (!print_)
      return;

   cout
      << "LogWrapper::tickPrice: "
      << PRINT(tickerId)
      << PRINT(type)
      << PRINT(price)
      << PRINT(canAutoExecute)
      << endl;
}

void
LogWrapper::tickSize(TickerId tickerId, TickType type, int size)
{
   if (!print_)
      return;

   cout
      << "LogWrapper::tickSize: "
      << PRINT(tickerId)
      << PRINT(type)
      << PRINT(size)
      << endl;
}

void
LogWrapper::tickGeneric(TickerId tickerId, TickType type, double value)
{
   if (!print_)
      return;

   cout
      << "LogWrapper::tickGeneric: "
      << PRINT(tickerId)
      << PRINT(type)
      << PRINT(value)
      << endl;
}

void
LogWrapper::tickString(TickerId tickerId, TickType type, const std::string& value)
{
   if (!print_)
      return;

   cout
      << "LogWrapper::tickString: "
      << PRINT(tickerId)
      << PRINT(type)
      << PRINT(value)
      << endl;
}

void
LogWrapper::error(const int id, const int errorCode, const std::string errorString)
{
   if (!print_)
      return;

   cout
      << "LogWrapper::error: "
      << PRINT(id)
      << PRINT(errorCode)
      << PRINT(errorString)
      << endl;
}

void
LogWrapper::tickEFP(TickerId tickerId,
                    TickType type,
                    double basisPoints,
                    const std::string& formattedBasisPoints,
                    double totalDividends,
                    int holdDays,
                    const std::string& futureExpiry,
                    double dividendImpact,
                    double dividendsToExpiry)
{
   if (!print_)
      return;

   cout
      << "LogWrapper::tickEFP: "
      << PRINT(tickerId)
      << PRINT(type)
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
LogWrapper::openOrder(OrderId orderId,
                      const Contract& c,
                      const Order& o,
                      const OrderState& ostate)
{
   if (!print_)
      return;

   cout
      << "LogWrapper::openOrder: "
      << PRINT(orderId)
      << endl;
}

void
LogWrapper::openOrderEnd()
{}

void
LogWrapper::winError(const std::string& str, int lastError)
{
   if (!print_)
      return;

   cout
      << "LogWrapper::winError: "
      << PRINT(str)
      << PRINT(lastError)
      << endl;
}

void
LogWrapper::connectionClosed()
{}

void
LogWrapper::updateAccountValue(const std::string& key,
                               const std::string& val,
                               const std::string& currency,
                               const std::string& accountName)
{
   if (!print_)
      return;

   cout
      << "LogWrapper::updateAccountValue: "
      << PRINT(key)
      << PRINT(val)
      << PRINT(currency)
      << PRINT(accountName)
      << endl;
}

void
LogWrapper::updatePortfolio(const Contract& contract,
                            int position,
                            double marketPrice,
                            double marketValue,
                            double averageCost,
                            double unrealizedPNL,
                            double realizedPNL,
                            const std::string& accountName)
{
   if (!print_)
      return;

   cout
      << "LogWrapper::updatePortfolio: "
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
LogWrapper::updateAccountTime(const std::string& timeStamp)
{
   if (!print_)
      return;

   cout
      << "LogWrapper::updateAccountTime: "
      << PRINT(timeStamp)
      << endl;
}

void
LogWrapper::accountDownloadEnd(const std::string& accountName)
{
   if (!print_)
      return;

   cout
      << "LogWrapper::accountDownloadEnd: "
      << PRINT(accountName)
      << endl;
}

void
LogWrapper::contractDetails(int reqId, const ContractDetails& contractDetails)
{
   if (!print_)
      return;

   cout
      << "LogWrapper::contractDetails: "
      << PRINT(reqId)
      << endl;
}

void
LogWrapper::bondContractDetails(int reqId, const ContractDetails& contractDetails)
{
   if (!print_)
      return;

   cout
      << "LogWrapper::bondContractDetails: "
      << PRINT(reqId)
      << endl;
}

void
LogWrapper::contractDetailsEnd(int reqId)
{
   if (!print_)
      return;

   cout
      << "LogWrapper::contractDetailsEnd: "
      << PRINT(reqId)
      << endl;
}

void
LogWrapper::execDetails(int reqId, const Contract& contract, const Execution& execution)
{
   if (!print_)
      return;

   cout
      << "LogWrapper::execDetails: "
      << PRINT(reqId)
      << endl;
}

void
LogWrapper::execDetailsEnd(int reqId)
{
   if (!print_)
      return;

   cout
      << "LogWrapper::execDetailsEnd: "
      << PRINT(reqId)
      << endl;
}


void
LogWrapper::updateMktDepth(TickerId id,
                           int position,
                           int operation,
                           int side,
                           double price,
                           int size)
{
   if (!print_)
      return;

   cout
      << "LogWrapper::updateMktDepth: "
      << PRINT(id)
      << PRINT(position)
      << PRINT(operation)
      << PRINT(side)
      << PRINT(price)
      << PRINT(size)
      << endl;
}

void
LogWrapper::updateMktDepthL2(TickerId id,
                             int position,
                             std::string marketMaker,
                             int operation,
                             int side,
                             double price,
                             int size)
{
   if (!print_)
      return;

   cout
      << "LogWrapper::updateMktDepthL2: "
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
LogWrapper::updateNewsBulletin(int msgId,
                               int msgType,
                               const std::string& newsMessage,
                               const std::string& originExch)
{
   if (!print_)
      return;

   cout
      << "LogWrapper::updateNewsBulletin: "
      << PRINT(msgId)
      << PRINT(msgType)
      << PRINT(newsMessage)
      << PRINT(originExch)
      << endl;
}

void
LogWrapper::managedAccounts(const std::string& accountsList)
{
   if (!print_)
      return;

   cout
      << "LogWrapper::managedAccounts: "
      << PRINT(accountsList)
      << endl;
}

void
LogWrapper::receiveFA(faDataType pFaDataType, const std::string& cxml)
{
   if (!print_)
      return;

   cout
      << "LogWrapper::receiveFA: "
      << PRINT(pFaDataType)
      << PRINT(cxml)
      << endl;
}

void
LogWrapper::historicalData(TickerId reqId,
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
   if (!print_)
      return;

   cout
      << "LogWrapper::historicalData: "
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
LogWrapper::scannerParameters(const std::string& xml)
{
   if (!print_)
      return;

   cout
      << "LogWrapper::scannerParameters: "
      << PRINT(xml)
      << endl;
}

void
LogWrapper::scannerData(int reqId,
                        int rank,
                        const ContractDetails& contractDetails,
                        const std::string& distance,
                        const std::string& benchmark,
                        const std::string& projection,
                        const std::string& legsStr)
{
   if (!print_)
      return;

   cout
      << "LogWrapper::scannerData: "
      << PRINT(reqId)
      << PRINT(rank)
      << PRINT(distance)
      << PRINT(benchmark)
      << PRINT(projection)
      << PRINT(legsStr)
      << endl;
}

void
LogWrapper::scannerDataEnd(int reqId)
{
   if (!print_)
      return;

   cout
      << "LogWrapper::scannerDataEnd: "
      << PRINT(reqId)
      << endl;
}

void
LogWrapper::realtimeBar(TickerId reqId,
                        long time,
                        double open,
                        double high,
                        double low,
                        double close,
                        long volume,
                        double wap,
                        int count)
{
   if (!print_)
      return;

   cout
      << "LogWrapper::realtimeBar: "
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
LogWrapper::fundamentalData(TickerId reqId, const std::string& data)
{
   if (!print_)
      return;

   cout
      << "LogWrapper::fundamentalData: "
      << PRINT(reqId)
      << PRINT(data)
      << endl;
}

void
LogWrapper::deltaNeutralValidation(int reqId, const UnderComp& underComp)
{
   if (!print_)
      return;

   cout
      << "LogWrapper::deltaNeutralValidation: "
      << PRINT(reqId)
      << endl;
}

void
LogWrapper::tickSnapshotEnd(int reqId)
{
   if (!print_)
      return;

   cout
      << "LogWrapper::tickSnapshotEnd: "
      << PRINT(reqId)
      << endl;
}

void
LogWrapper::marketDataType(TickerId reqId, int marketDataType)
{
   if (!print_)
      return;

   cout
      << "LogWrapper::marketDataType: "
      << PRINT(reqId)
      << PRINT(marketDataType)
      << endl;
}

void
LogWrapper::orderStatus(OrderId orderId,
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
   if (!print_)
      return;

   cout
      << "LogWrapper::orderStatus: "
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
LogWrapper::currentTime(long time)
{
   time_t t = (time_t)time;
   struct tm * timeinfo = localtime (&t);
   printf("The current date/time is: %s", asctime(timeinfo));
}

void
LogWrapper::tickOptionComputation(TickerId tickerId,
                                  TickType type,
                                  double impliedVol,
                                  double delta,
                                  double optPrice,
                                  double pvDividend,
                                  double gamma,
                                  double vega,
                                  double theta,
                                  double undPrice)
{
   if (!print_)
      return;

   cout
      << "TwsClient::tickOptionComputation: "
      << PRINT(tickerId)
      << PRINT(type)
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
