#include "system/duration.h"

void
Duration::fixup() {
   if (usec_ < 0L) {
      usec_ += 1000000L;
      --sec_;
   }
}

Duration::Duration(long sec, long usec)
   : sec_(sec)
   , usec_(usec)
{
   if (usec_ < 0L || usec_ >= 1000000L) {
      sec_ += usec_ / 1000000L;
      usec_ %= 1000000L;
      fixup();
   }
}

Duration::Duration()
   : sec_(0L)
   , usec_(0L)
{
   fixup();
}

Duration::Duration(long long usec)
   : sec_ (static_cast<long>(usec / 1000000L))
   , usec_(static_cast<long>(usec % 1000000L))
{
   fixup();
}

Duration&
Duration::operator+=(const Duration& rhs)
{
   sec_  += rhs.sec_;
   usec_ += rhs.usec_;

   if (usec_ >= 1000000L) {
      usec_ -= 1000000L;
      ++sec_;
   }

   return *this;
}

Duration&
Duration::operator-=(const Duration& rhs)
{
   sec_  -= rhs.sec_;
   usec_ -= rhs.usec_;
   fixup();
   return *this;
}

Duration&
Duration::operator%=(const Duration& rhs)
{
   long long t = sec_ * 1000000L + usec_;
   long long r = rhs.sec_ * 1000000L + rhs.usec_;
   t %= r;

   sec_  = static_cast<long>(t / 1000000L);
   usec_ = static_cast<long>(t % 1000000L);
   fixup();
   return *this;
}

long long
Duration::microseconds() const
{
   return static_cast<long long>(sec_) * 1000000LL + usec_;
}

Duration::operator long long() const
{
   return microseconds();
}

time_t
Duration::seconds() const
{
   return static_cast<time_t>(sec_);
}

