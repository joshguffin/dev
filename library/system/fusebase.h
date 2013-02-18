#ifndef system_fusebase_h_INCLUDED
#define system_fusebase_h_INCLUDED

#include "system/twssystem.h"

#include <boost/function.hpp>
#include <boost/date_time/posix_time/posix_time_types.hpp>

namespace SystemLib {

class FuseBase
{
   friend class TwsSystem;
public:

   typedef boost::posix_time::time_duration duration;
   typedef boost::posix_time::ptime         time_point;

   IMPLEMENT_ACCESSOR(const time_point&, time);
   void baseFire();

   void activate(const duration&);
   void activate();
   void deactivate();

   ~FuseBase();

   static duration NextFireTime();

protected:

   typedef boost::function<void (void*)> FuseTarget;
   FuseBase(const boost::posix_time::time_duration&, void* object, FuseTarget);

private:

   static time_point Time(const duration&);

   static void Add(FuseBase*);
   static void Remove(FuseBase*);
   static void ProcessQueue();

   struct FuseComp;
   typedef std::set<FuseBase*, FuseComp> Set; // weak pointers
   static Set Queue_;

private:

   const duration delay_;
   time_point time_;
   FuseTarget function_;
   void* object_;

   bool active_;
};


struct FuseBase::FuseComp
{
   bool operator()(const FuseBase* lhs, const FuseBase* rhs) const
   { return lhs->time() < rhs->time(); }
};

} // end of namespace SystemLib

#endif // system_fusebase_h_INCLUDED
