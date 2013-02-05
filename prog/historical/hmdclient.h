#ifndef hmdclient_h_INCLUDED
#define hmdclient_h_INCLUDED

#include "system/twsclientbase.h"

#include "datapoint.h"

#include <boost/scoped_ptr.hpp>
#include <memory>
#include <stdio.h>

class HmdClient : public TwsClientBase
{
public:

	HmdClient();
	~HmdClient();

   IMPLEMENT_ACCESSOR(bool , completed);

   void request(const std::string& symbol, const std::string&);
   void dump() const;

private:

	virtual void scannerData(int, int, const ContractDetails&, const std::string&, const std::string&, const std::string&, const std::string&);
	virtual void scannerDataEnd(int);
	virtual void scannerParameters(const std::string&);
	virtual void historicalData(TickerId, const std::string&, double, double, double, double, int, int, double, int);
	virtual void error(const int, const int, const std::string);

private:

   bool requested_;
   bool completed_;
   TickerId id_;

   std::vector<DataPoint> data_;

   static TickerId NextClientId_;
};

#endif // hmdclient_h_INCLUDED
