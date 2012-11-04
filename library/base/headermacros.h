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

#define IMPLEMENT_SPARSE_ENUM(Name, FieldsMacro)                               \
   IMPLEMENT_ENUM_IMPL(SPARSE, Name, FieldsMacro)                              \
   IMPLEMENT_ENUM_PRINT(Name, ToString)

#define IMPLEMENT_COMPACT_ENUM(Name, FieldsMacro)                              \
   IMPLEMENT_ENUM_IMPL(COMPACT, Name, FieldsMacro)                             \
   IMPLEMENT_ENUM_PRINT(Name, ToString)

// creates enum Name
#define IMPLEMENT_SPARSE_ENUM_WRAPPER(Name, FieldsMacro)                       \
   IMPLEMENT_ENUM_WRAPPER_IMPL(SPARSE, Name, FieldsMacro)                      \
   IMPLEMENT_ENUM_PRINT(Name::Type, Name::ToString)

#define IMPLEMENT_COMPACT_ENUM_WRAPPER(Name, FieldsMacro)                      \
   IMPLEMENT_ENUM_WRAPPER_IMPL(COMPACT, Name, FieldsMacro)                     \
   IMPLEMENT_ENUM_PRINT(Name::Type, Name::ToString)

#define IMPLEMENT_SPARSE_ENUM_WRAPPER_IN_CLASS(Name, FieldsMacro)              \
   IMPLEMENT_ENUM_WRAPPER_IMPL(SPARSE, Name, FieldsMacro)

#define IMPLEMENT_COMPACT_ENUM_WRAPPER_IN_CLASS(Name, FieldsMacro)             \
   IMPLEMENT_ENUM_WRAPPER_IMPL(COMPACT, Name, FieldsMacro)

//=== Enum implementation macros ===============================================

#define IMPLEMENT_ENUM_PRINT(Type, Function)                                   \
inline std::ostream&                                                           \
operator<<(std::ostream& os, Type t) {                                         \
   return os << Function(t);                                                   \
}

// compact implementation macros
#define IMPLEMENT_COMPACT_ENUM_DECLARATION_IMPL(Name) Name,
#define IMPLEMENT_COMPACT_ENUM_TOSTRING_IMPL(Name) case Name: return #Name;
#define IMPLEMENT_COMPACT_ENUM_FROMSTRING_IMPL(Name) if (str == #Name) return Name;

// sparse implementation macros
#define IMPLEMENT_SPARSE_ENUM_DECLARATION_IMPL(Name, Value) Name = Value,
#define IMPLEMENT_SPARSE_ENUM_TOSTRING_IMPL(Name, Value)    case Name: return #Name;
#define IMPLEMENT_SPARSE_ENUM_FROMSTRING_IMPL(Name, Value)  if (str == #Name) return Name;

//=== Common enum implementation ===============================================

#define IMPLEMENT_ENUM_IMPL(EnumType, Type, FieldsMacro)                       \
   enum Type {                                                                 \
      FieldsMacro(IMPLEMENT_##EnumType##_ENUM_DECLARATION_IMPL)                \
      Unknown                                                                  \
   };                                                                          \
                                                                               \
   static inline std::string ToString(Type t) {                                \
      switch (t) {                                                             \
         FieldsMacro(IMPLEMENT_##EnumType##_ENUM_TOSTRING_IMPL)                \
         default:                                                              \
            std::stringstream ss;                                              \
            ss << #Type << "::Unknown(" << t << ')';                           \
            return ss.str();                                                   \
      }                                                                        \
   }                                                                           \
                                                                               \
   static inline Type FromString(const std::string& str) {                     \
      FieldsMacro(IMPLEMENT_##EnumType##_ENUM_FROMSTRING_IMPL)                 \
      return Unknown;                                                          \
   }

#define IMPLEMENT_ENUM_WRAPPER_IMPL(EnumType, Name, FieldsMacro)               \
   struct Name { IMPLEMENT_ENUM_IMPL(EnumType, Type, FieldsMacro) };

#endif // headermacros_h_INCLUDED
