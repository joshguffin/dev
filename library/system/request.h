#ifndef system_request_h_INCLUDED
#define system_request_h_INCLUDED

#include "data/bidask.h"
#include "data/fundamentals.h"
#include "data/historicalstats.h"
#include "data/last.h"
#include "data/singleprice.h"
#include "data/state.h"
#include "data/stats.h"
#include "system/requestkey.h"
#include <boost/unordered_map.hpp>
#include <boost/shared_ptr.hpp>

/**
 * To make a data request, inherit from Request::Consumer and implement any
 * handle method whose data you wish to use.
 */

class Request;
typedef boost::shared_ptr<Request> RequestPtr;

class Request
{

public:

   class Consumer;

#define REQUEST_TYPES(F) \
   F(OptionVolume            , 100) \
   F(OptionOpenInterest      , 101) \
   F(HistoricalVolatility    , 104) \
   F(OptionImpliedVolatility , 106) \
   F(IndexFuturePremium      , 162) \
   F(MiscellaneousStats      , 165) \
   F(MarkPrice               , 221) \
   F(AuctionValues           , 225) \
   F(Shortable               , 236)
   IMPLEMENT_SPARSE_ENUM_WRAPPER_IN_CLASS(Generic, REQUEST_TYPES)
#undef REQUEST_TYPES

public:

   const TwsApi::Contract& contract() const;
   IMPLEMENT_ACCESSOR(TwsApi::TickerId, tid);

   template <typename T>
   static void Tick(TwsApi::TickerId, TwsApi::TickType, const T&);

   static void    Add(Consumer&);
   static void Remove(Consumer&);

private:

   Request(const RequestKey&);

   void update(TwsApi::TickType, int);
   void update(TwsApi::TickType, double);
   void update(TwsApi::TickType, const std::string&);

   template <typename T> void notify(const T&);
   template <typename T> void notify(TwsApi::TickType, T);

private:

   RequestKey key_;
   TwsApi::TickerId tid_;

   typedef std::set<Consumer*> Consumers;

   Consumers consumers_;

   DataLib::BidAsk bidask_;
   DataLib::Last   last_;
   DataLib::Mark   mark_;
   DataLib::Open   open_;
   DataLib::Close  close_;
   DataLib::State  state_;
   DataLib::Stats  stats_;

   DataLib::HistoricalStats histStats_;
   DataLib::Fundamentals    fundamentals_;

private:

   typedef boost::unordered_map<RequestKey       , RequestPtr> KeyStore;
   typedef boost::unordered_map<TwsApi::TickerId , RequestPtr> TickerStore;

   static    KeyStore& Keys();
   static TickerStore& Tickers();
};

class Request::Consumer
{
public:

   Consumer(const RequestKey& key) : key_(key) { Request::Add(*this); }
   virtual ~Consumer() {}

#define DEFINE_HANDLE(Type) virtual void handle(const DataLib::Type&) {}
   DEFINE_HANDLE(BidAsk);
   DEFINE_HANDLE(Last);
   DEFINE_HANDLE(Mark);
   DEFINE_HANDLE(Open);
   DEFINE_HANDLE(Close);
   DEFINE_HANDLE(State);
   DEFINE_HANDLE(Stats);

   DEFINE_HANDLE(HistoricalStats);
   DEFINE_HANDLE(Fundamentals);
#undef DEFINE_HANDLE

   IMPLEMENT_ACCESSOR(const RequestKey& , key);

private:
   const RequestKey key_;
};

#include "system/request.ch"

#endif // system_request_h_INCLUDED
