#ifndef headermacros_h_INCLUDED
#define headermacros_h_INCLUDED


#define IMPLEMENT_ACCESSOR(Type , Name) \
   Type Name() const { return Name##_; }

#define IMPLEMENT_ACCESSORS(Type , Name) \
   Type Name() const { return Name##_; } \
   void Name(const Type& t) { Name##_ = t; }


//==============================================================================

#define IMPLEMENT_SPARSE_ENUM_DECLARATION_IMPL(Name, Value) Name = Value,
#define IMPLEMENT_SPARSE_ENUM_TOSTRING_IMPL(Name, Value) case Name: return #Name;
#define IMPLEMENT_SPARSE_ENUM_PRINT_IMPL(Name, Value)    case Name: os << #Name;
#define IMPLEMENT_SPARSE_ENUM_FROMSTRING_IMPL(Name, Value) if (str == #Name) return Name;

#define IMPLEMENT_SPARSE_ENUM_STRUCT(FieldsMacro, Name)
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
}

#endif // headermacros_h_INCLUDED

