#include "system/common.h"
#include "system/unittest.h"
#include "util/persistence.h"

#include <sstream>
#include <cstdio>

BOOST_AUTO_TEST_CASE(integer)
{
   std::string path = "/tmp/persisted.junk";
   ::remove(path.c_str());
   {
      UtilLib::Persistence<int> value(path);

      BOOST_CHECK(value == 0);

      value = 10;
      BOOST_CHECK(value == 10);
   } // allow value to go out of scope, closing the file

   // test persisted value
   UtilLib::Persistence<int> value2(path);
   BOOST_CHECK(value2 == 10);

   value2 = 11;
   BOOST_CHECK(value2 == 11);
}


BOOST_AUTO_TEST_CASE(string)
{
   std::string path = "/tmp/persisted.junk";
   ::remove(path.c_str());
   {
      UtilLib::Persistence<std::string> value(path);

      BOOST_CHECK(value == "");

      value = "foobar";
      BOOST_CHECK(value == "foobar");
   }

   UtilLib::Persistence<std::string> value2(path);
   BOOST_CHECK(value2 == "foobar");

   value2 = "barfoo";
   BOOST_CHECK(value2 == "barfoo");
}
