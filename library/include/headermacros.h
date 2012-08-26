#ifndef headermacros_h_INCLUDED
#define headermacros_h_INCLUDED


#define IMPLEMENT_ACCESSOR(Type , Name) \
   Type Name() const { return Name##_; }

#define IMPLEMENT_ACCESSORS(Type , Name) \
   Type Name() const { return Name##_; } \
   void Name(Type t) { Name##_ = t; }

#define IMPLEMENT_STATIC_ACCESSOR(Type , Name, Var) \
   static Type Name() const { return Instance().Var##_; }

//==============================================================================

#define IMPLEMENT_SPARSE_ENUM_DECLARATION_IMPL(Name, Value) Name = Value,
#define IMPLEMENT_SPARSE_ENUM_TOSTRING_IMPL(Name, Value) case Name: return #Name;
#define IMPLEMENT_SPARSE_ENUM_PRINT_IMPL(Name, Value)    case Name: os << #Name;
#define IMPLEMENT_SPARSE_ENUM_FROMSTRING_IMPL(Name, Value) if (str == #Name) return Name;

/*
#define IMPLEMENT_SPARSE_ENUM_STRUCT(Name, FieldsMacro)
struct Name
{
   enum Type { FieldsMacro(IMPLEMENT_ENUM_DECLARATION_IMPL) Unknown##Name##Value };

   static std::string ToString(Type t) {
      switch (t) {
         FieldsMacro(IMPLEMENT_ENUM_FROMSTRING_IMPL);
         default:
            return #Name + "::UnknownEnumValue(" + static_cast<int>(t) + ')';
      }
   }

   static Type FromString(const std::string& t) {
      FieldsMacro(IMPLEMENT_SPARSE_ENUM_FROMSTRING_IMPL);
      return Unknown##Name##Value;
   }
};
inline std::ostream&
operator<<(std::ostream& os, Name::Type t) {
   switch (t) {
      FieldsMacro(IMPLEMENT_SPARSE_ENUM_PRINT_IMPL);
      os << #Name << "::UnknownEnumValue(" << static_cast<int>(t) << ')';
   }
   return os;
}
*/

//==============================================================================
// Boost unit test definitions
//==============================================================================

/*
#ifdef BOOST_TEST_MAIN

#define FieldsMacroExample(F) \
   F(EnumVal1, 'a') \
   F(EnumVal2, 'c') \
   F(EnumVal3, 'D') \
   F(EnumVal4, 'G') \
   F(EnumVal5, ' ')


BOOST_AUTO_TEST_CASE(EnumStructExample)
{
   IMPLEMENT_SPARSE_ENUM_STRUCT(SomeStruct, FieldsMacroExample);
}

#undef FieldsMacroExample

#endif // BOOST_TEST_MAIN
*/

#endif // headermacros_h_INCLUDED

