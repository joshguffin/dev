// just compile this and link with -lboost_unit_test_framework
#include <iostream>
#include <sstream>

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>
#include "string/integertostring.h"
#include "include/headermacros.h"

// === SPARSE enums ===========================================================

#define FieldsMacroExample(F) \
   F(EnumVal1, 'a') \
   F(EnumVal2, 'c') \
   F(EnumVal3, 'D') \
   F(EnumVal4, 'G') \
   F(EnumVal5, ' ') \
   F(EnumVal6, 8)
   IMPLEMENT_SPARSE_ENUM_WRAPPER(Test, FieldsMacroExample);
#undef FieldsMacroExample

BOOST_AUTO_TEST_CASE(SparseValuesTest)
{
   BOOST_CHECK(Test::EnumVal1 == 'a');
   BOOST_CHECK(Test::EnumVal2 == 'c');
   BOOST_CHECK(Test::EnumVal3 == 'D');
   BOOST_CHECK(Test::EnumVal4 == 'G');
   BOOST_CHECK(Test::EnumVal5 == ' ');
   BOOST_CHECK(Test::EnumVal6 == 8);
}

#define STRING_TEST(value) Test::ToString(Test::value) == #value
BOOST_AUTO_TEST_CASE(SparseToString)
{
   BOOST_CHECK(STRING_TEST(EnumVal1));
   BOOST_CHECK(STRING_TEST(EnumVal2));
   BOOST_CHECK(STRING_TEST(EnumVal3));
   BOOST_CHECK(STRING_TEST(EnumVal4));
   BOOST_CHECK(STRING_TEST(EnumVal5));
   BOOST_CHECK(STRING_TEST(EnumVal6));
}
#undef STRING_TEST

#define STRING_TEST(value) Test::FromString(#value) == Test::value
BOOST_AUTO_TEST_CASE(SparseFromString)
{
   BOOST_CHECK(STRING_TEST(EnumVal1));
   BOOST_CHECK(STRING_TEST(EnumVal2));
   BOOST_CHECK(STRING_TEST(EnumVal3));
   BOOST_CHECK(STRING_TEST(EnumVal4));
   BOOST_CHECK(STRING_TEST(EnumVal5));
   BOOST_CHECK(STRING_TEST(EnumVal6));
}
#undef STRING_TEST

#define STREAM_TEST(value) { std::stringstream ss; ss << Test::value; BOOST_CHECK(ss.str() == #value); }
BOOST_AUTO_TEST_CASE(SparseStream)
{
   STREAM_TEST(EnumVal1);
   STREAM_TEST(EnumVal2);
   STREAM_TEST(EnumVal3);
   STREAM_TEST(EnumVal4);
   STREAM_TEST(EnumVal5);
   STREAM_TEST(EnumVal6);
}
#undef STREAM_TEST

// === COMPACT enums ===========================================================


#define FieldsMacroExample(F) \
   F(EnumVal1) \
   F(EnumVal2) \
   F(EnumVal3) \
   F(EnumVal4) \
   F(EnumVal5) \
   F(EnumVal6)
   IMPLEMENT_COMPACT_ENUM_WRAPPER(Test2, FieldsMacroExample);
#undef FieldsMacroExample

BOOST_AUTO_TEST_CASE(CompactValuesTest)
{
   BOOST_CHECK(Test2::EnumVal1 == 0);
   BOOST_CHECK(Test2::EnumVal2 == 1);
   BOOST_CHECK(Test2::EnumVal3 == 2);
   BOOST_CHECK(Test2::EnumVal4 == 3);
   BOOST_CHECK(Test2::EnumVal5 == 4);
   BOOST_CHECK(Test2::EnumVal6 == 5);
   BOOST_CHECK(Test2::Unknown  == 6);
}

#define STRING_TEST(value) Test2::ToString(Test2::value) == #value
BOOST_AUTO_TEST_CASE(CompactToString)
{
   BOOST_CHECK(STRING_TEST(EnumVal1));
   BOOST_CHECK(STRING_TEST(EnumVal2));
   BOOST_CHECK(STRING_TEST(EnumVal3));
   BOOST_CHECK(STRING_TEST(EnumVal4));
   BOOST_CHECK(STRING_TEST(EnumVal5));
   BOOST_CHECK(STRING_TEST(EnumVal6));
}
#undef STRING_TEST

#define STRING_TEST(value) Test2::FromString(#value) == Test2::value
BOOST_AUTO_TEST_CASE(CompactFromString)
{
   BOOST_CHECK(STRING_TEST(EnumVal1));
   BOOST_CHECK(STRING_TEST(EnumVal2));
   BOOST_CHECK(STRING_TEST(EnumVal3));
   BOOST_CHECK(STRING_TEST(EnumVal4));
   BOOST_CHECK(STRING_TEST(EnumVal5));
   BOOST_CHECK(STRING_TEST(EnumVal6));
}
#undef STRING_TEST

#define STREAM_TEST(value) { std::stringstream ss; ss << Test2::value; BOOST_CHECK(ss.str() == #value); }
BOOST_AUTO_TEST_CASE(CompactStream)
{
   STREAM_TEST(EnumVal1);
   STREAM_TEST(EnumVal2);
   STREAM_TEST(EnumVal3);
   STREAM_TEST(EnumVal4);
   STREAM_TEST(EnumVal5);
   STREAM_TEST(EnumVal6);
}
#undef STREAM_TEST
