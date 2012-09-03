#ifndef util_commandline_h_INCLUDED
#define util_commandline_h_INCLUDED

#include <vector>
#include <string>
#include <boost/lexical_cast.hpp>

#include "include/headermacros.h"

namespace UtilLib {

// --- CommandLine declaration -------------------------------------------------

class CommandLine
{

public:

   template <typename T> class Flag;

   static void Init(int argc, char** argv);

private:

   static const std::string& Find(const std::string&);
   static bool Present(const std::string&);
   static CommandLine& Instance();

   CommandLine();

private:

   typedef std::vector<std::string> Arguments;
   Arguments arguments_;
};

// --- Flag declaration --------------------------------------------------------

template <typename T>
class CommandLine::Flag
{

public:

   Flag(const std::string& flag, const std::string& description);
   Flag(const std::string& flag, const std::string& description, const T& defaultValue);

   IMPLEMENT_ACCESSOR(const T& , value);

private:

   static T Cast(const std::string&);

   static T Parse(const std::string& flag, const std::string& description); // required
   static T Parse(const std::string& flag, const std::string& description, const T& defaultValue);

   T value_;
};

// --- CommandLine implementation ------------------------------------------------------------------


// --- Flag implementation -------------------------------------------------------------------------

template <typename T>
inline
CommandLine::Flag<T>::Flag(const std::string& flag, const std::string& description)
   : value_(Parse(flag, description))
{}

template <typename T>
inline
CommandLine::Flag<T>::Flag(const std::string& flag, const std::string& description, const T& defaultValue)
   : value_(Parse(flag, description, defaultValue))
{}


template <typename T>
inline T
CommandLine::Flag<T>::Parse(const std::string& flag, const std::string& description)
{
   const std::string& value = CommandLine::Find(flag);
   if (value.empty())
      abort();

   return Cast<T>(value);
}

template <typename T>
inline T
CommandLine::Flag<T>::Parse(const std::string& flag, const std::string& description, const T& defaultValue)
{
   const std::string& value = CommandLine::Find(flag);
   if (value.empty())
      return defaultValue;

   return Cast<T>(value);
}

template <typename T>
inline T
CommandLine::Flag<T>::Cast(const std::string& value)
{
   try {
      return boost::lexical_cast<T>(value);
   }
   catch(boost::bad_lexical_cast &) {
      return T();
   }
}

template <>
inline std::string
CommandLine::Flag<std::string>::Cast(const std::string& value)
{
   return value;
}

//Flag<int> stuff("hi", "bye", 5);

} // end of namespace UtilLib

#endif // util_commandline_h_INCLUDED
