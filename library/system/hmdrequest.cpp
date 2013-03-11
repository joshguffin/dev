#include "system/common.h"
#include "system/hmdrequest.h"

namespace SystemLib {

HmdRequest::KeyStore&
HmdRequest::Keys()
{
   static KeyStore keys;
   return keys;
}

HmdRequest::TickerStore&
HmdRequest::Tickers()
{
   static TickerStore tickers;
   return tickers;
}

void
HmdRequest::Done(TwsApi::TickerId tid)
{
   TickerStore tickers = Tickers();
   TickerStore::iterator loc = tickers.find(tid);
   if (tickers.end() == loc)
      return;

   HmdRequestPtr& pt = loc->second;

   HmdRequest::Consumers::iterator it  = pt->consumers_.begin();
   HmdRequest::Consumers::iterator end = pt->consumers_.end();

   const HmdResult& result = pt->bars_;
   for (; it != end; ++it)
      (*it)->handle(result);
}

void
HmdRequest::Tick(TwsApi::TickerId tid, const DataLib::HmdBar& bar)
{
   TickerStore tickers = Tickers();
   TickerStore::iterator loc = tickers.find(tid);
   if (tickers.end() == loc)
      return;

   HmdRequestPtr& pt = loc->second;
   pt->bars_.push_back(bar);
}

void
HmdRequest::Add(Consumer& consumer)
{
   const HmdRequestKey& key = consumer.key();
   HmdRequestPtr& pt = Keys()[key];
   if (!pt) {
      pt.reset(new HmdRequest(key));
      TwsApi::TickerId id = pt->tid_;
      Tickers()[id] = pt;
   }

   pt->consumers_.insert(&consumer);
}

void
HmdRequest::Remove(Consumer& consumer)
{
   KeyStore& store = Keys();

   const HmdRequestKey& key = consumer.key();
   KeyStore::iterator loc   = store.find(key);
   HmdRequestPtr& pt        = loc->second;

   if (!pt)
      return;

   pt->consumers_.erase(&consumer);

   if (pt->consumers_.empty()) {
      TickerStore& tickers       = Tickers();
      TickerStore::iterator tloc = tickers.find(pt->tid_);
      if (tloc != tickers.end())
         tickers.erase(tloc);

      //TwsSystem::Instance().cancelHistoricalData(*pt);
      store.erase(loc);
   }
}

HmdRequest::HmdRequest(const HmdRequestKey& key)
   : key_(key)
   , tid_(-1)
{
   tid_ = TwsSystem::Instance().requestHistoricalData(*this);
}

const TwsApi::Contract&
HmdRequest::contract() const
{
   return key_.contract();
}



} // end of namespace SystemLib
