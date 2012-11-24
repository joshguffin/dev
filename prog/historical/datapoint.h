#ifndef datapoint_h_INCLUDED
#define datapoint_h_INCLUDED

class DataPoint
{

public:

   DataPoint(time_t date, double open, double high, double low, double close, int volume, int barcount, double WAP, bool hasGaps);

   IMPLEMENT_ACCESSOR(time_t , date);
   IMPLEMENT_ACCESSOR(double , open);
   IMPLEMENT_ACCESSOR(double , high);
   IMPLEMENT_ACCESSOR(double , low);
   IMPLEMENT_ACCESSOR(double , close);
   IMPLEMENT_ACCESSOR(int    , volume);
   IMPLEMENT_ACCESSOR(int    , barcount);
   IMPLEMENT_ACCESSOR(double , WAP);
   IMPLEMENT_ACCESSOR(bool   , hasGaps);

private:

   time_t date_;
   double open_;
   double high_;
   double low_;
   double close_;
   int volume_;
   int barcount_;
   double WAP_;
   bool hasGaps_;
};

std::ostream& operator<<(std::ostream&, const DataPoint&);

#endif // datapoint_h_INCLUDED
