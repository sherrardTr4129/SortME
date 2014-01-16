//Author: Trevor Sherrard

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>

class RobotServer
{
     public: 
          void send(unsigned char NumToSort);
};
