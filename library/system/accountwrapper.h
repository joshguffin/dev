#ifndef system_accountwrapper_h_INCLUDED
#define system_accountwrapper_h_INCLUDED

#include "system/datawrapper.h"

#include <vector>
#include <set>
#include <boost/unordered_map.hpp>

namespace StringLib { class StringTable; }

namespace SystemLib {

class AccountWrapper : public DataWrapper
{

public:

   struct Consumer;
   struct Position;

   typedef std::string Account;
   typedef std::map<TwsApi::Contract, Position> Portfolio;

protected:

   AccountWrapper() {}

   void failed(TwsApi::TickerId id, const std::string& reason, int code);

private:

   // Consumer access
   void    addConsumer(Consumer&);
   void removeConsumer(Consumer&);

	virtual void updateAccountTime(const std::string& timeStamp);
	virtual void updateAccountValue(const std::string& key, const std::string& val, const std::string& currency, const std::string& accountName);
	virtual void updatePortfolio(const TwsApi::Contract& contract, int position, double marketPrice, double marketValue, double averageCost, double unrealizedPNL, double realizedPNL, const std::string& accountName);
	virtual void accountDownloadEnd(const std::string& name);
	virtual void managedAccounts(const std::string& list);

private:

   struct Entry { std::string value; std::string currency; };

   typedef std::string Key;
   typedef boost::unordered_map<Key,     Entry>     Values;
   typedef boost::unordered_map<Account, Values>    AccountData;
   typedef boost::unordered_map<Account, Portfolio> Portfolios;

   typedef std::set<Consumer*> Consumers;

   Consumers   consumers_;
   AccountData accountData_;
   Portfolios  portfolios_;

   std::string lastUpdateTimeStamp_;
};

struct AccountWrapper::Position
{
public:

   Position();
   Position(int, double, double, double, double, double);

   IMPLEMENT_ACCESSORS(double, marketPrice);
   IMPLEMENT_ACCESSORS(double, marketValue);
   IMPLEMENT_ACCESSORS(double, averageCost);
   IMPLEMENT_ACCESSORS(double, unrealizedPNL);
   IMPLEMENT_ACCESSORS(double, realizedPNL);
   IMPLEMENT_ACCESSORS(int, position);

   template <typename T>
   void dump(T&) const;

   template <typename T>
   static void Headers(T&);

private:
   int position_;
   double marketPrice_;
   double marketValue_;
   double averageCost_;
   double unrealizedPNL_;
   double realizedPNL_;
};

struct AccountWrapper::Consumer
{
   Consumer();
   virtual ~Consumer();

   virtual void update(const std::string& account,
                       const Portfolio& portfolio,
                       const std::string& timestamp) = 0;
};

// appropriate for StringLib::StringTable and StringLib::CSV
template <typename T>
inline void
AccountWrapper::Position::dump(T& streamManip) const
{
   streamManip
      << position_
      << marketPrice_
      << marketValue_
      << averageCost_
      << unrealizedPNL_
      << realizedPNL_;
}

// appropriate for StringLib::StringTable and StringLib::CSV
template <typename T>
inline void
AccountWrapper::Position::Headers(T& streamManip)
{
   streamManip
      << "Position"
      << "Market Price"
      << "Market Value"
      << "Average Cost"
      << "Unrealized PnL"
      << "Realized PnL";
}

} // end of namespace SystemLib

#endif // system_accountwrapper_h_INCLUDED
