#include "system/common.h"
#include "data/singleprice.h"

namespace DataLib {

SinglePrice::SinglePrice()
   : price_(-1.0)
{}

SinglePrice::SinglePrice(double price)
   : price_(price)
{}

bool
SinglePrice::valid() const
{
   return price_ > 0.0;
}

} // end of namespace DataLib
