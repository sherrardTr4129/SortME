//Author: Trevor Sherrard

#include <stdio.h>      
#include <stdlib.h>
#include <string.h>    
#include <unistd.h>     
#include <fcntl.h>      
#include <errno.h>      
#include <termios.h>    


#include "RobotServer.h"

using namespace std;
void RobotServer::send(unsigned char NumToSend)
{
  int USB = open( "/dev/ttyUSB0", O_RDWR| O_NOCTTY );
  struct termios tty;
  memset (&tty, 0, sizeof tty);
  //Set Baud Rate 
  cfsetospeed (&tty, B9600);
  cfsetispeed (&tty, B9600);


  tty.c_cflag     &=  ~PARENB;        // Make 8n1
  tty.c_cflag     &=  ~CSTOPB;
  tty.c_cflag     &=  ~CSIZE;
  tty.c_cflag     |=  CS8;
  tty.c_cflag     &=  ~CRTSCTS;       // no flow control
  tty.c_lflag     =   0;          // no signaling chars, no echo, no canonical processing
  tty.c_oflag     =   0;                  // no remapping, no delays 
  tty.c_cc[VMIN]      =   0;                  // read doesn't block
  tty.c_cc[VTIME]     =   5;                  // 0.5 seconds read timeout

  tty.c_cflag     |=  CREAD | CLOCAL;     // turn on READ & ignore ctrl lin  es
  tty.c_iflag     &=  ~(IXON | IXOFF | IXANY);// turn off s/w flow ctrl
  tty.c_lflag     &=  ~(ICANON | ECHO | ECHOE | ISIG); // make raw
  tty.c_oflag     &=  ~OPOST;              // make raw

  //Flush Port, then applies attributes 
  tcflush( USB, TCIFLUSH );

  //unsigned char cmd[] = NumToSend;
  int n_written = 0;
  write( USB, &NumToSend, 1 );
  close(USB);

}
