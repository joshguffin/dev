#include "system/common.h"
#include "system/datawrapper.h"
#include "system/request.h"

int
DataWrapper::requestMarketData(const Request& request) const
{
   static int id = 0;
   const TwsApi::Contract& contract = request.contract();
   client().reqMktData(++id, contract, "104,165,221,236", false);
   return id;
}

void
DataWrapper::cancelMarketData(const Request& request) const
{
   client().cancelMktData(request.tid());
}

void
DataWrapper::tickPrice(TwsApi::TickerId id, TwsApi::TickType type, double value, int autoex)
{
   Request::Tick(id, type, value);
}

void
DataWrapper::tickSize(TwsApi::TickerId id, TwsApi::TickType type, int value)
{
   Request::Tick(id, type, value);
}

void
DataWrapper::tickGeneric(TwsApi::TickerId id, TwsApi::TickType type, double value)
{
   Request::Tick(id, type, value);
}

void
DataWrapper::tickString(TwsApi::TickerId id, TwsApi::TickType type, const std::string& value)
{
   cout << "String: " << id << ' ' << type << ' ' << value << endl;
   Request::Tick(id, type, value);
}

void
DataWrapper::failed(TwsApi::TickerId id, const std::string& reason, int code)
{
   Request::Failure fail(reason, code);
   Request::Tick(id, fail);
}

