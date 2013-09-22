#ifndef udpserver_h_INCLUDED
#define udpserver_h_INCLUDED


class UdpServer
{

public:

   UdpServer(unsigned short port);

   void processMessages();

   virtual void handleMessage(const char*, unsigned);

private:

   int fd_;
   unsigned short port_;
};

#endif // udpserver_h_INCLUDED

