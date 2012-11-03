#ifndef eposixclientsocket_def
#define eposixclientsocket_def

#include "ib/EClientSocketBase.h"

class EWrapper;

class TwsSocket : public EClientSocketBase
{
public:

	explicit TwsSocket(EWrapper& ptr);
	~TwsSocket();

	virtual bool eConnect(const char* host, unsigned int port, int clientId=0);
	virtual void eDisconnect();

	bool isSocketOK() const;
	int fd() const;

private:

	int send(const char* buf, size_t sz);
	int receive(char* buf, size_t sz);

public:
	// helper
	bool handleSocketError();

private:

	int fd_;
};

#endif
