#ifndef string_csv_h_INCLUDED
#define string_csv_h_INCLUDED

#include <sstream>
#include <string>
#include <iostream>

namespace StringLib {

//==============================================================================
// Declaration
//==============================================================================

class CSV
{

public:

   template <typename T>
   friend CSV&          operator<<(CSV&, const T&);
   friend std::ostream& operator<<(std::ostream&, const CSV&);

   CSV() : separator_(",") {}
   CSV(const std::string& separator) : separator_(separator) {}

   IMPLEMENT_ACCESSORS(const std::string&, separator);

   void reset();

private:

   std::string separator_;
   std::stringstream values_;
};

//==============================================================================
// Implementation
//==============================================================================

inline void
CSV::reset()
{
   values_.str("");
}

inline std::ostream&
operator<<(std::ostream& os, const CSV& csv)
{
   return os << csv.values_.str();
}

template <typename T>
inline CSV&
operator<<(CSV& csv, const T& item)
{
   if (!csv.values_.str().empty())
      csv.values_ << csv.separator_;

   csv.values_ << item;
   return csv;
}

} // end of namespace StringLib

#endif // string_csv_h_INCLUDED

