#ifndef ibwrap_twsclientbase_h_INCLUDED
#define ibwrap_twsclientbase_h_INCLUDED

#include "ibwrap/logwrapper.h"
#include "ibwrap/twssocket.h"

#include <boost/scoped_ptr.hpp>
#include <memory>
#include <stdio.h>

class TwsClientBase : public LogWrapper
{
public:

	TwsClientBase();
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

#endif // ibwrap_twsclientbase_h_INCLUDED
