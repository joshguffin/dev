#include "system/common.h"
#include "system/request.h"

Request::KeyStore&
Request::Keys()
{
   static KeyStore keys;
   return keys;
}

Request::TickerStore&
Request::Tickers()
{
   static TickerStore tickers;
   return tickers;
}

void
Request::update(TickType type, int value)
{
   switch (type) {
      case LAST_SIZE:
         last_.size(value);
         notify(last_);
         return;
      case BID_SIZE:
         bidask_.bidSize(value);
         notify(bidask_);
         return;
      case ASK_SIZE:
         bidask_.askSize(value);
         notify(bidask_);
   }
}

void
Request::update(TickType type, double value)
{
   switch (type) {
      case LAST:
         last_.price(value);
         notify(last_);
         return;
      case BID:
         bidask_.bid(value);
         notify(bidask_);
         return;
      case ASK:
         bidask_.ask(value);
         notify(bidask_);
   }
}

void
Request::update(TickType type, const std::string& value)
{
   cout << "Request::update: " << value << endl;
}

Request::Request(const RequestKey& key)
   : key_(key)
{
   const TwsApi::Contract& contract = key.contract();
   tid_ = TwsSystem::Instance().requestMarketData(contract);
}
