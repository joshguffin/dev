#ifndef system_hmdrequestkey_h_INCLUDED
#define system_hmdrequestkey_h_INCLUDED

#include <boost/functional/hash.hpp>

namespace SystemLib {

class HmdRequestKey
{

public:

   HmdRequestKey(const std::string&);

   IMPLEMENT_ACCESSORS(const TwsApi::Contract& , contract);

   bool operator==(const HmdRequestKey&) const;

private:

   TwsApi::Contract contract_;
};

std::ostream& operator<<(std::ostream&, const HmdRequestKey&);
size_t hash_value(const HmdRequestKey&);

} // end of namespace SystemLib

#endif // system_hmdrequestkey_h_INCLUDED
