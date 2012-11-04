#include "system/common.h"

#include "string/stringtable.h"

#include <assert.h>
#include <iomanip>
#include <iostream>

namespace StringLib {

StringTable::EndRow StringTable::endr;

//==============================================================================
// StringTable implementation
//==============================================================================

StringTable::StringTable()
   : separator_(" ")
   , trimLastColumn_(true)
   , rows_(0)
{}

StringTable::StringTable(const std::string& separator,
                         const std::string& bol,
                         const std::string& eol)
   : separator_(separator)
   , beginningOfLine_(bol)
   , endOfLine_(eol)
   , trimLastColumn_(true)
   , rows_(0)
{}

void
StringTable::addRow(const StringTable::Row& row)
{
   size_t rowWidth = row.size();

   while (columns_.size() < rowWidth)
      columns_.push_back(Column(rows_));


   Columns::iterator       cit  = columns_.begin();
   Columns::const_iterator cend = columns_.end();
   Row::const_iterator rit      = row.begin();
   Row::const_iterator rend     = row.end();

   while (cit != cend) {
      static std::string empty;

      Column& column           = *cit++;
      const std::string& entry = (rit == rend ? empty : *rit++);
      column.width_            = std::max(column.width_, entry.size());

      column.entries_.push_back(entry);
   }

   rows_++;
}

bool
StringTable::setMiniumumWidth(size_t column, size_t width)
{
   if (column > columns_.size() - 1)
      return false;

   columns_[column].width_ = width;
   return true;
}

bool
StringTable::setAlignment(size_t column, ColumnAlignment alignment)
{
   if (column >= columns_.size())
      return false;

   columns_[column].alignment_ = alignment;
   return true;
}

/**
 * Width does not include newlines
 */
size_t
StringTable::outputWidth() const
{
   if (!rows_)
      return 0;

   Columns::const_iterator cit  = columns_.begin();
   Columns::const_iterator cend = columns_.end();
   size_t separatorWidth  = separator_.size();
   size_t width           = beginningOfLine_.size() + endOfLine_.size();

   assert(cit != cend);

   while (true) {
      width += cit++->width_;
      if (cit != cend)
         width += separatorWidth;
      else
         break;
   }

   return width;
}

std::ostream&
StringTable::write(std::ostream& os) const
{
   if (!rows_)
      return os;

   size_t row = 0;
   while (true) {

      Columns::const_iterator cit  = columns_.begin();
      Columns::const_iterator cend = columns_.end();

      assert(cit != cend);

      os << beginningOfLine_;

      // print the row
      while (true) {

         const Column& column = *cit++;
         bool end     = cit == cend;
         bool trimCol = false;

         if (end) {
            trimCol = (trimLastColumn_ &&
                       endOfLine_.empty() &&
                       column.alignment_ == Left);
         }

         if (column.alignment_ == Left)
            os << std::left;
         else
            os << std::right;

         if (!trimCol)
            os << std::setw(column.width_);

         os << column.entries_[row];

         if (end)
            break;
         else
            os << separator_;
      }

      ++row;
      if (row != rows_)
         os << endOfLine_ << '\n';
      else
         break;
   }

   return os;
}

std::string
StringTable::str() const
{
   std::stringstream ss;
   write(ss);
   return ss.str();
}

} // end of namespace StringLib
