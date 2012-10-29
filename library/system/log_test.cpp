// just compile this and link with -lboost_unit_test_framework
#include <iostream>
#include <sstream>

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>
#include "system/log.h"


BOOST_AUTO_TEST_CASE(SparseValuesTest)
{
   LOG << "Stuff" << endm;
   LOG(WARN) << "Stuff" << endm;
   LOG(FATAL) << "outch" << endm;
   BOOST_CHECK(true);
}

