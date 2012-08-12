#include <iostream>
#include <sstream>

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>
#include "string/integertostring.h"

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
RunStringTest(T val, const std::string& description)
{
   std::string libResult = StringLib::IntegerToString(val);
   std::string stdResult = CreateStdString(val);
   bool equal            = libResult == stdResult;

   if (equal)
      std::cout
         << "[\033[01;32;5;160m" << "OK" << "\033[0m]"
         << " " << description
         << " (" << libResult << " == " << stdResult << ")"
         << std::endl;
   else {
      std::string errString = "[\033[01;38;5;160mERROR\033[0m]";
      std::cout
         << errString
         << ' ' << '(' << description << ')'
         << ' ' << "lib: " << libResult << " " << "len=" << libResult.length() << '\n'
         << std::string(7, ' ')
         << ' ' << "std: " << stdResult << " " << "len=" << stdResult.length() << std::endl;
   }
   BOOST_CHECK(equal);
}

#define CREATE_AUTO_TEST_CASE(T)                         \
   BOOST_AUTO_TEST_CASE(IntegerToString_##T##_Test)      \
   {                                                     \
      RunStringTest(std::numeric_limits<T>::max() , #T); \
      RunStringTest(std::numeric_limits<T>::min() , #T); \
      RunStringTest(static_cast<T>(0)             , #T); \
      RunStringTest(static_cast<T>(1)             , #T); \
      RunStringTest(static_cast<T>(-1)            , #T); \
   }

CREATE_AUTO_TEST_CASE(int8_t  );
CREATE_AUTO_TEST_CASE(int16_t );
CREATE_AUTO_TEST_CASE(int32_t );
CREATE_AUTO_TEST_CASE(int64_t );
CREATE_AUTO_TEST_CASE(uint8_t );
CREATE_AUTO_TEST_CASE(uint16_t);
CREATE_AUTO_TEST_CASE(uint32_t);
CREATE_AUTO_TEST_CASE(uint64_t);

#undef CREATE_AUTO_TEST_CASE

#define RUN_EXPLICIT_TEST(Val) RunStringTest(Val, #Val);

   enum Unnamed    { One, Two };
   enum Characters { charOne = 'a', charTwo = '\0', charThree = ' ' };
   enum PosNeg     { someval=1, otherval=-1 };


BOOST_AUTO_TEST_CASE(IntegerToString_Sample_Values)
{
   RUN_EXPLICIT_TEST(true);
   RUN_EXPLICIT_TEST(false);
   RUN_EXPLICIT_TEST(static_cast<uint16_t>(2355));
   RUN_EXPLICIT_TEST(static_cast<int16_t>(-1295));
   RUN_EXPLICIT_TEST(static_cast<int64_t>(-8372598273598235LL));


   RUN_EXPLICIT_TEST(One);
   RUN_EXPLICIT_TEST(Two);
   RUN_EXPLICIT_TEST(charOne);
   RUN_EXPLICIT_TEST(charTwo);
   RUN_EXPLICIT_TEST(charThree);
   RUN_EXPLICIT_TEST(someval);
   RUN_EXPLICIT_TEST(otherval);

}
