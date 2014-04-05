
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "UDP.h"
#include <strings.h>
#include <cstring>


void UDP::send(const char* sendChar, const char * IP)
{
   int sockfd,n;
   char* fgetChar = const_cast<char*> (sendChar);
   struct sockaddr_in servaddr,cliaddr;
   char sendline[1000];
   char recvline[1000];

   sockfd=socket(AF_INET,SOCK_DGRAM,0);

   bzero(&servaddr,sizeof(servaddr));
   servaddr.sin_family = AF_INET;
   servaddr.sin_addr.s_addr=inet_addr(IP);
   servaddr.sin_port=htons(32000);

   while (fgets(fgetChar, 10000,stdin) != NULL)
   {
      sendto(sockfd,sendChar,std::strlen(sendChar),0,
             (struct sockaddr *)&servaddr,sizeof(servaddr));
      n=recvfrom(sockfd,recvline,10000,0,NULL,NULL);
      recvline[n]=0;
      fputs(recvline,stdout);
   }
}
