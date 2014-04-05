#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string>

class UDP
{
    public:
	void send(const char* sendChar, const char* IP);
};
