//author: Trevor Sherrard
//project: SortME

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>

class RobotSerial
{
     public: 
          void send(char NumToSort); 
};
