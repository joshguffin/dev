#ifndef system_twsclientbase_h_INCLUDED
#define system_twsclientbase_h_INCLUDED

#include "system/logwrapper.h"
#include "system/twssocket.h"

#include <boost/scoped_ptr.hpp>
#include <memory>
#include <stdio.h>

class TwsClientBase : public LogWrapper
{
public:

	TwsClientBase(bool print = true);
	~TwsClientBase();

	void processMessages();
   TwsSocket& socket();

public:

   bool connect(const std::string& host, unsigned port);
	bool isConnected() const;

private:

	virtual void error(const int id, const int errorCode, const std::string errorString);

private:

	boost::scoped_ptr<TwsSocket> client_;
};

#endif // system_twsclientbase_h_INCLUDED
