#ifndef system_fuse_h_INCLUDED
#define system_fuse_h_INCLUDED

#include "system/fusebase.h"

namespace SystemLib {

/*
 * Construct a fuse that fires after a specified interval by calling a member
 * function on a given object.  The member function must have the signature
 *
 * void function();
 *
 * and in particular should not be const.
 *
 * struct Bar { void foo(); };
 * Bar bar;
 * FuseBase* fuse = Fuse::Create(milliseconds(60), bar, &Bar::foo);
 * fuse->activate();
 *
 */

class Fuse
{
public:

   // returns a new'd pointer, which the caller owns
   template <class Target, typename Member>
   static FuseBase* Create(const FuseBase::duration&, Target& object, Member function);

private:
   template <class, typename> class Wrap;
};

//==============================================================================
// Wrapper class to permit the use of the Fuse::Create method
//==============================================================================

template <class Target, typename Member>
class Fuse::Wrap : public FuseBase
{
public:
   Wrap(const boost::posix_time::time_duration&, Target&, Member);
   static void FuseBaseTarget(void*);
   void fire();

private:
   Target* targetObject_;
   Member  targetFunction_;
};

} // end of namespace SystemLib

#include "system/fuse.ch"

#endif // system_fuse_h_INCLUDED
