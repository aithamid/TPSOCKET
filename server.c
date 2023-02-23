// Server side C/C++ program to demonstrate Socket
// programming
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <time.h>
#include "common.h"

#define PORT 8080

void server_handle(int * server_fd, int * new_socket, int port)
{
	
	struct sockaddr_in address;
	int opt = 1;
	int addrlen = sizeof(address);

	// Creating socket file descriptor
	if ((*(server_fd) = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		perror("socket failed");
		exit(EXIT_FAILURE);
	}

	// Forcefully attaching socket to the port 8080
	if (setsockopt(*(server_fd), SOL_SOCKET,
				SO_REUSEADDR | SO_REUSEPORT, &opt,
				sizeof(opt))) {
		perror("setsockopt");
		exit(EXIT_FAILURE);
	}
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(port);

	// Forcefully attaching socket to the port 8080
	if (bind(*(server_fd), (struct sockaddr*)&address,
			sizeof(address))
		< 0) {
		perror("bind failed");
		exit(EXIT_FAILURE);
	}
	if (listen(*(server_fd), 3) < 0) {
		perror("listen");
		exit(EXIT_FAILURE);
	}
	if ((*(new_socket)
		= accept(*(server_fd), (struct sockaddr*)&address,
				(socklen_t*)&addrlen))
		< 0) {
		perror("accept");
		exit(EXIT_FAILURE);
	}
}

void echo_server(int sockfd) {
	char buff[MSG_LEN];
	while (1) {
		// Cleaning memory
		memset(buff, 0, MSG_LEN);
		// Receiving message
		if (recv(sockfd, buff, MSG_LEN, 0) <= 0) {
			break;
		}
		printf("Received: %s", buff);
        if( strcmp(buff, "/quit") == 0)
		{
			return;
		}
		// Sending message (ECHO)
		if (send(sockfd, buff, strlen(buff), 0) <= 0) {
			break;
		}
		printf("Message sent!\n");
	}
}

int check_args(int argc, char const* argv[])
{
	if(argc>1)
		return atoi(argv[1]);
	return 8080;
}

int main(int argc, char const* argv[])
{   
    
	int server_fd, new_socket;
	int port = check_args(argc, argv);
	printf("HAAHAH%d", port);
    server_handle(&server_fd, &new_socket, port);
    echo_server(new_socket);

	close(new_socket);
    
	// closing the listening socket
	shutdown(server_fd, SHUT_RDWR);

	return 0;
}
