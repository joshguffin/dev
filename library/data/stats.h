#ifndef data_stats_h_INCLUDED
#define data_stats_h_INCLUDED

#include <iostream>

namespace DataLib {

class Stats
{

public:

   Stats();

   IMPLEMENT_ACCESSORS(double , high);
   IMPLEMENT_ACCESSORS(double , low);

   IMPLEMENT_ACCESSORS(double , tradeRate);
   IMPLEMENT_ACCESSORS(double , tradeCount);

   IMPLEMENT_ACCESSORS(double , realTimeVolume);
   IMPLEMENT_ACCESSORS(double , volumeRate);

   IMPLEMENT_ACCESSORS(int , volume);

   bool valid() const;

private:

   double high_;
   double low_;

   double tradeRate_;
   double tradeCount_;

   double volumeRate_;
   double realTimeVolume_;

   int volume_;
};

inline std::ostream&
operator<<(std::ostream& os, const Stats& data)
{
   os << data.high()
      << ' ' << data.low()
      << ' ' << data.tradeRate()
      << ' ' << data.tradeCount()
      << ' ' << data.realTimeVolume()
      << ' ' << data.volumeRate()
      << ' ' << data.volume();
   return os;
}

inline std::istream&
operator>>(std::istream& is, Stats& data)
{
   double items[6];
   int vol;

   for (int i = 0; i < 6; ++i)
      is >> items[i];

   is >> vol;

   data.high(items[0]);
   data.low(items[1]);
   data.tradeRate(items[2]);
   data.tradeCount(items[3]);
   data.realTimeVolume(items[4]);
   data.volumeRate(items[5]);
   data.volume(vol);
   return is;
}

} // end of namespace DataLib

#endif // data_stats_h_INCLUDED

