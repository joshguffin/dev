#ifndef system_request_h_INCLUDED
#define system_request_h_INCLUDED

#include "data/bidask.h"
#include "data/last.h"
#include "system/requestkey.h"
#include <boost/unordered_map.hpp>
#include <boost/shared_ptr.hpp>

class Request;
typedef boost::shared_ptr<Request> RequestPtr;

class Request
{

public:

   Request(const RequestKey&);

   template <typename T>
   static void Tick(TickerId, TickType, const T&);

public:

   class Consumer;

private:

   void update(TickType, int);
   void update(TickType, double);
   void update(TickType, const std::string&);

   template <typename T> void notify(const T&);

private:

   RequestKey key_;
   TickerId   tid_;

   typedef std::set<Consumer*> Consumers;

   Consumers consumers_;

   DataLib::BidAsk bidask_;
   DataLib::Last   last_;

private:

   typedef boost::unordered_map<RequestKey, RequestPtr> KeyStore;
   typedef boost::unordered_map<TickerId,   RequestPtr> TickerStore;

   static    KeyStore& Keys();
   static TickerStore& Tickers();
};

class Request::Consumer
{
public:
   virtual void handle(const DataLib::BidAsk&);
   virtual void handle(const DataLib::Last&);
};

template <typename T>
inline void
Request::notify(const T& item)
{
   Consumers::iterator it  = consumers_.begin();
   Consumers::iterator end = consumers_.end();
   for (; it != end; ++it)
      (*it)->handle(item);
}

template <typename T>
inline void
Request::Tick(TickerId tid, TickType type, const T& value)
{
   TickerStore& tickers = Tickers();

   TickerStore::iterator loc = tickers.find(tid);
   if (loc == tickers.end()) {
      LOG
         << "Request::Tick: ticker " << tid << " not found ("
         << type << '=' << value << ')'
         << endm;
      return;
   }

   RequestPtr& request = loc->second;
   request->update(type, value);
}

#endif // system_request_h_INCLUDED
