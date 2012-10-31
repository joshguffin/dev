#ifndef timer_h_INCLUDED
#define timer_h_INCLUDED

#include <ctime>



namespace SystemLib {

   const char* SecondPrecisionTime();
   const char* MicrosecondPrecisionTime();
   const char* MillisecondPrecisionTime();
   const char* YYYYMMDD();

} // end of namespace SystemLib


#endif // timer_h_INCLUDED

