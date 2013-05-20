#ifndef system_combo_h_INCLUDED
#define system_combo_h_INCLUDED

#include <vector>

namespace SystemLib {

class Combo
{
public:
   class Leg;
   typedef std::vector<Leg> Legs;

public:
   Combo(const Legs&);
   Combo(const std::string& key);

   void addLeg(const Leg&);

   IMPLEMENT_ACCESSOR(const Legs&, legs);
   IMPLEMENT_ACCESSOR(const std::string&, key);

   const std::string& key();

private:
   void buildKey();
   void buildLegs();

private:
   bool keyDirty_;
   std::string key_;
   Legs legs_;
};

class Combo::Leg
{
public:
   Leg(const TwsApi::Contract&, int);

   IMPLEMENT_ACCESSORS(const TwsApi::Contract&, contract);
   IMPLEMENT_ACCESSORS(int, ratio);

private:
   TwsApi::Contract contract_;
   int ratio_;
};

std::ostream& operator<<(std::ostream&, const Combo&);
std::ostream& operator<<(std::ostream&, const Combo::Leg&);

} // end of namespace SystemLib

#endif // system_combo_h_INCLUDED
