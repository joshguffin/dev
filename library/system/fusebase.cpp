#include "system/common.h"
#include "system/fusebase.h"

namespace SystemLib {

FuseBase::time_point
FuseBase::Time(const duration& delay)
{
   return SystemLib::TwsSystem::Instance().updateNow() + delay;
}

FuseBase::FuseBase(const boost::posix_time::time_duration& delay,
                   void* object,
                   FuseTarget function)
   : delay_(delay)
   , time_(Time(delay))
   , function_(function)
   , object_(object)
{
   assert(function);
   assert(object);
}

FuseBase::~FuseBase()
{
   Remove(this);
}

void
FuseBase::baseFire()
{
   function_(object_);
}

FuseBase::duration
FuseBase::NextFireTime()
{
   static FuseBase::duration empty;
   if (Queue_.empty())
      return empty;

   FuseBase& next = **Queue_.begin();
   const time_point& now  = TwsSystem::Now();
   const time_point& soon = next.time();
   if (soon < now)
      return empty;

   return soon - now;
}

void
FuseBase::activate()
{
   if (active_)
      return;

   time_ = Time(delay_);
   Add(this);
}

void
FuseBase::activate(const duration& delay)
{
   if (!active_) {
      activate();
      return;
   }

   time_point time = Time(delay);
   if (time <= time_)
      return;
  
   time_ = time;
   Remove(this);
   Add(this);
}

//==============================================================================
// Queue methods
//==============================================================================

FuseBase::Set FuseBase::Queue_;

void
FuseBase::ProcessQueue()
{
   if (Queue_.empty())
      return;
    const boost::posix_time::ptime& now = TwsSystem::Instance().updateNow();

   Set::iterator it  = Queue_.begin();
   Set::iterator end = Queue_.end();
   while (it != end) {
      FuseBase* fuse = *it;
      if (fuse->time() > now)
         break;

      fuse->active_ = false;
      Queue_.erase(it++);
      fuse->baseFire();
   }
}

void
FuseBase::Add(FuseBase* fuse)
{
   if (fuse->active_)
      return;

   Queue_.insert(fuse);
   fuse->active_ = true;
}

void
FuseBase::Remove(FuseBase* fuse)
{
   if (!fuse->active_)
      return;

   Set::iterator it  = Queue_.begin();
   Set::iterator end = Queue_.end();
   for (; it != end; ++it) {
      FuseBase* queuedFuse = *it;

      if (fuse != queuedFuse)
         continue;

      fuse->active_ = false;
      Queue_.erase(it);
      return;
   }
}

} // end of namespace SystemLib
