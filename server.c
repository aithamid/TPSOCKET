#include <netinet/in.h> //structure for storing address information
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h> //for socket APIs
#include <sys/types.h>

int main(int argc, char const* argv[])
{
    int port=9001;
    
    printf("%d", argc);
    if(argc>1)
    {
        printf("CHANGE");
        port = strtol(argv[1], NULL, 10);
    } 



	// create server socket similar to what was done in
	// client program
	int servSockD = socket(AF_INET, SOCK_STREAM, 0);

	// string store data to send to client
	char serMsg[255] = "Message du serveur c'est Adam";

	// define server address
	struct sockaddr_in servAddr;

	servAddr.sin_family = AF_INET;
	servAddr.sin_port = htons(9001);
	servAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

	// bind socket to the specified IP and port
	bind(servSockD, (struct sockaddr*)&servAddr,
		sizeof(servAddr));

	// listen for connections
	listen(servSockD, 1);

	// integer to hold client socket.
	int clientSocket = accept(servSockD, NULL, NULL);

	// send's messages to client socket
	send(clientSocket, serMsg, sizeof(serMsg), 0);

	return 0;
}
