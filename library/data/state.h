#ifndef data_state_h_INCLUDED
#define data_state_h_INCLUDED

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

   static std::string Request() { return "236"; }

private:

   bool halted_;
   Shortable::Type state_;
};

} // end of namespace DataLib

#endif // data_state_h_INCLUDED
