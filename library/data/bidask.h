#ifndef data_bidask_h_INCLUDED
#define data_bidask_h_INCLUDED

namespace DataLib {

class BidAsk
{

public:

   BidAsk();
   BidAsk(double, double, int, int);

   IMPLEMENT_ACCESSORS(double , bid);
   IMPLEMENT_ACCESSORS(double , ask);
   IMPLEMENT_ACCESSORS(int   , bidSize);
   IMPLEMENT_ACCESSORS(int   , askSize);

   bool valid() const;

private:

   double bid_;
   double ask_;
   int    bidSize_;
   int    askSize_;
};

inline BidAsk::BidAsk()
   : bid_(-1.0f)
   , ask_(-1.0f)
   , bidSize_(-1)
   , askSize_(-1)
{}

inline BidAsk::BidAsk(double bid, double ask, int bidSize, int askSize)
   : bid_(bid)
   , ask_(ask)
   , bidSize_(bidSize)
   , askSize_(askSize)
{}

inline bool
BidAsk::valid() const
{
   return bid_ > 0.0f && ask_ > 0.0f && bidSize_ > 0 && askSize_ > 0;
}

} // end of namespace DataLib

#endif // data_bidask_h_INCLUDED
