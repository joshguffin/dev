#ifndef socket_h_INCLUDED
#define socket_h_INCLUDED

#include <boost/asio.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/noncopyable.hpp>

// RAII wrapper for sockets
class UdpSocket
{

public:

   UdpSocket(unsigned port);

   struct Message;
   void send(const Message& message);

private:

   void listen();
   void handleReceive(const boost::system::error_code&);
   void handleSend(boost::shared_ptr<std::string>,
                   const boost::system::error_code&,
                   std::size_t);

private:

   boost::asio::io_service service_;
   boost::asio::ip::udp::socket socket_;
   boost::asio::ip::udp::endpoint endpoint_;

   std::vector<char>    receiveBuffer_;
   std::vector<Message> messageBuffer_;
};


struct UdpSocket::Message
{
   Message(const boost::asio::ip::udp::endpoint& ep, const std::string& msg)
      : endpoint(ep), message(msg)
   {}

   boost::asio::ip::udp::endpoint endpoint;
   std::string message;
};

#endif // socket_h_INCLUDED
