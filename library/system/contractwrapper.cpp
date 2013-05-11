#include "system/common.h"

#include "system/contractwrapper.h"

namespace SystemLib {

void
ContractWrapper::requestDetails(const std::string& symbol,
                                Contract::Security::Type type)
{
   TwsApi::Contract contract;
   contract.symbol = symbol;
   contract.secType = Contract::Security::ToString(type);
   contract.exchange = "SMART";

int id = 0;
   client().reqContractDetails(id, contract);
}

void
ContractWrapper::contractDetails(int reqId, const TwsApi::ContractDetails& details)
{
   Contract contract(details);
}

void
ContractWrapper::bondContractDetails(int reqId, const TwsApi::ContractDetails& details)
{
}

void
ContractWrapper::contractDetailsEnd(int reqId)
{
   cout << "ContractWrapper::contractDetailsEnd(" << reqId << ')' << endl;
}

} // end of namespace SystemLib
