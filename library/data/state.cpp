#include "system/common.h"
#include "data/state.h"

namespace DataLib {

State::State()
   : halted_(false)
   , state_(Shortable::Unknown)
{}

// update short sale state
void
State::update(double value)
{
   if (value > 2.5)
      // There are at least 1000 shares available for a short sale
      state_ = Shortable::Available;
   else if (value > 1.5)
      // This contract will be available for short sale if shares can be located
      state_ = Shortable::RequiresLookup;
   else if (value > 0.5)
      // Not available for short sale
      state_ = Shortable::NotAvailable;
   else
      state_ = Shortable::Unknown;
}

bool
State::valid() const
{
   return state_ != Shortable::Unknown;
}

} // end of namespace DataLib


