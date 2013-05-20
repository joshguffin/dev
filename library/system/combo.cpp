#include "system/common.h"
#include "system/combo.h"

#include <boost/algorithm/string.hpp>

namespace SystemLib {

Combo::Combo(const std::vector<Leg>& legs)
   : keyDirty_(false)
   , legs_(legs)
{
   buildKey();
}

Combo::Combo(const std::string& key)
   : keyDirty_(false)
   , key_(key)
{
   buildLegs();
}

void
Combo::addLeg(const Combo::Leg& leg)
{
   legs_.push_back(leg);
}

std::ostream&
operator<<(std::ostream& os, const Combo& combo)
{
   return os << combo.key();
}

const std::string&
Combo::key()
{
   if (!keyDirty_)
      return key_;

   buildKey();
   return key_;
}

void
Combo::buildKey()
{
   keyDirty_ = false;

   if (legs_.empty()) {
      key_ = "";
      return;
   }

   Combo::Legs::const_iterator it  = legs_.begin();
   Combo::Legs::const_iterator end = legs_.end();

   std::stringstream ss;
   while (true) {
      ss << *it++;
      if (it == end)
         break;
      ss << ',';
   }

   key_ = ss.str();
}

void
Combo::buildLegs()
{
   if (key_.empty())
      return;

   typedef std::vector<std::string> Components;
   Components components;
   boost::split(components, key_, boost::is_any_of(","));
   if (components.empty())
      return;

   Components::const_iterator it  = components.begin();
   Components::const_iterator end = components.end();

   Components leg;
   while (it != end) {
      const std::string& component = *it++;
      leg.clear();
      boost::split(leg, component, boost::is_any_of(":"));
      if (leg.size() != 2)
         continue;

      const std::string& conid = leg[0];
      const std::string& ratio = leg[1];

      TwsApi::Contract contract;
      contract.conId = atol(conid.c_str());
      int intRatio   = atoi(ratio.c_str());

      legs_.push_back(Leg(contract, intRatio));
   }
}

std::ostream&
operator<<(std::ostream& os, const Combo::Leg& leg)
{
   return os << leg.contract().conId << ':' << leg.ratio();
}

} // end of namespace SystemLib

