#ifndef data_state_h_INCLUDED
#define data_state_h_INCLUDED

#include <iostream>

namespace DataLib {

class State
{

public:

#define SHORTABLE(F) \
   F(Available)      \
   F(RequiresLookup) \
   F(Unavailable)    \
   F(NotTrading)
   IMPLEMENT_COMPACT_ENUM_WRAPPER_IN_CLASS(Shortable, SHORTABLE)
#undef SHORTABLE

#define HALTED(F) \
   F(True)        \
   F(False)       \
   F(NotTrading)
   IMPLEMENT_COMPACT_ENUM_WRAPPER_IN_CLASS(Halted, HALTED)
#undef SHORTABLE

public:

   State();

   IMPLEMENT_ACCESSORS(Shortable::Type, shortable);
   IMPLEMENT_ACCESSORS(Halted::Type   , halted);

   void shortable(double);
   void halted(double);

   bool valid() const;

private:

   Halted::Type    halted_;
   Shortable::Type shortable_;
};

inline std::ostream&
operator<<(std::ostream& os, const State& data)
{
   return os << data.shortable() << ' ' << data.halted();
}

} // end of namespace DataLib

#endif // data_state_h_INCLUDED
