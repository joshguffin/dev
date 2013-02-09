#ifndef data_stats_h_INCLUDED
#define data_stats_h_INCLUDED

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

   static std::string Request() { return ""; }

private:

   double high_;
   double low_;

   double tradeRate_;
   double tradeCount_;

   double volumeRate_;
   double realTimeVolume_;

   int volume_;
};

} // end of namespace DataLib

#endif // data_stats_h_INCLUDED

