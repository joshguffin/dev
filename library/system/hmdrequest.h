#ifndef system_hmdrequest_h_INCLUDED
#define system_hmdrequest_h_INCLUDED

#include "data/hmdbar.h"
#include "system/hmdrequestkey.h"
#include <boost/unordered_map.hpp>
#include <boost/shared_ptr.hpp>

/**
 * To make a data request, inherit from Request::Consumer and implement any
 * handle method whose data you wish to use.
 */
namespace SystemLib {

class HmdRequest;
typedef boost::shared_ptr<HmdRequest> HmdRequestPtr;

//==============================================================================
// Request declaration
//==============================================================================

class HmdRequest
{

public:

   class Consumer;
   class Failure;

public:

   const TwsApi::Contract& contract() const;
   IMPLEMENT_ACCESSOR(TwsApi::TickerId, tid);

   static void Tick(TwsApi::TickerId, const DataLib::HmdBar&);
   static void Done(TwsApi::TickerId);

   static void    Add(Consumer&);
   static void Remove(Consumer&);

private:

   HmdRequest(const SystemLib::HmdRequestKey&);

private:
   HmdRequestKey key_;
   TwsApi::TickerId tid_;

   typedef std::set<Consumer*> Consumers;
   Consumers consumers_;

   typedef std::vector<DataLib::HmdBar> HmdResult;
   HmdResult bars_;

private:
   typedef boost::unordered_map<HmdRequestKey    , HmdRequestPtr> KeyStore;
   typedef boost::unordered_map<TwsApi::TickerId , HmdRequestPtr> TickerStore;

   static    KeyStore& Keys();
   static TickerStore& Tickers();
};

//==============================================================================
// Consumer declaration
//==============================================================================

class HmdRequest::Consumer
{
public:
   Consumer(const HmdRequestKey& key) : key_(key) { HmdRequest::Add(*this); }
   virtual ~Consumer() { HmdRequest::Remove(*this); }

   // implement any to receive data
   virtual void handle(const HmdResult&)=0;

   IMPLEMENT_ACCESSOR(const HmdRequestKey& , key);

private:
   const HmdRequestKey key_;
};

} // end of namespace SystemLib

#endif // system_hmdrequest_h_INCLUDED
