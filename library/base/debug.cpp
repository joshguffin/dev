#include "system/common.h"
#include "debug.h"

// This is a 'circular' library dependence, but it won't hurt anything since
// there's no impementation file.
#include "string/ansishellcolors.h"

#include <boost/regex.hpp>
#include <tr1/unordered_map>

#ifdef DOUT
#undef DOUT
#endif

//#ifndef NDEBUG
//#define DOUT(trace) std::cout << trace << std::endl;
//#else
#define DOUT(trace) {}
//#endif

namespace DebugWrap {

//==============================================================================
// Helper functions
//==============================================================================

namespace {

static int IndentLevel = 1;

inline void
DecrementGlobalIndentLevel()
{
   if (IndentLevel <= 1)
      return;

   IndentLevel--;
}

inline int
IncrementGlobalIndentLevel()
{
   return IndentLevel++;
}

} // end of unnamed namespace

//==============================================================================
// Scope::Manager declaration
//==============================================================================

class Scope::Manager
{

public:

   static void   Add(const std::string&);
   static bool Match(const std::string&);
   static void Erase(const std::string&);
   static void Clear();

   static bool ScopeEnabled(size_t location);
   static size_t ScopeLocation(const std::string&);

   static std::string Known();

private:

   static void Update();
   static void Update(const boost::regex&);

private:

   typedef std::string ScopeName;
   typedef size_t ScopeIndex;

   typedef std::vector<boost::regex> Expressions;
   typedef std::vector<unsigned short> ScopeStates;

   typedef std::tr1::unordered_map<ScopeName, ScopeIndex> ScopeIndices;

   static Expressions  Expressions_;
   static ScopeStates  ScopeStates_;
   static ScopeIndices ScopeIndices_;
};

//==============================================================================
// Scope::Manager implementation
//==============================================================================
Scope::Manager::Expressions
Scope::Manager::Expressions_;

Scope::Manager::ScopeStates
Scope::Manager::ScopeStates_;

Scope::Manager::ScopeIndices
Scope::Manager::ScopeIndices_;

void
Scope::Manager::Add(const std::string& expression)
{
   DOUT("Scope::Manager::Add: " << expression);
   boost::regex regex(expression);
   Expressions_.push_back(regex);
   Update(regex);
}

void
Scope::Manager::Update()
{

   ScopeStates::iterator sit  = ScopeStates_.begin();
   ScopeStates::iterator send = ScopeStates_.end();

   for (; sit != send; ++sit)
      *sit = false;

   Expressions::const_iterator it  = Expressions_.begin();
   Expressions::const_iterator end = Expressions_.end();

   while (it != end)
      Update(*it++);
}

void
Scope::Manager::Update(const boost::regex& regex)
{
   ScopeIndices::const_iterator it  = ScopeIndices_.begin();
   ScopeIndices::const_iterator end = ScopeIndices_.end();

   for (; it != end; ++it) {
      const ScopeName& name = it->first;

      if (!boost::regex_match(name, regex))
         continue;
      DOUT("Scope::Manager::Update: " << name << " matches " << regex.str());
      ScopeIndex index = it->second;
      ScopeStates_[index] = true;
   }
}

bool
Scope::Manager::ScopeEnabled(size_t location)
{
   bool enabled = ScopeStates_[location];
   DOUT("Scope::Manager::ScopeEnabled: " << location << " => " << enabled);
   return enabled;
}

Scope::Manager::ScopeIndex
Scope::Manager::ScopeLocation(const std::string& scope)
{
   ScopeIndices::const_iterator loc = ScopeIndices_.find(scope);
   if (loc != ScopeIndices_.end())
      return loc->second;

   // Each 'scope' is a static that is built with a ScopeIndex for fast lookups
   // of its state in the vector
   ScopeIndex position = ScopeStates_.size();
   ScopeStates_.push_back(Match(scope));
   ScopeIndices_[scope] = position;

   DOUT("Scope::Manager::ScopeLocation: " << scope << ' ' << position);
   return position;
}

void
Scope::Manager::Clear()
{
   Expressions().swap(Expressions_);
   Update();
}

std::string
Scope::Manager::Known()
{
   std::string values;
   Expressions::iterator it  = Expressions_.begin();
   Expressions::iterator end = Expressions_.begin();

   if (it == end)
      return "";

   while (true) {
      const boost::regex& current = *it++;
      values += current.str();

      if (it == end)
         break;

      values += " ";
   }

   return values;
}

bool
Scope::Manager::Match(const std::string& str)
{
   Expressions::iterator it  = Expressions_.begin();
   Expressions::iterator end = Expressions_.end();

      DOUT("Scope::Manager::Match: testing " << str);

   while (it != end) {
      const boost::regex& current = *it++;
      DOUT("Scope::Manager::Match: checking " << current.str());
      if (boost::regex_match(str, current))
         return true;
   }

   return false;
}

void
Scope::Manager::Erase(const std::string& expression)
{
   Expressions::iterator it  = Expressions_.begin();
   Expressions::iterator end = Expressions_.end();

   while (it != end) {
      const boost::regex& current = *it++;
      if (expression != current.str())
         continue;

      Expressions_.erase(it);
      Update();
      break;
   }
}

//==============================================================================
// Scope implementation
//==============================================================================

Scope::Scope(Static& scope)
   : scope_(scope)
{
   scope.enter();
}

Scope::~Scope()
{
   scope_.exit();
}

void
Scope::Add(const std::string& value)
{
   Manager::Add(value);
}

void
Scope::Erase(const std::string& value)
{
   Manager::Erase(value);
}

void
Scope::ClearExpressions()
{
   Manager::Clear();
}

void
Scope::PrintEllipsis(int level)
{
   while (level-- > 0)
      cout << "... ";
}

//==============================================================================
// Scope::Static implementation
//==============================================================================

using namespace StringLib;
Scope::Static::Static(const std::string& id)
   : id_(id)
   , location_(Manager::ScopeLocation(id))
   , level_(0)
{
}

bool
Scope::Static::enabled() const
{
   return Manager::ScopeEnabled(location_);
}

void
Scope::Static::enter()
{
   int currentIndent = IncrementGlobalIndentLevel();
   levels_.push(currentIndent);
   level_ = currentIndent;

   PrintEllipsis(level_ - 1);
   cout << ">>> " << Color(id_, Color::BoldYellow) << endl;

   DOUT("Enter: set level to " << level_ << " for " << id_);
}

void
Scope::Static::exit()
{
   level_ = levels_.top();
   levels_.pop();
   DecrementGlobalIndentLevel();

   PrintEllipsis(level_ - 1);
   cout << "<<< " << Color(id_, Color::Yellow) << endl;

   DOUT("Exit: set level to " << level_ << " for " << id_);
}

} // end of namespace DebugWrap
