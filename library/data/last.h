#ifndef data_last_h_INCLUDED
#define data_last_h_INCLUDED

namespace DataLib {

//==============================================================================
// Last declaration
//==============================================================================

class Last
{

public:

   Last();
   Last(double, int, time_t);

   IMPLEMENT_ACCESSORS(double , price);
   IMPLEMENT_ACCESSORS(int    , size);
   IMPLEMENT_ACCESSORS(time_t , time);

   bool valid() const;

private:

   double price_;
   int    size_;
   time_t time_;
};

//==============================================================================
// Last implementation 
//==============================================================================

inline 
Last::Last()
   : price_(-1.0f)
   , size_(-1)
   , time_(-1)
{}

inline 
Last::Last(double price, int size, time_t time)
   : price_(price)
   , size_(size)
   , time_(time)
{}

inline bool
Last::valid() const
{
   return price_ > 0.0f && size_ > -1 && time_ > -1;
}

} // end of namespace DataLib

#endif // data_last_h_INCLUDED
