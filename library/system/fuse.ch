#ifndef system_fuse_ch_INCLUDED
#define system_fuse_ch_INCLUDED

namespace SystemLib {

template <class Target, typename Member>
inline FuseBase*
Fuse::Create(const FuseBase::duration& duration, Target& object, Member function)
{
   FuseBase* tfuse(new Wrap<Target, Member>(duration, object, function));
   return tfuse;
}

template <class Target, typename Member>
inline void
Fuse::Wrap<Target, Member>::FuseBaseTarget(void* obj)
{
   typedef Fuse::Wrap<Target, Member>* WrapPt;
   WrapPt  wrap   = reinterpret_cast<WrapPt>(obj);
   Target* target = wrap->targetObject_;
   Member& member = wrap->targetFunction_;
   (target->*member)();
}

template <class Target, typename Member>
inline
Fuse::Wrap<Target, Member>::Wrap(const FuseBase::duration& duration,
                                 Target& target,
                                 Member function)
   : FuseBase(duration, this, &Fuse::Wrap<Target, Member>::FuseBaseTarget)
   , targetObject_(&target)
   , targetFunction_(function)
{
}

template <class Target, typename Member>
inline void
Fuse::Wrap<Target, Member>::fire()
{
   (targetObject_->*targetFunction_)();
}

} // end of namespace SystemLib

#endif // system_fuse_ch_INCLUDED
