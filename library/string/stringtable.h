#ifndef string_stringtable_h_INCLUDED
#define string_stringtable_h_INCLUDED

#include "include/headermacros.h"

#include <vector>
#include <string>
#include <sstream>
#include <map>

#include <iostream>

namespace StringLib {

class StringTable
{
   template <typename T> friend StringTable& operator<<(StringTable&, const T&);
   friend std::ostream& operator<<(std::ostream&, const StringTable&);

public:

   struct EndRow{};
   static EndRow endr;

   enum ColumnAlignment { Left, Right };

public:

   typedef std::vector<std::string> Row;

   StringTable();
   StringTable(const std::string& separator,
               const std::string& bol,
               const std::string& eol);

   std::string str() const;

   void addRow(const Row&);
   bool setAlignment(size_t column, ColumnAlignment);

   bool empty() const { return columns_.empty(); }
   size_t outputWidth() const;

   bool setMiniumumWidth(size_t column, size_t width);

   IMPLEMENT_ACCESSORS( bool               , trimLastColumn  );
   IMPLEMENT_ACCESSORS( const std::string& , separator       );
   IMPLEMENT_ACCESSORS( const std::string& , beginningOfLine );
   IMPLEMENT_ACCESSORS( const std::string& , endOfLine       );

private:

   std::ostream& write(std::ostream&) const;

private:

   struct Column;
   typedef std::vector<Column> Columns;

   std::string separator_;
   std::string beginningOfLine_;
   std::string endOfLine_;

   Columns columns_;
   Row  rowStream_;

   bool trimLastColumn_;
   size_t rows_;
};

inline std::ostream&
operator<<(std::ostream& os, const StringTable& table)
{
   return table.write(os);
}

template <typename T>
inline StringTable& operator<<(StringTable& table, const T& value);

template <>
inline StringTable&
operator<<(StringTable& table, const StringTable::EndRow&)
{
   table.addRow(table.rowStream_);
   StringTable::Row().swap(table.rowStream_);
   return table;
}

template <>
inline StringTable&
operator<<(StringTable& table, const std::string& value)
{
   table.rowStream_.push_back(value);
   return table;
}

template <typename T>
inline StringTable&
operator<<(StringTable& table, const T& value)
{
   std::stringstream ss;
   ss << value;
   return table << ss.str();
}

struct StringTable::Column
{
   Column() : width_(0), alignment_(Left) {}
   Column(size_t width) : entries_(width), width_(0), alignment_(Left) {}
   ~Column() {}

   typedef std::vector<std::string> Entries;
   Entries entries_;
   size_t width_;
   ColumnAlignment alignment_;
};



} // end of namespace StringLib

#endif // string_stringtable_h_INCLUDED

