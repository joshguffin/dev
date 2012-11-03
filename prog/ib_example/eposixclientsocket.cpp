#include "eposixclientsocket.h"

#include "ib/TwsSocketClientErrors.h"
#include "ib/EWrapper.h"

#include <arpa/inet.h>
#include <errno.h>
#include <sys/select.h>
#include <string.h>

///////////////////////////////////////////////////////////
// member funcs
TwsSocket::TwsSocket(EWrapper& ptr)
   : EClientSocketBase(&ptr)
{
	fd_ = -1;
}

TwsSocket::~TwsSocket()
{
}

bool
TwsSocket::eConnect(const char* host, unsigned int port, int clientId)
{
	// reset errno
	errno = 0;

	// already connected?
	if (fd_ >= 0) {
		errno = EISCONN;
		getWrapper()->error(NO_VALID_ID, ALREADY_CONNECTED.code(), ALREADY_CONNECTED.msg());
		return false;
	}

	// create socket
	fd_ = socket(AF_INET, SOCK_STREAM, 0);

	// cannot create socket
	if (fd_ < 0) {
		getWrapper()->error(NO_VALID_ID, FAIL_CREATE_SOCK.code(), FAIL_CREATE_SOCK.msg());
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
	int result = connect(fd_, (struct sockaddr *) &sa, sizeof(sa));
	if (result < 0) {
		// error connecting
		getWrapper()->error(NO_VALID_ID, CONNECT_FAIL.code(), CONNECT_FAIL.msg());
		return false;
	}

	// set client id
	setClientId(clientId);

	onConnectBase();

	while (isSocketOK() && !isConnected()) {
		if (!checkMessages()) {
			getWrapper()->error(NO_VALID_ID, CONNECT_FAIL.code(), CONNECT_FAIL.msg());
			return false;
		}
	}

	// successfully connected
	return true;
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
TwsSocket::fd() const
{
	return fd_;
}

int
TwsSocket::send(const char* buf, size_t sz)
{
	if (sz <= 0)
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
	if (sz <= 0)
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
		getWrapper()->error(NO_VALID_ID, CONNECT_FAIL.code(), CONNECT_FAIL.msg());
   else
      getWrapper()->error(NO_VALID_ID, SOCKET_EXCEPTION.code(),
			SOCKET_EXCEPTION.msg() + strerror(errno));
	// reset errno
	errno = 0;
	eDisconnect();
	return false;
}
