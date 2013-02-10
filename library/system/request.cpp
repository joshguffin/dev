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
Request::Add(Consumer& consumer)
{
   const RequestKey& key = consumer.key();
   RequestPtr& pt = Keys()[key];
   if (!pt) {
      pt.reset(new Request(key));
      TwsApi::TickerId id = pt->tid_;
      Tickers()[id] = pt;
   }

   pt->consumers_.insert(&consumer);
}

void
Request::Remove(Consumer& consumer)
{
   KeyStore& store = Keys();

   const RequestKey& key  = consumer.key();
   KeyStore::iterator loc = store.find(key);
   RequestPtr& pt         = loc->second;

   pt->consumers_.erase(&consumer);

   if (pt->consumers_.empty()) {

      TickerStore& tickers       = Tickers();
      TickerStore::iterator tloc = tickers.find(pt->tid_);
      if (tloc != tickers.end())
         tickers.erase(tloc);

      TwsSystem::Instance().cancelMarketData(*pt);
      store.erase(loc);
   }
}

void
Request::Tick(TwsApi::TickerId tid, const Failure& reason)
{
   TickerStore& tickers = Tickers();

   TickerStore::iterator loc = tickers.find(tid);
   if (loc == tickers.end()) {
      LOG
         << "Request::Tick: ticker " << tid << " not found (failure "
         << reason << ')'
         << endm;
      return;
   }

   RequestPtr& request = loc->second;
   request->notify(reason);
}

Request::Request(const RequestKey& key)
   : key_(key)
   , tid_(-1)
{
   tid_ = TwsSystem::Instance().requestMarketData(*this);
}

const TwsApi::Contract&
Request::contract() const
{
   return key_.contract();
}

// --- Tick handling -----------------------------------------------------------

#define HANDLE_CASE(name, member, function) \
   case TwsApi::name:                       \
      member.function(value);               \
      if (member.valid())                   \
         notify(member);                    \
      return;

void
Request::update(TwsApi::TickType type, int value)
{
   switch (type) {
      HANDLE_CASE(BID_SIZE   , bidask_    , bidSize);
      HANDLE_CASE(ASK_SIZE   , bidask_    , askSize);
      HANDLE_CASE(LAST_SIZE  , last_      , size);
      HANDLE_CASE(VOLUME     , stats_     , volume);
      HANDLE_CASE(HALTED     , state_     , halted);
      HANDLE_CASE(AVG_VOLUME , histStats_ , averageVolume);
   }
}

void
Request::update(TwsApi::TickType type, double value)
{
   switch (type) {
      HANDLE_CASE(LAST         , last_      , price);
      HANDLE_CASE(BID          , bidask_    , bid);
      HANDLE_CASE(ASK          , bidask_    , ask);
      HANDLE_CASE(HIGH         , stats_     , high);
      HANDLE_CASE(LOW          , stats_     , low);
      HANDLE_CASE(MARK_PRICE   , mark_      , price);
      HANDLE_CASE(OPEN_PRICE   , open_      , price);
      HANDLE_CASE(CLOSE_PRICE  , close_     , price);
      HANDLE_CASE(LOW_13_WEEK  , histStats_ , lo13wk);
      HANDLE_CASE(LOW_26_WEEK  , histStats_ , lo26wk);
      HANDLE_CASE(LOW_52_WEEK  , histStats_ , lo52wk);
      HANDLE_CASE(HIGH_13_WEEK , histStats_ , hi13wk);
      HANDLE_CASE(HIGH_26_WEEK , histStats_ , hi26wk);
      HANDLE_CASE(HIGH_52_WEEK , histStats_ , hi52wk);
      HANDLE_CASE(SHORTABLE    , state_     , shortable);
      HANDLE_CASE(TRADE_COUNT  , stats_     , tradeCount);
      HANDLE_CASE(TRADE_RATE   , stats_     , tradeRate);
      HANDLE_CASE(VOLUME_RATE  , stats_     , volumeRate);
      HANDLE_CASE(RT_VOLUME    , stats_     , realTimeVolume);
   }
}

void
Request::update(TwsApi::TickType type, const std::string& value)
{
   switch (type) {
      HANDLE_CASE(LAST_TIMESTAMP     , last_         , setTime);
      HANDLE_CASE(FUNDAMENTAL_RATIOS , fundamentals_ , vals);
   }
   cout << "Request::update: " << value << endl;
}

#undef HANDLE_CASE
