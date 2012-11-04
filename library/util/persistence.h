#ifndef util_persistence_h_INCLUDED
#define util_persistence_h_INCLUDED

#include "include/headermacros.h"
#include <fstream>
#include <string>

namespace UtilLib {

template <typename T>
class Persistence
{

public:

   typedef T value_type;

public:

   Persistence(const std::string& path);

   IMPLEMENT_ACCESSOR(const T&, value)
   IMPLEMENT_ACCESSOR(const std::string&, path)

   bool is_open() const;

public:

   bool operator==(const T&) const;
   Persistence<T>& operator=(const T&);

private:

   void write();

private:

   T value_;
   std::string path_;
   std::ofstream stream_;
};

#include "util/persistence.ch"

} // end of namespace UtilLib

#endif // util_persistence_h_INCLUDED
