#ifndef data_last_h_INCLUDED
#define data_last_h_INCLUDED

namespace DataLib {

class Last
{

public:

   Last();
   Last(double, int, time_t);

   IMPLEMENT_ACCESSORS(double , price);
   IMPLEMENT_ACCESSORS(int    , size);
   IMPLEMENT_ACCESSORS(time_t , time);

   bool valid() const;
   void setTime(const std::string&);

   static std::string Request() { return ""; }

private:

   double price_;
   int    size_;
   time_t time_;
};

} // end of namespace DataLib

#endif // data_last_h_INCLUDED
