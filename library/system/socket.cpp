#include "system/common.h"
#include "system/socket.h"

#include <boost/bind.hpp>

using boost::asio::ip::udp;

UdpSocket::UdpSocket(unsigned port)
   : socket_(service_, udp::endpoint(udp::v4(), port))
   , receiveBuffer_(2048)
{
   socket_.non_blocking(true);

   listen();
}

void
UdpSocket::listen()
{
   static const boost::asio::socket_base::message_flags flags(0);

   boost::system::error_code error;

   socket_.async_receive_from(boost::asio::buffer(receiveBuffer_),
                              endpoint_,
                              flags,
                              error);
}

void
UdpSocket::send(const Message& message)
{
   socket_.async_send_to(boost::asio::buffer(message.message),
                         message.endpoint,
                         boost::bind(&UdpSocket::handleSend,
                                     this,
                                     boost::asio::placeholders::error,
                                     boost::asio::placeholders::bytes_transferred));
}

void
UdpSocket::handleReceive(const boost::system::error_code& error)
{
   if (error && error != boost::asio::error::message_size)
      throw boost::system::system_error(error);

   std::string message(&receiveBuffer_[0]);

   Message result(endpoint_, message);
   messageBuffer_.push_back(result);

   listen();
}


void
UdpSocket::handleSend(boost::shared_ptr<std::string> message,
                      const boost::system::error_code& error,
                      std::size_t bytes_transferred)
{
   cout << *message 
      << ' ' << error
      << ' ' << bytes_transferred
      << endl;
}

