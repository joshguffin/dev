#ifndef system_contract_h_INCLUDED
#define system_contract_h_INCLUDED

#include <string>

namespace SystemLib {

class Contract
{

public:

   explicit Contract(const TwsApi::ContractDetails&);
   Contract(const std::string& symbol, const std::string& secType);

   class Derivative;

   IMPLEMENT_ACCESSORS(long , conid);

   IMPLEMENT_ACCESSORS(const std::string& , symbol);
   IMPLEMENT_ACCESSORS(const std::string& , exchange);
   IMPLEMENT_ACCESSORS(const std::string& , currency);

#define Fields(F) \
   F(STK)  \
   F(OPT)  \
   F(FUT)  \
   F(IND)  \
   F(FOP)  \
   F(CASH) \

   IMPLEMENT_COMPACT_ENUM_WRAPPER_IN_CLASS(Security, Fields);
#undef Fields

private:

   long        conid_;
   std::string symbol_;
   std::string exchange_;
   std::string currency_;
   std::string primaryExchange_;

   Security::Type securityType_;
};

IMPLEMENT_ENUM_PRINT(Contract::Security::Type, Contract::Security::ToString);


class Contract::Derivative : public Contract
{

public:

private:

   double      strike_;
   std::string expiry_;
   std::string right_;
};

} // end of namespace SystemLib

#endif // system_contract_h_INCLUDED
