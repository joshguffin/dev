#include "system/common.h"
#include "generator.h"

#include <vector>
#include <string>

void
parse(std::ifstream& is,
      int& desired,
      std::vector<double>& consts,
      std::vector<double>& vars,
      std::vector<int>& constraints)
{
   char ident;
   std::string line, token;
   while (getline(is, line)) {
      if (line.empty() || line[0] == '#')
         continue;

      std::stringstream ss(line);
      ss >> ident;

      if (ident == 'i') {
         ss >> token;
         consts.push_back(atof(token.c_str()));
         ss >> token;
         vars.push_back(atof(token.c_str()));
      }
      else {
         if (ident == 'd') {
            ss >> token;
            desired = atoi(token.c_str());
         }
         else if (ident == 'c')
            while (ss >> token)
               constraints.push_back(atoi(token.c_str()));
         else {
            cout << "Could not parse line '" << line << "'" << endl;
            abort();
         }
      }
   }

}

int
main(int argc, char** argv) {

   if (argc < 2) {
      cout << "Usage: " << argv[0] << " <file>" << endl;
      return EXIT_FAILURE;
   }

   std::ifstream is(argv[1]);
   if (!is) {
      cout << "Unable to open file at " << argv[1] << endl;
      return EXIT_FAILURE;
   }

   // parse inputs
   int desired;
   std::vector<double> consts;
   std::vector<double> vars;
   std::vector<int> constraints;
   parse(is, desired, consts, vars, constraints);

   Generator generator(consts, vars, constraints);

   // minimize
   generator.minimize(desired);
   generator.describe();

   return 0;
}

