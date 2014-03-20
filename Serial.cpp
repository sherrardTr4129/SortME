// Originally created 5 December 2006
//2006-2013, Tod E. Kurt, http://todbot.com/blog/

#include <stdio.h>    // Standard input/output definitions 
#include <stdlib.h> 
#include <string.h>   // String function definitions 
#include <unistd.h>   // for usleep()
#include <getopt.h>

#include "arduino-serial-lib.h"
#include "Serial.h"

int Serial::sendChar(const char* c)
{
       const int buf_max = 256;

       int fd = -1;
       char serialport[buf_max];
       int baudrate = 9600;  // default
       char quiet=0;
       char eolchar = '\n';
       int timeout = 5000;
       char buf[buf_max];
       int rc,n;
       strcpy(buf, c);
       baudrate = strtol("9600",NULL,10);
       fd = serialport_init("/dev/ttyACM0", baudrate);
       if( fd==-1 ) return -1;
       serialport_flush(fd);
       rc = serialport_write(fd, buf);
       return 0;
}    

