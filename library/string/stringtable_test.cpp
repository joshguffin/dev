#include "system/common.h"
#include "system/unittest.h"
#include "string/stringtable.h"

#include <sstream>
#include <ctype.h>

using namespace std;
using namespace StringLib;

void
addChar(StringTable& output, char out)
{
   if (isgraph(out))
      output << out;
   else {
      std::stringstream ss;
      ss << "\\" << static_cast<int>(out);
      output << ss.str();
   }
}

bool
compareExplicitly(const std::string& tableString,
                  const std::string& expected)
{
   size_t tablelen  = tableString.length();
   size_t stringlen = expected.length();
   size_t len = std::max(tableString.length(), expected.length());

   // hilarious
   StringTable output;

   if (stringlen != tablelen)
      cout
         << "Lengths differ: table is " << tablelen
         << ", string is " << stringlen
         << endl;

   for (size_t i = 0; i < len; i++) {

      if (i >= tableString.length()) {
         output << "Extra char in string";
         addChar(output, expected[i]);
         output << StringTable::endr;
         continue;
      }

      if (i >= expected.length()) {
         output << "Extra char in table";
         addChar(output, tableString[i]);
         output << StringTable::endr;
         continue;
      }


      if (tableString[i] == expected[i])
         continue;

      std::stringstream ss;
      ss << "Position " << i << ":";
      output << ss.str();

      addChar(output, tableString[i]);
      output << "!=";
      addChar(output, expected[i]);

      output << StringTable::endr;
   }

   if (!output.empty())
      cout << output << endl;

   return tableString == expected;
}


BOOST_AUTO_TEST_CASE(Default_alignment)
{
   StringTable table;

   table << 1   << 10 << 100 << StringTable::endr;
   table << 100 << 10 <<   1 << StringTable::endr;

   std::string tableString(table.str());
   std::string validation("1   10 100\n100 10 1");

   BOOST_CHECK(compareExplicitly(tableString, validation));
}



BOOST_AUTO_TEST_CASE(Specified_Alignment)
{
   StringTable table;

   table << 1   << 10 << 100 << StringTable::endr;
   table << 100 << 10 <<   1 << StringTable::endr;

   table.setAlignment(2, StringTable::Right);

   std::string tableString(table.str());
   std::string validation("1   10 100\n100 10   1");

   BOOST_CHECK(compareExplicitly(tableString, validation));
}

BOOST_AUTO_TEST_CASE(Empty_table)
{
   StringTable table;
   std::string tableString(table.str());
   std::string validation;
   BOOST_CHECK(compareExplicitly(tableString, validation));
}

BOOST_AUTO_TEST_CASE(Mixed_args)
{
   StringTable table;
   BOOST_CHECK(table.empty());

   table << "awef" << 10L                             << 100ULL << StringTable::endr;
   table << 100.00 << static_cast<unsigned short>(10) << 1.04f  << StringTable::endr;

   BOOST_CHECK(!table.empty());

   table.setAlignment(2, StringTable::Right);

   std::string tableString(table.str());
   std::string validation("awef 10  100\n100  10 1.04");

   /*
   cout << table << endl;
   cout << validation << endl;
   */

   BOOST_CHECK(compareExplicitly(tableString, validation));
}


class TestCase
{
};

std::ostream&
operator<<(std::ostream& os, const TestCase&)
{
   return os << "tc";
}

BOOST_AUTO_TEST_CASE(Custom_object)
{
   StringTable table;
}


