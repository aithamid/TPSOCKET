// Client side C/C++ program to demonstrate Socket
// programming
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <time.h>
#define PORT 8080
#define BUFF_MAX 8192

void echo_client(int client_fd){
	char buffer[BUFF_MAX] = { 0 };
	while(1)
	{	
		char message[BUFF_MAX] ="coucou";
		printf("Sent : \t\t%s\n",message);
		//scanf("%s", message);
		send(client_fd, message, strlen(message), 0);

		read(client_fd, buffer, BUFF_MAX);
		if(buffer[0] != '\0')    
        	printf("Received : \t%s\n", buffer);

		memset(buffer, 0, BUFF_MAX);
		sleep(1);
	}
}

const char * get_ip(int argc, char const* argv[])
{
	const char * ip = argv[1];
	return ip;
}

int get_port(int argc, char const* argv[])
{
	int port = atoi(argv[2]);
	return port;
}

int client_connect(int * client_fd, int argc, char const* argv[])
{

	int status; 
	struct sockaddr_in serv_addr;
	if ((*(client_fd) = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		printf("\n Socket creation error \n");
		return -1;
	}

	// IP : 
	const char * ip = get_ip(argc, argv);
	int port = get_port(argc, argv);


	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(port);

	// Convert IPv4 and IPv6 addresses from text to binary
	// form
	if (inet_pton(AF_INET, ip, &serv_addr.sin_addr)
		<= 0) {
		printf(
			"\nInvalid address/ Address not supported \n");
		return -1;
	}

	if ((status
		= connect(*(client_fd), (struct sockaddr*)&serv_addr,
				sizeof(serv_addr)))
		< 0) {
		printf("\nConnection Failed \n");
		return -1;
	}

	return 0;
}




int main(int argc, char const* argv[])
{

	int client_fd;
	if(client_connect(&client_fd,argc, argv) == 0){
		
		echo_client(client_fd);
		
	}

	// closing the connected socket
	close(client_fd);
	return 0;
}
