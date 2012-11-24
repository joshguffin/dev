#include "string/ansishellcolors.h"

#include <map>
#include <string>
#include <iostream>
#include <sstream>

using std::cout;
using std::endl;

void
replace(std::string& target,
        const std::string& search,
        const std::string& replace)
{
   std::string::size_type next = target.find(search);

   for(; next != std::string::npos; next = target.find(search, next)) {
      target.replace(next, search.length(), replace);
      next += replace.length();
   }
}

typedef std::ostream& (*colorfun)(std::ostream& os);

const colorfun&
color(const std::string& desired)
{
   typedef std::map<std::string, colorfun> Colors;
   static Colors colors;
   if (colors.empty()) {

   colors["red"]     = StringLib::red;
   colors["green"]   = StringLib::green;
   colors["yellow"]  = StringLib::yellow;
   colors["blue"]    = StringLib::blue;
   colors["magenta"] = StringLib::magenta;
   colors["cyan"]    = StringLib::cyan;
   colors["black"]   = StringLib::black;
   colors["white"]   = StringLib::white;
   }

   Colors::const_iterator loc = colors.find(desired);
   if (loc == colors.end()) {
      static const colorfun empty = StringLib::empty;
      return empty;
   }

   return loc->second;
}

int
main(int argc, char** argv)
{
   if (argc < 2) {
      cout << "Usage: " << argv[0] << " <string> [color]" << endl;
      return 1;
   }

   const std::string search = argv[1];
   const std::string desiredColor = argc == 3 ? argv[2] : "green";

   const colorfun& colorval = color(desiredColor);

   std::stringstream replaceStream;
   replaceStream << StringLib::bold << colorval << search << StringLib::resetColor;

   const std::string replacement = replaceStream.str();

   std::string line;
   while (getline(std::cin, line)) {
      replace(line, search, replacement);
      cout << line << endl;
   }

   return 0;
}

