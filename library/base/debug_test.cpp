#include "system/common.h"
#include "system/unittest.h"
#include "base/debug.h"

#include <sstream>

#define CHECK_NAME(Name, option) { DebugWrap::Scope::Static a(Name); BOOST_CHECK(option a.enabled()); }
#define CHECK_TRUE(Name)  CHECK_NAME(Name, )
#define CHECK_FALSE(Name) CHECK_NAME(Name, !)

BOOST_AUTO_TEST_CASE(WildcardMatch)
{
   DebugWrap::Scope::ClearExpressions();
   DebugWrap::Scope::Add(".*");

   CHECK_TRUE("a=efa");
   CHECK_TRUE("$291A");
   CHECK_TRUE("a+9Oie");
   CHECK_TRUE("b-f");
}

BOOST_AUTO_TEST_CASE(BeginsWithAorB)
{
   DebugWrap::Scope::ClearExpressions();
   DebugWrap::Scope::Add("^a.*");
   DebugWrap::Scope::Add("^b.*");

   CHECK_TRUE("a=efa");
   CHECK_TRUE("a+9Oie");
   CHECK_FALSE("$291A");
   CHECK_FALSE("");
   CHECK_TRUE("b-f");
}

BOOST_AUTO_TEST_CASE(AddAndErase)
{
   DebugWrap::Scope::ClearExpressions();
   DebugWrap::Scope::Add("^a.*");

   CHECK_TRUE("a=efa");
   CHECK_TRUE("a+9Oie");

   DebugWrap::Scope::Erase("^a.*");

   CHECK_FALSE("a=efa");
   CHECK_FALSE("a+9Oie");
}

void foo(int level)
{
   Dscope("foo");
   Dout(level)

   if (level <= 0)
      return;

   foo(--level);
}

BOOST_AUTO_TEST_CASE(Printing)
{
   DebugWrap::Scope::ClearExpressions();
   DebugWrap::Scope::Add("foo");

   foo(5);

}
