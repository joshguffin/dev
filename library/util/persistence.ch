#ifndef util_persistence_ch_INCLUDED
#define util_persistence_ch_INCLUDED

template <typename T>
Persistence<T>::Persistence(const std::string& path)
   : value_()
   , path_(path)
{
   std::ifstream input(path.c_str());
   if (input) {
      input >> value_;
      input.close();
   }

   stream_.open(path.c_str(), std::ios::trunc);
}

template <typename T>
bool
Persistence<T>::is_open() const
{
   return stream_.is_open();
}

// yuck
template <typename T>
void
Persistence<T>::write()
{
   stream_.close();
   stream_.open(path_.c_str(), std::ios::trunc);
   stream_ << value_;
}

template <typename T>
Persistence<T>&
Persistence<T>::operator=(const T& rhs)
{
   value_ = rhs;
   write();
   return *this;
}

template <typename T>
bool
Persistence<T>::operator==(const T& rhs) const
{
   return value_ == rhs;
}

#endif // util_persistence_ch_INCLUDED
