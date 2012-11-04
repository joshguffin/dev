#ifndef system_unittest_h_INCLUDED
#define system_unittest_h_INCLUDED

// don't screw up boost macro with the system/log macro
#undef WARN

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>

#endif // system_unittest_h_INCLUDED
