#include "system/common.h"
#include "system/logwrapper.h"

#define PRINT(x) ' ' << #x << '=' << x

namespace SystemLib {

void
LogWrapper::nextValidId(TwsApi::OrderId orderId)
{
   if (!print_)
      return;

   LOG
      << "LogWrapper::nextValidId: "
      << PRINT(orderId)
      << endm;
}


void
LogWrapper::tickPrice(TwsApi::TickerId tickerId,
                     TwsApi::TickType type,
                     double price,
                     int canAutoExecute)
{
   if (!print_)
      return;

   LOG
      << "LogWrapper::tickPrice: "
      << PRINT(tickerId)
      << PRINT(type)
      << PRINT(price)
      << PRINT(canAutoExecute)
      << endm;
}

void
LogWrapper::tickSize(TwsApi::TickerId tickerId, TwsApi::TickType type, int size)
{
   if (!print_)
      return;

   LOG
      << "LogWrapper::tickSize: "
      << PRINT(tickerId)
      << PRINT(type)
      << PRINT(size)
      << endm;
}

void
LogWrapper::tickGeneric(TwsApi::TickerId tickerId, TwsApi::TickType type, double value)
{
   if (!print_)
      return;

   LOG
      << "LogWrapper::tickGeneric: "
      << PRINT(tickerId)
      << PRINT(type)
      << PRINT(value)
      << endm;
}

void
LogWrapper::tickString(TwsApi::TickerId tickerId, TwsApi::TickType type, const std::string& value)
{
   if (!print_)
      return;

   LOG
      << "LogWrapper::tickString: "
      << PRINT(tickerId)
      << PRINT(type)
      << PRINT(value)
      << endm;
}

void
LogWrapper::error(const int id, const int errorCode, const std::string& errorString)
{
   if (!print_)
      return;

   LOG
      << "LogWrapper::error: "
      << PRINT(id)
      << PRINT(errorCode)
      << PRINT(errorString)
      << endm;
}

void
LogWrapper::tickEFP(TwsApi::TickerId tickerId,
                    TwsApi::TickType type,
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

   LOG
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
      << endm;
}

void
LogWrapper::openOrder(TwsApi::OrderId orderId,
                      const TwsApi::Contract& contract,
                      const TwsApi::Order& order,
                      const TwsApi::OrderState& state)
{
   if (!print_)
      return;

   LOG
      << "LogWrapper::openOrder: "
      << PRINT(orderId)
      << PRINT(contract)
      << PRINT(state) << '\n'
      << PRINT(order)
      << endm;
}

void
LogWrapper::openOrderEnd()
{
   LOG << "LogWrapper::openOrderEnd" << endm;
}

void
LogWrapper::winError(const std::string& str, int lastError)
{
   if (!print_)
      return;

   LOG
      << "LogWrapper::winError: "
      << PRINT(str)
      << PRINT(lastError)
      << endm;
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

   LOG
      << "LogWrapper::updateAccountValue: "
      << PRINT(key)
      << PRINT(val)
      << PRINT(currency)
      << PRINT(accountName)
      << endm;
}

void
LogWrapper::updatePortfolio(const TwsApi::Contract& contract,
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

   LOG
      << "LogWrapper::updatePortfolio: "
      << PRINT(contract)
      << PRINT(position)
      << PRINT(marketPrice)
      << PRINT(marketValue)
      << PRINT(averageCost)
      << PRINT(unrealizedPNL)
      << PRINT(realizedPNL)
      << PRINT(accountName)
      << endm;
}

void
LogWrapper::updateAccountTime(const std::string& timeStamp)
{
   if (!print_)
      return;

   LOG
      << "LogWrapper::updateAccountTime: "
      << PRINT(timeStamp)
      << endm;
}

void
LogWrapper::accountDownloadEnd(const std::string& accountName)
{
   if (!print_)
      return;

   LOG
      << "LogWrapper::accountDownloadEnd: "
      << PRINT(accountName)
      << endm;
}

void
LogWrapper::contractDetails(int reqId, const TwsApi::ContractDetails& contractDetails)
{
   if (!print_)
      return;

   LOG
      << "LogWrapper::contractDetails: "
      << PRINT(reqId)
      << endm;
}

void
LogWrapper::bondContractDetails(int reqId, const TwsApi::ContractDetails& contractDetails)
{
   if (!print_)
      return;

   LOG
      << "LogWrapper::bondContractDetails: "
      << PRINT(reqId)
      << endm;
}

void
LogWrapper::contractDetailsEnd(int reqId)
{
   if (!print_)
      return;

   LOG
      << "LogWrapper::contractDetailsEnd: "
      << PRINT(reqId)
      << endm;
}

void
LogWrapper::execDetails(int reqId, const TwsApi::Contract& contract, const TwsApi::Execution& execution)
{
   if (!print_)
      return;

   LOG
      << "LogWrapper::execDetails: "
      << PRINT(reqId)
      << endm;
}

void
LogWrapper::execDetailsEnd(int reqId)
{
   if (!print_)
      return;

   LOG
      << "LogWrapper::execDetailsEnd: "
      << PRINT(reqId)
      << endm;
}

void
LogWrapper::updateMktDepth(TwsApi::TickerId id,
                           int position,
                           int operation,
                           int side,
                           double price,
                           int size)
{
   if (!print_)
      return;

   LOG
      << "LogWrapper::updateMktDepth: "
      << PRINT(id)
      << PRINT(position)
      << PRINT(operation)
      << PRINT(side)
      << PRINT(price)
      << PRINT(size)
      << endm;
}

void
LogWrapper::updateMktDepthL2(TwsApi::TickerId id,
                             int position,
                             std::string marketMaker,
                             int operation,
                             int side,
                             double price,
                             int size)
{
   if (!print_)
      return;

   LOG
      << "LogWrapper::updateMktDepthL2: "
      << PRINT(id)
      << PRINT(position)
      << PRINT(marketMaker)
      << PRINT(operation)
      << PRINT(side)
      << PRINT(price)
      << PRINT(size)
      << endm;
}

void
LogWrapper::updateNewsBulletin(int msgId,
                               int msgType,
                               const std::string& newsMessage,
                               const std::string& originExch)
{
   if (!print_)
      return;

   LOG
      << "LogWrapper::updateNewsBulletin: "
      << PRINT(msgId)
      << PRINT(msgType)
      << PRINT(newsMessage)
      << PRINT(originExch)
      << endm;
}

void
LogWrapper::managedAccounts(const std::string& accountsList)
{
   if (!print_)
      return;

   LOG
      << "LogWrapper::managedAccounts: "
      << PRINT(accountsList)
      << endm;
}

void
LogWrapper::receiveFA(TwsApi::faDataType pFaDataType, const std::string& cxml)
{
   if (!print_)
      return;

   LOG
      << "LogWrapper::receiveFA: "
      << PRINT(pFaDataType)
      << PRINT(cxml)
      << endm;
}

void
LogWrapper::historicalData(TwsApi::TickerId reqId,
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

   LOG
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
      << endm;
}

void
LogWrapper::scannerParameters(const std::string& xml)
{
   if (!print_)
      return;

   LOG
      << "LogWrapper::scannerParameters: "
      << PRINT(xml)
      << endm;
}

void
LogWrapper::scannerData(int reqId,
                        int rank,
                        const TwsApi::ContractDetails& contractDetails,
                        const std::string& distance,
                        const std::string& benchmark,
                        const std::string& projection,
                        const std::string& legsStr)
{
   if (!print_)
      return;

   LOG
      << "LogWrapper::scannerData: "
      << PRINT(reqId)
      << PRINT(rank)
      << PRINT(distance)
      << PRINT(benchmark)
      << PRINT(projection)
      << PRINT(legsStr)
      << endm;
}

void
LogWrapper::scannerDataEnd(int reqId)
{
   if (!print_)
      return;

   LOG
      << "LogWrapper::scannerDataEnd: "
      << PRINT(reqId)
      << endm;
}

void
LogWrapper::realtimeBar(TwsApi::TickerId reqId,
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

   LOG
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
      << endm;
}

void
LogWrapper::fundamentalData(TwsApi::TickerId reqId, const std::string& data)
{
   if (!print_)
      return;

   LOG
      << "LogWrapper::fundamentalData: "
      << PRINT(reqId)
      << PRINT(data)
      << endm;
}

void
LogWrapper::deltaNeutralValidation(int reqId, const TwsApi::UnderComp& underComp)
{
   if (!print_)
      return;

   LOG
      << "LogWrapper::deltaNeutralValidation: "
      << PRINT(reqId)
      << endm;
}

void
LogWrapper::tickSnapshotEnd(int reqId)
{
   if (!print_)
      return;

   LOG
      << "LogWrapper::tickSnapshotEnd: "
      << PRINT(reqId)
      << endm;
}

void
LogWrapper::marketDataType(TwsApi::TickerId reqId, int marketDataType)
{
   if (!print_)
      return;

   LOG
      << "LogWrapper::marketDataType: "
      << PRINT(reqId)
      << PRINT(marketDataType)
      << endm;
}

void
LogWrapper::orderStatus(TwsApi::OrderId orderId,
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

   LOG
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
      << endm;
}

void
LogWrapper::currentTime(long time)
{
   time_t t = (time_t)time;
   struct tm * timeinfo = localtime (&t);
   printf("The current date/time is: %s", asctime(timeinfo));
}

void
LogWrapper::tickOptionComputation(TwsApi::TickerId tickerId,
                                  TwsApi::TickType type,
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

   LOG
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
      << endm;
}

} // end of namespace SystemLib
