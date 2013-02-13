#include "system/common.h"
#include "system/accountwrapper.h"

#include <boost/algorithm/string.hpp>

void
AccountWrapper::managedAccounts(const std::string& list)
{
   LogWrapper::managedAccounts(list);

   std::vector<Account> accounts;
   boost::split(accounts, list, boost::is_any_of(","));

   std::vector<std::string>::const_iterator it  = accounts.begin();
   std::vector<std::string>::const_iterator end = accounts.end();

   const bool subscribe = true;
   while (it != end)
      client().reqAccountUpdates(subscribe, *it++);
}

void
AccountWrapper::updateAccountValue(const std::string& key,
                                   const std::string& val,
                                   const std::string& currency,
                                   const std::string& accountName)
{
   Values& vals = accountData_[accountName];
   Entry entry  = { val, currency };
   vals[key]    = entry;
}

void
AccountWrapper::updatePortfolio(const TwsApi::Contract& contract,
                                int position,
                                double marketPrice,
                                double marketValue,
                                double averageCost,
                                double unrealizedPNL,
                                double realizedPNL,
                                const std::string& accountName)
{
   Position pos(position,
                marketPrice,
                marketValue,
                averageCost,
                unrealizedPNL,
                realizedPNL);

   Portfolio& portfolio = portfolios_[accountName];
   portfolio[contract] = pos;
}

void
AccountWrapper::updateAccountTime(const std::string& timeStamp)
{
   lastUpdateTimeStamp_ = timeStamp;
}

void
AccountWrapper::accountDownloadEnd(const std::string& accountName)
{
   LogWrapper::accountDownloadEnd(accountName);
   std::set<Consumer*>::iterator it  = consumers_.begin();
   std::set<Consumer*>::iterator end = consumers_.end();

   for (; it != end; ++it) {

      Portfolios::const_iterator pit  = portfolios_.begin();
      Portfolios::const_iterator pend = portfolios_.end();

      // a Poe loop, indeed
      for (; pit != pend; ++pit)
         (*it)->update(pit->first, pit->second, lastUpdateTimeStamp_);
   }
}

AccountWrapper::Position::Position()
   : position_(-1)
   , marketPrice_(-1.0)
   , marketValue_(-1.0)
   , averageCost_(-1.0)
   , unrealizedPNL_(-1.0)
   , realizedPNL_(-1.0)
{
}

AccountWrapper::Position::Position(int position,
                                   double marketPrice,
                                   double marketValue,
                                   double averageCost,
                                   double unrealizedPNL,
                                   double realizedPNL)
   : position_(position)
   , marketPrice_(marketPrice)
   , marketValue_(marketValue)
   , averageCost_(averageCost)
   , unrealizedPNL_(unrealizedPNL)
   , realizedPNL_(realizedPNL)
{
}

void
AccountWrapper::addConsumer(Consumer& consumer)
{
   consumers_.insert(&consumer);
}

void
AccountWrapper::removeConsumer(Consumer& consumer)
{
   consumers_.erase(&consumer);
}

AccountWrapper::Consumer::Consumer()
{
   TwsSystem::Instance().addConsumer(*this);
}

AccountWrapper::Consumer::~Consumer()
{
   TwsSystem::Instance().removeConsumer(*this);
}

