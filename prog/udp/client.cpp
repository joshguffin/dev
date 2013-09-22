#include "system/udpserver.h"
#include <vector>
#include <string>
#include <iostream>
using std::cout;
using std::endl;

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 


#define BUFSIZE 1024

/* 
 * error - wrapper for perror
 */
void error(const std::string& msg)
{
   perror(msg.c_str());
   exit(0);
}


int
main(int argc, char** argv)
{
   std::vector<std::string> args(argv, argv + argc);

   if (args.size() < 4) {
      cout << "Usage: " << args[0] << " <host> <port> <message>" << endl;
      return EXIT_FAILURE;
   }

   typedef std::vector<std::string> Args;
   Args::iterator it  = args.begin() + 3;
   Args::iterator end = args.end();

   std::string message;
   while (true) {
      const std::string& arg = *it++;
      message += arg;

      if (it == end)
         break;

      message += " ";
   }

   int sockfd, portno, n;
   unsigned int serverlen;
   struct sockaddr_in serveraddr;
   struct hostent *server;
   const char *hostname;
   char buf[BUFSIZE];

   std::string host = args[1];

   hostname = host.c_str();
   portno = atoi(args[2].c_str());

   /* socket: create the socket */
   sockfd = socket(AF_INET, SOCK_DGRAM, 0);
   if (sockfd < 0) 
      error("ERROR opening socket");

   /* gethostbyname: get the server's DNS entry */
   server = gethostbyname(hostname);
   if (server == NULL) {
      fprintf(stderr,"ERROR, no such host as %s\n", hostname);
      exit(0);
   }

   /* build the server's Internet address */
   bzero((char *) &serveraddr, sizeof(serveraddr));
   serveraddr.sin_family = AF_INET;
   bcopy((char *)server->h_addr, 
         (char *)&serveraddr.sin_addr.s_addr, server->h_length);
   serveraddr.sin_port = htons(portno);

   strcpy(buf, message.c_str());

   struct sockaddr* const addr = reinterpret_cast<struct sockaddr*>(&serveraddr);

   /* send the message to the server */
   serverlen = sizeof(serveraddr);
   n = sendto(sockfd, buf, strlen(buf), 0, addr, serverlen);
   if (n < 0) 
      error("ERROR in sendto");

   char inbuf[BUFSIZE];

   /* print the server's reply */
   n = recvfrom(sockfd, inbuf, BUFSIZE, 0, addr, &serverlen);
   if (n < 0) 
      error("ERROR in recvfrom");

   *(inbuf + n) = 0;
   printf("%s\n", inbuf);

   return 0;
}

