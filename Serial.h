#include <stdio.h>    // Standard input/output definitions 
#include <stdlib.h> 
#include <string.h>   // String function definitions 
#include <unistd.h>   // for usleep()
#include <getopt.h>

#include "arduino-serial-lib.h"


class Serial
{
     public:	
	int sendChar(const char* c, int fd );
};
