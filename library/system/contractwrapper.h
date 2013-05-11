#ifndef system_contractwrapper_h_INCLUDED
#define system_contractwrapper_h_INCLUDED

#include "system/accountwrapper.h"
#include "system/contract.h"

namespace SystemLib {

class ContractWrapper : public AccountWrapper
{

public:

   ContractWrapper() {}
   virtual ~ContractWrapper() {}


   void requestDetails(const std::string& symbol, Contract::Security::Type);

private:

   virtual void     contractDetails(int reqId, const TwsApi::ContractDetails&);
   virtual void bondContractDetails(int reqId, const TwsApi::ContractDetails&);
   virtual void contractDetailsEnd(int reqId);


};

} // end of namespace SystemLib

#endif // system_contractwrapper_h_INCLUDED
