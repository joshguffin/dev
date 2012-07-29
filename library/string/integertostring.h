#ifndef string_integertostring_h_INCLUDED
#define string_integertostring_h_INCLUDED

#include <stdint.h>
#include <assert.h>
#include <string>
#include <limits>

#include <boost/static_assert.hpp>
#include <boost/type_traits/make_unsigned.hpp>
#include <boost/type_traits/is_signed.hpp>
#include <boost/utility/enable_if.hpp>

namespace StringLib {

namespace IntegerToStringImpl {

// instantiated if the type is unsigned
template <typename UnsignedType>
typename boost::disable_if<boost::is_signed<UnsignedType>, char*>::type
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
typename boost::enable_if<boost::is_signed<SignedType>, char*>::type
FillBuffer(char* pt, SignedType input, char*buf)
{
   BOOST_STATIC_ASSERT(std::numeric_limits<SignedType>::is_integer);
   BOOST_STATIC_ASSERT(boost::is_signed<SignedType>::value);
   typedef typename boost::make_unsigned<SignedType>::type UnsignedType;

   bool negative = input < 0;

   UnsignedType uinput = negative ? -input : input;

   pt = FillBuffer(pt, uinput, buf);

   if (negative)
       *--pt = '-';

   return pt;
}

} // end of namespace IntegerToStringImpl

template <typename IntegralType>
typename boost::disable_if<boost::is_enum<IntegralType>, std::string>::type
IntegerToString(IntegralType input)
{
   if (input == 0)
      return "0";

   BOOST_STATIC_ASSERT(std::numeric_limits<IntegralType>::is_integer);

   const size_t bufferSize = (std::numeric_limits<IntegralType>::digits
                              + static_cast<size_t>(boost::is_signed<IntegralType>::value));

   BOOST_STATIC_ASSERT(bufferSize);

   char buffer[bufferSize];
   char* end = buffer + bufferSize -1;
   char* pt  = IntegerToStringImpl::FillBuffer(end, input, buffer);

   assert(pt >= buffer);
   assert(pt <= end);
   return std::string(pt, end - pt + 1);
}

template <typename EnumType>
typename boost::enable_if<boost::is_enum<EnumType>, std::string>::type
IntegerToString(EnumType input)
{
   return IntegerToString(static_cast<int>(input));
}

} // end of namespace StringLib

#endif // string_integertostring_h_INCLUDED
