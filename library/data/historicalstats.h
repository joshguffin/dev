#ifndef data_historicalstats_h_INCLUDED
#define data_historicalstats_h_INCLUDED

#include <iostream>

namespace DataLib {

class HistoricalStats
{

public:

   HistoricalStats();

   IMPLEMENT_ACCESSORS(double , hi13wk);
   IMPLEMENT_ACCESSORS(double , hi26wk);
   IMPLEMENT_ACCESSORS(double , hi52wk);
   IMPLEMENT_ACCESSORS(double , lo13wk);
   IMPLEMENT_ACCESSORS(double , lo26wk);
   IMPLEMENT_ACCESSORS(double , lo52wk);

   IMPLEMENT_ACCESSORS(int , averageVolume);

   bool valid() const;

private:

   double hi13wk_;
   double hi26wk_;
   double hi52wk_;
   double lo13wk_;
   double lo26wk_;
   double lo52wk_;

   int averageVolume_;
};

inline std::ostream&
operator<<(std::ostream& os, const HistoricalStats& data)
{
   os << data.lo13wk()
      << ' ' << data.hi13wk()
      << ' ' << data.lo26wk()
      << ' ' << data.hi26wk()
      << ' ' << data.lo52wk()
      << ' ' << data.hi52wk()
      << ' ' << data.averageVolume();
   return os;
}

inline std::istream&
operator>>(std::istream& is, HistoricalStats& data)
{
   double items[6];
   int avgV;

   for (int i = 0; i < 6; ++i)
      is >> items[i];

   is >> avgV;

   data.averageVolume(avgV);
   data.lo13wk(items[0]);
   data.hi13wk(items[1]);
   data.lo26wk(items[2]);
   data.hi26wk(items[3]);
   data.lo52wk(items[4]);
   data.hi52wk(items[5]);
   return is;
}

} // end of namespace DataLib

#endif // data_historicalstats_h_INCLUDED
