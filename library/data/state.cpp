#include "system/common.h"
#include "data/state.h"

namespace DataLib {

State::State()
   : halted_(Halted::Unknown)
   , shortable_(Shortable::Unknown)
{}

// update short sale state
void
State::shortable(double value)
{
   if (value > 2.5)
      // There are at least 1000 shares available for a short sale
      shortable_ = Shortable::Available;
   else if (value > 1.5)
      // This contract will be available for short sale if shares can be located
      shortable_ = Shortable::RequiresLookup;
   else if (value > 0.5)
      // Not available for short sale
      shortable_ = Shortable::Unavailable;
   else if (value > -0.5)
      shortable_ = Shortable::NotTrading;
   else
      shortable_ = Shortable::Unknown;
}

void
State::halted(double value)
{
   if (value > 0.5)
      halted_ = Halted::True;
   else if (value > -0.5)
      halted_ = Halted::False;
   else if (value > -1.5)
      halted_ = Halted::NotTrading;
   else
      halted_ = Halted::Unknown;
}

bool
State::valid() const
{
   return halted_ != Halted::Unknown && shortable_ != Shortable::Unknown;
}

} // end of namespace DataLib


