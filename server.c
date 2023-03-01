// Server side C/C++ program to demonstrate Socket
// programming
#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <poll.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>
#include <ctype.h>
#include <stdbool.h>
#include "common.h"
#include "server.h"

bool arg_check(int argc)
{
	if(argc!=2)
		return false;
	return true;
}	


int main(int argc, char const* argv[])
{   
	if(!(arg_check))
	{
		printf("failure");
	}

	return 0;
}
