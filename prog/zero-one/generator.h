#ifndef generator_h_INCLUDED
#define generator_h_INCLUDED

#include <vector>

class Generator {

public:
   Generator(const std::vector<double>& constants,
             const std::vector<double>& variables,
             const std::vector<int>& constraints);

   void describe() const;
   void minimize(int desiredSize);

private:
   double computeCost(const std::vector<int>& constituents) const;
   void minimize(std::vector<int>& constituents,
                 const int desiredSize,
                 const int remainingSize,
                 const size_t index);

private:
   const std::vector<double> constants_;
   const std::vector<double> variables_;
   const std::vector<int> constraints_;

   size_t components_;
   double min_;
   std::vector<int> minDistribution_;
};

#endif // generator_h_INCLUDED
