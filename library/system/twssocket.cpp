#include "system/common.h"

#include "twssocket.h"

// ugh.
namespace TwsApi {
#include "twsapi/IB_LIBRARY/Shared/EClientSocketBaseImpl.h"
}

#include <arpa/inet.h>
#include <errno.h>
#include <string.h>
#include <iostream>

using std::cout;
using std::endl;
using namespace TwsApi;

namespace SystemLib {

///////////////////////////////////////////////////////////
// member funcs
TwsSocket::TwsSocket(EWrapper& wrap)
   : EClientSocketBase(&wrap)
   , wrapper_(wrap)
	, fd_(-1)
{
}

TwsSocket::~TwsSocket()
{
}

bool
TwsSocket::connect(const std::string& host, unsigned port)
{
   const int clientID = 0;
   return TwsSocket::eConnect(host.c_str(), port, clientID);
}

bool
TwsSocket::eConnect(const char* host, unsigned int port, int clientId)
{
	// reset errno
	errno = 0;

	// already connected?
	if (fd_ >= 0) {
		errno = EISCONN;
		wrapper_.error(NO_VALID_ID, ALREADY_CONNECTED.code(), ALREADY_CONNECTED.msg());
		return false;
	}

	// create socket
	fd_ = socket(AF_INET, SOCK_STREAM, 0);

	// cannot create socket
	if (fd_ < 0) {
		wrapper_.error(NO_VALID_ID, FAIL_CREATE_SOCK.code(), FAIL_CREATE_SOCK.msg());
		return false;
	}

	// use local machine if no host passed in
	if (!(host && *host))
		host = "127.0.0.1";

	// starting to connect to server
	struct sockaddr_in sa;
	memset(&sa, 0, sizeof(sa));
	sa.sin_family = AF_INET;
	sa.sin_port = htons(port);
	sa.sin_addr.s_addr = inet_addr(host);

	// try to connect
	int result = ::connect(fd_, (struct sockaddr *) &sa, sizeof(sa));
	if (result < 0) {
		// error connecting
		wrapper_.error(NO_VALID_ID, CONNECT_FAIL.code(), CONNECT_FAIL.msg());
		return false;
	}

	// set client id
	setClientId(clientId);

	onConnectBase();

	while (isSocketOK() && !isConnected()) {
		if (!checkMessages()) {
			wrapper_.error(NO_VALID_ID, CONNECT_FAIL.code(), CONNECT_FAIL.msg());
			return false;
		}
	}

	// successfully connected
	return true;
}

void
TwsSocket::disconnect()
{
   TwsSocket::eDisconnect();
}

void
TwsSocket::eDisconnect()
{
	if (fd_ >= 0 )
		// close socket
		close(fd_);
	fd_ = -1;
	eDisconnectBase();
}

bool
TwsSocket::isSocketOK() const
{
	return (fd_ >= 0);
}

int
TwsSocket::send(const char* buf, size_t sz)
{
	if (sz == 0)
		return 0;

	int nResult = ::send(fd_, buf, sz, 0);

	if (nResult == -1 && !handleSocketError()) {
		return -1;
	}
	if (nResult <= 0) {
		return 0;
	}
	return nResult;
}

int
TwsSocket::receive(char* buf, size_t sz)
{
	if (sz == 0)
		return 0;

	int nResult = ::recv(fd_, buf, sz, 0);

	if (nResult == -1 && !handleSocketError()) {
		return -1;
	}
	if (nResult <= 0) {
		return 0;
	}
	return nResult;
}

void
TwsSocket::processMessages(timeval& interval)
{
   errno = 0;

   fd_set readSet, writeSet, errorSet;

   if (fd_ < 0 )
      return;

   FD_ZERO(&readSet);
   errorSet = writeSet = readSet;

   FD_SET(fd_, &readSet);

   if (!isOutBufferEmpty())
      FD_SET(fd_, &writeSet);

   FD_CLR(fd_, &errorSet);

   int ret = select(fd_ + 1, &readSet, &writeSet, &errorSet, &interval);

   // timeout
   if (ret == 0)
      return;

   if (ret < 0) {
      cout << "TwsSocket::processMessages: select error " << errno << endl;
      eDisconnect();
      return;
   }

   if (fd_ < 0)
      return;

   int socketError = FD_ISSET(fd_, &errorSet);
   if (socketError)
      onError();

   if (fd_ < 0)
      return;

   int writeReady = FD_ISSET(fd_, &writeSet);
   if (writeReady)
      onSend();

   if (fd_ < 0)
      return;

   int readReady = FD_ISSET(fd_, &readSet);
   if (readReady)
      onReceive();
}

///////////////////////////////////////////////////////////
// callbacks from socket

void
TwsSocket::onReceive()
{
	if (!handleSocketError())
		return;

	checkMessages();
}

void
TwsSocket::onSend()
{
	if (!handleSocketError())
		return;

	sendBufferedData();
}

void
TwsSocket::onError()
{
	handleSocketError();
}

///////////////////////////////////////////////////////////
// helper
bool
TwsSocket::handleSocketError()
{
	// no error
	if (errno == 0)
		return true;

	// Socket is already connected
	if (errno == EISCONN) {
		return true;
	}

	if (errno == EWOULDBLOCK)
		return false;

	if (errno == ECONNREFUSED)
		wrapper_.error(NO_VALID_ID, CONNECT_FAIL.code(), CONNECT_FAIL.msg());
   else
      wrapper_.error(NO_VALID_ID, SOCKET_EXCEPTION.code(),
			SOCKET_EXCEPTION.msg() + strerror(errno));
	// reset errno
	errno = 0;
	eDisconnect();
	return false;
}

} // end of namespace SystemLib
