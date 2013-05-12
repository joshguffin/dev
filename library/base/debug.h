#ifndef debug_h_INCLUDED
#define debug_h_INCLUDED

// TODO: Fix this to recognize flags
#ifndef NDEBUG
#define DEBUG_ENABLED
#else
//#define DEBUG_ENABLED
#endif

#include <stack>
#include <string>

//==============================================================================
// Usage macros
//==============================================================================

#ifdef DEBUG_ENABLED
#define Dscope(id)                                     \
   static DebugWrap::Scope::Static _dscopeStatic_(id); \
   DebugWrap::Scope::Scope scopedDebugStackObject(_dscopeStatic_);

#define Dout(trace) {                         \
   if (_dscopeStatic_.enabled()) {            \
      int level = _dscopeStatic_.level();     \
      DebugWrap::Scope::PrintEllipsis(level); \
      std::cout << trace << std::endl;        \
   } }

#define Dlog(trace) {              \
   if (_dscopeStatic_.enabled()) { \
      LOG << trace << endm;        \
   } }

#else  // DEBUG_ENABLED
#define Dscope(id) {}
#define Dout(id)   {}
#define Dlog(id)   {}
#endif // DEBUG_ENABLED

//==============================================================================
// Scope declaration
//==============================================================================

namespace DebugWrap {

class Scope
{
public:

   class Static;
   class Manager;

   Scope(Static&);
   ~Scope();

public:

   static void   Add(const std::string& expression);
   static void Erase(const std::string& expression);
   static void ClearExpressions();
   static void PrintEllipsis(int);

private:

   Static& scope_;
};

class Scope::Static
{
public:
   Static(const std::string& id);

   bool enabled() const;
   int level() const { return level_; }
   const std::string& id() const { return id_; }

   void enter();
   void exit();

private:

   std::string id_;
   size_t location_;

   int level_;
   std::stack<int> levels_;
};

} // end of namespace DebugWrap

#endif // debug_h_INCLUDED
