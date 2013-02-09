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
   F(NotAvailable)
   IMPLEMENT_COMPACT_ENUM_WRAPPER_IN_CLASS(Shortable, SHORTABLE)
#undef SHORTABLE

public:

   State();

   IMPLEMENT_ACCESSORS(Shortable::Type, state);
   IMPLEMENT_ACCESSORS(bool, halted);

   bool valid() const;
   void update(double);

private:

   bool halted_;
   Shortable::Type state_;
};

inline std::ostream&
operator<<(std::ostream& os, const State& data)
{
   return os << data.state() << ' ' << data.halted();
}

} // end of namespace DataLib

#endif // data_state_h_INCLUDED
