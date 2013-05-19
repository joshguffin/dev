#include "string/ansishellcolors.h"

#include <map>
#include <string>
#include <iostream>
#include <sstream>

using std::cout;
using std::endl;

using namespace StringLib;

int
main(int argc, char** argv)
{
   if (argc < 2) {
      cout << "Usage: " << argv[0] << " <string> [color]" << endl;
      return 1;
   }

   std::string value(argv[1]);
   const char* defaultColor = "Green";
   std::string desiredColor(argc > 2 ? argv[2] : defaultColor);
   Color::Value color = Color::FromString(desiredColor);

   cout << Color(value, color) << endl;


   return 0;
}

