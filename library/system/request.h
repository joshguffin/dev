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

namespace SystemLib {

class Request;
typedef boost::shared_ptr<Request> RequestPtr;

//==============================================================================
// Request declaration
//==============================================================================

class Request
{

public:

   class Consumer;
   class Failure;

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
   static void Tick(TwsApi::TickerId, const Failure&);

   static void    Add(Consumer&);
   static void Remove(Consumer&);

private:

   Request(const RequestKey&);

   void update(TwsApi::TickType, int);
   void update(TwsApi::TickType, double);
   void update(TwsApi::TickType, const std::string&);

   void failure(const std::string&, int);

   template <typename T> void notify(const T&);
   template <typename T> void notify(TwsApi::TickType, T);

private:

   RequestKey key_;
   TwsApi::TickerId tid_;

   DataLib::BidAsk bidask_;
   DataLib::Last   last_;
   DataLib::Mark   mark_;
   DataLib::Open   open_;
   DataLib::Close  close_;
   DataLib::State  state_;
   DataLib::Stats  stats_;

   DataLib::HistoricalStats histStats_;
   DataLib::Fundamentals    fundamentals_;

   typedef std::set<Consumer*> Consumers;
   Consumers consumers_;

private:

   typedef boost::unordered_map<RequestKey       , RequestPtr> KeyStore;
   typedef boost::unordered_map<TwsApi::TickerId , RequestPtr> TickerStore;

   static    KeyStore& Keys();
   static TickerStore& Tickers();
};

//==============================================================================
// Consumer declaration/implementation
//==============================================================================

class Request::Consumer
{
public:

   Consumer(const RequestKey& key) : key_(key) { Request::Add(*this); }
   virtual ~Consumer() { Request::Remove(*this); }

   // implement any to receive data
   virtual void handle(const DataLib::BidAsk&) {}
   virtual void handle(const DataLib::Last&) {}
   virtual void handle(const DataLib::Mark&) {}
   virtual void handle(const DataLib::Open&) {}
   virtual void handle(const DataLib::Close&) {}
   virtual void handle(const DataLib::State&) {}
   virtual void handle(const DataLib::Stats&) {}
   virtual void handle(const DataLib::HistoricalStats&) {}
   virtual void handle(const DataLib::Fundamentals&) {}
   virtual void handle(const Request::Failure&) {}

   IMPLEMENT_ACCESSOR(const RequestKey& , key);

private:
   const RequestKey key_;
};

//==============================================================================
// Failure declaration/implementation
//==============================================================================

class Request::Failure
{

public:

   Failure(const std::string& reason, int code) : reason_(reason), code_(code) {}

   IMPLEMENT_ACCESSOR(const std::string& , reason);
   IMPLEMENT_ACCESSOR(int , code);

private:

   std::string reason_;
   int code_;
};

inline std::ostream&
operator<<(std::ostream& os, const Request::Failure& failure)
{
   return os << failure.code() << ' ' << failure.reason();
}

} // end of namespace SystemLib

#include "system/request.ch"

#endif // system_request_h_INCLUDED
