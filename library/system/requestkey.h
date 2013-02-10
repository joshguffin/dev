#ifndef system_requestkey_h_INCLUDED
#define system_requestkey_h_INCLUDED

#include <boost/functional/hash.hpp>

class RequestKey
{

public:

   RequestKey(const std::string&);

   IMPLEMENT_ACCESSORS(const TwsApi::Contract& , contract);

   bool operator==(const RequestKey&) const;

private:

   TwsApi::Contract contract_;
};

inline RequestKey::RequestKey(const std::string& symbol)
{
   contract_.symbol   = symbol;
   contract_.secType  = "STK";
   contract_.exchange = "SMART";
   contract_.currency = "USD";
}

inline size_t
hash_value(const RequestKey& key)
{
   std::size_t seed = 0;

   boost::hash<std::string> stringHash;

   const TwsApi::Contract& contract = key.contract();

   boost::hash_combine(seed, stringHash(contract.symbol));
   boost::hash_combine(seed, stringHash(contract.secType));
   boost::hash_combine(seed, stringHash(contract.exchange));
   boost::hash_combine(seed, stringHash(contract.currency));

   return seed;
}

inline bool
RequestKey::operator==(const RequestKey& key) const
{
   return key.contract_ == contract_;
}

inline std::ostream&
operator<<(std::ostream& os, const RequestKey& key)
{
   return os << key.contract();
}

#endif // system_requestkey_h_INCLUDED
