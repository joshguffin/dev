#ifndef twssocket_h_INCLUDED
#define twssocket_h_INCLUDED

#include "twsapi/common.h"

namespace TwsApi {
class EWrapper;
}

namespace SystemLib {

class TwsSocket : public TwsApi::EClientSocketBase
{
public:

	TwsSocket(TwsApi::EWrapper& ptr);
	~TwsSocket();

	bool isSocketOK() const;
   void processMessages();

   bool connect(const std::string& host, unsigned port);
   void disconnect();

   void updateTime();

private:

	virtual int send(const char* buf, size_t sz);
	virtual int receive(char* buf, size_t sz);

	virtual bool eConnect(const char* host, unsigned int port, int clientId=0);
	virtual void eDisconnect();

private:

	// callback from socket
	void onReceive();
	void onSend();
	void onError();

public:
	// helper
	bool handleSocketError();

private:

   TwsApi::EWrapper& wrapper_;
	time_t sleepDeadline_;
	int fd_;
};

} // end of namespace SystemLib

#endif // twssocket_h_INCLUDED
