#ifndef integertostring_h_INCLUDED
#define integertostring_h_INCLUDED

#include <stdint.h>
#include <assert.h>
#include <string>
#include <limits>

#include <boost/static_assert.hpp>
#include <boost/type_traits/make_unsigned.hpp>
#include <boost/type_traits/is_signed.hpp>
#include <boost/utility/enable_if.hpp>

#include <boost/test/unit_test.hpp>

namespace StringLib {

// instantiated if the type is unsigned
template <typename UnsignedType>
typename boost::disable_if<typename boost::is_signed<UnsignedType>::type, char*>::type
FillBuffer(char* pt, UnsignedType input, char*buf)
{
   BOOST_STATIC_ASSERT(std::numeric_limits<UnsignedType>::is_integer);
   BOOST_STATIC_ASSERT(!boost::is_signed<UnsignedType>::value);

   do {
      assert(pt >= buf);
      *pt-- = input % 10 + '0';
      input /= 10;
   } while (input);

   pt++;
   return pt;
}

// instantiated if the type is signed
template <typename SignedType>
typename boost::enable_if<typename boost::is_signed<SignedType>::type, char*>::type
FillBuffer(char* pt, SignedType input, char*buf)
{
   BOOST_STATIC_ASSERT(std::numeric_limits<SignedType>::is_integer);
   BOOST_STATIC_ASSERT(boost::is_signed<SignedType>::value);
   typedef typename boost::make_unsigned<SignedType>::type UnsignedType;

   bool negative = input < 0;

   // handle input = MIN_INT
   if (negative)
   {
      // sign of modulus of negative number is implementation-defined
      *pt-- = std::abs(input % -10) + '0';
      input /= -10;
   }

   while (input) {
      assert(pt >= buf);
      *pt-- = input % 10 + '0';
      input /= 10;
   }

   if (negative)
       *pt-- = '-';

   return ++pt;
}

template <typename IntegralType>
std::string
IntegerToString(IntegralType input)
{
   if (input == 0)
      return "0";

   BOOST_STATIC_ASSERT(std::numeric_limits<IntegralType>::is_integer);

   const size_t bufferSize = (std::numeric_limits<IntegralType>::digits
                              + static_cast<int>(boost::is_signed<IntegralType>::value));

   BOOST_STATIC_ASSERT(bufferSize);

   char buffer[bufferSize];
   char* end = buffer + bufferSize -1;
   char* pt  = FillBuffer(end, input, buffer);

   assert(pt >= buffer);
   assert(pt <=  end);
   return std::string(pt, end - pt + 1);
}

// To run the unit tests, the following order of #includes is important.
//
// #include <iostream>
// #include <sstream>
//
// #define BOOST_TEST_MAIN
//
// #include <boost/test/unit_test.hpp>
// #include "string/integertostring.h"

#ifdef BOOST_TEST_MAIN

namespace IntegerToStringTest {

template <typename T>
std::string
CreateStdString(T t)
{
   std::stringstream ss;
   ss << t;
   return ss.str();
}

// stringstream needs to treat chars specially
template <> std::string CreateStdString<signed char>(signed char t)
{
   std::stringstream ss;
   ss << static_cast<int>(t);
   return ss.str();
}

template <> std::string CreateStdString<unsigned char>(unsigned char t)
{
   std::stringstream ss;
   ss << static_cast<uint>(t);
   return ss.str();
}

template <typename T>
void
RunStringTest(T val)
{
   std::string libResult = StringLib::IntegerToString(val);
   std::string stdResult = CreateStdString(val);
   bool equal            = libResult == stdResult;

   if (equal)
      std::cout
         << "\033[01;38;5;160m" << "OK" << "\033[39m" << " "
         << libResult << "==" << stdResult << std::endl;
   else
      std::cout
         << "lib: " << libResult << " " << "len=" << libResult.length() << '\n'
         << "std: " << stdResult << " " << "len=" << stdResult.length() << std::endl;
   BOOST_CHECK(equal);
}

#define CREATE_AUTO_TEST_CASE(T)                                                    \
   BOOST_AUTO_TEST_CASE(IntegerToString_##T##_Test)                                 \
   {                                                                                \
      StringLib::IntegerToStringTest::RunStringTest(std::numeric_limits<T>::max()); \
      StringLib::IntegerToStringTest::RunStringTest(std::numeric_limits<T>::min()); \
      StringLib::IntegerToStringTest::RunStringTest(static_cast<T>(0));             \
      StringLib::IntegerToStringTest::RunStringTest(static_cast<T>(1));             \
      StringLib::IntegerToStringTest::RunStringTest(static_cast<T>(-1));            \
   }

CREATE_AUTO_TEST_CASE(int8_t   );
CREATE_AUTO_TEST_CASE(int16_t  );
CREATE_AUTO_TEST_CASE(int32_t  );
CREATE_AUTO_TEST_CASE(int64_t  );
CREATE_AUTO_TEST_CASE(u_int8_t );
CREATE_AUTO_TEST_CASE(u_int16_t);
CREATE_AUTO_TEST_CASE(u_int32_t);
CREATE_AUTO_TEST_CASE(u_int64_t);

#undef CREATE_AUTO_TEST_CASE

BOOST_AUTO_TEST_CASE(IntegerToString_Sample_Values)
{
   StringLib::IntegerToStringTest::RunStringTest(true);
   StringLib::IntegerToStringTest::RunStringTest(false);

   StringLib::IntegerToStringTest::RunStringTest(static_cast<u_int16_t>(2355));
   StringLib::IntegerToStringTest::RunStringTest(static_cast<int16_t>(-1295));

   StringLib::IntegerToStringTest::RunStringTest(static_cast<int64_t>(-8372598273598235LL));


}

} // end of namespace IntegerToStringTest

#endif // BOOST_TEST_MAIN

} // end of namespace StringLib

#endif // integertostring_h_INCLUDED
