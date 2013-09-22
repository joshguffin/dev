#include "system/common.h"

#include "generator.h"
#include <numeric>
#include <iterator>
#include <algorithm>

namespace {
template <typename T>
std::ostream&
operator<<(std::ostream& os, const std::vector<T>& items) {
   std::copy(items.begin(), items.end(), std::ostream_iterator<T>(os, " "));
   return os;
}
}

Generator::Generator(const std::vector<double>& constants,
                     const std::vector<double>& variables,
                     const std::vector<int>& constraints)
   : constants_(constants)
   , variables_(variables)
   , constraints_(constraints)
   , components_(constraints_.size())
   , min_(std::numeric_limits<double>::max())
{
   /*
   cout
      << "constants:   " << constants << '\n'
      << "variables:   " << variables << '\n'
      << "constraints: " << constraints << endl;
*/
   assert(components_ == variables_.size());
   assert(components_ == constants_.size());
}

void
Generator::minimize(int desiredSize)
{
   std::vector<int> constituents(components_);
   minimize(constituents, desiredSize, desiredSize, 0);
}

double
Generator::computeCost(const std::vector<int>& constituents) const
{
   double total = 0.0;
   for (size_t ii = 0; ii < components_; ++ii) {
      if (constituents[ii] == 0)
         continue;

      total += constants_[ii] + constituents[ii] * variables_[ii];
   }

   return total;
}

void
Generator::describe() const
{
   cout
      << "Minimum:    " << min_ << "\n"
      << "Components: " << minDistribution_ << endl;
}

void
Generator::minimize(std::vector<int>& constituents,
                    const int desiredSize,
                    const int remainingSize,
                    const size_t index)
{
   // size has been fully distributed to constituents
   if (remainingSize == 0) {
      double thisCost = computeCost(constituents);

      //cout << constituents << " cost=" << thisCost << endl;
      if (thisCost > min_)
         return;

      min_ = thisCost;
      minDistribution_ = constituents;
      return;
   }

   // cannot fulfill the desired size with the current constituents
   const int available = constraints_[index];
   if (index == components_ && available < desiredSize)
      return;

   // distribute remaining size amongst this and larger indices
   int start = std::min(available, desiredSize);

   do {
      constituents[index] = start;
      int remaining = remainingSize - start;

      minimize(constituents, desiredSize, remaining, index + 1);
   } while (--start > 0);
}
