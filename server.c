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
#include <poll.h>

#include "server.h"
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

#define BUFF_MAX 8192
#define MAXCLI 20

#define STRUCT_MSG 0
#define CHAR_MSG 1

struct myServer {
	const int server_socket;
    const char * ip;
    const int port;
	struct pollfd fds[MAXCLI+1];
};
	
extern struct ServerClass {
	struct myServer (*handle_create)(
        const char * addr_ip,
        const int port
		);
} myServer;


	
struct myServer handle_create(const char * addr_ip, const int port_num)
{
    /* Create socket */
    int server_sock = 0;
    server_sock = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in server_addr;
    memset(&server_addr, '\0', sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port_num);
    inet_aton(addr_ip, &(server_addr.sin_addr));

    // Bind to server address
    printf("Binding...\n");
    if (bind(server_sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1)
    {
        perror("Error while binding");
        exit(EXIT_FAILURE);
    }

    // Listen on server socket
    printf("Listening...\n");
    if (listen(server_sock, MAXCLI) == -1)
    {
        perror("Error while listening");
        exit(EXIT_FAILURE);
    }
	return (struct myServer) {
		
        .server_socket=server_sock,
		.ip=strdup(addr_ip),
        .port=port_num
	};
}

int send_buf(int cfd, char *buf, int size)
{
    int ret = 0;
    int len = 0;
    int tmp = 0;

    if (size > 0)
        len = size;
    else
        len = strlen(buf);

    while (tmp < len)
    {
        if (-1 == (ret = send(cfd, (void *)buf + tmp, strlen(buf) - tmp, 0)))
        {
            perror("Error while sending");
            return 0;
        }
        tmp += ret;
    }
    return 1;
}
	
struct ServerClass myServer={.handle_create=&handle_create};
bool arg_check(int argc)
{
	if(argc!=2)
		return false;
	else 
		return true;
}	

int handle_data(struct myServer * s)
{
	int nfds = MAXCLI + 1;
    
    memset(s->fds, 0, nfds * sizeof(struct pollfd));
    s->fds[0].fd = s->server_socket;
    s->fds[0].events = POLLIN;
    // clients_hist ch = init();
    // channel_list cl = init_cl();
    while (1)
    {
        int enabled = 0;
        enabled = poll(s->fds, nfds, -1);

        if (enabled > 0)
        {
            for (int i = 0; i < nfds; i++)
            {
                if (i == 0 && s->fds[i].revents == POLLIN)
                {
                    // Accept incoming connection
                    struct sockaddr_in client_addr;
                    socklen_t size_addr = sizeof(struct sockaddr_in);
                    printf("start accepting...\n");
                    int client_fd = -1;
                    if (-1 == (client_fd = accept(s->server_socket, (struct sockaddr *)&client_addr, &size_addr)))
                    {
                        perror("Error while accepting");
                        return 0;
                    }
                    int j = 1;
                    while (s->fds[i + j].fd != 0)
                        j = j + 1;
                    s->fds[i + j].fd = client_fd;
                    s->fds[i + j].events = POLLIN | POLLHUP;

                    // Add elements to clients history struct
                    //add(&ch, client_fd, client_addr.sin_port, client_addr.sin_addr);

                    // Define the first welcome message
                    
                }
                else if (i > 0 && s->fds[i].revents == POLLHUP)
                {
                    // In case there is a connection loss on WAN (unusuable on LAN for Linux 2.6 and above)
                    //rem(&ch, s->fds[i].fd);

                    close(s->fds[i].fd);
                    printf("Socket: %d is closed\n", s->fds[i].fd);
                    memset((s->fds + i), 0, sizeof(struct pollfd));
                    printf("Connection lost with client!\n");
                }
                else if (i > 0 && s->fds[i].revents == POLLIN)
                {
                    // Read data from client
                	char buf[BUFF_MAX] = {0};

                    
                    memset(buf, 0, BUFF_MAX);

                    // Read message length
                    int ret = 0;
                    {
                        if (-1 == (ret = recv(s->fds[i].fd, buf, BUFF_MAX, 0)))
                        {
                            perror("Error while receiving");
                            return 0;
                        }
						// if (-1 == (ret = send(s->fds[i].fd, buf,  BUFF_MAX, 0)));
                        // {
                        //     perror("Error while sending");
                        //     return 0;
                        // }
                        send(s->fds[i].fd, buf, strlen(buf), 0);
						
                    }
				}
			}
		}
	}
}

int main(int argc, char const* argv[])
{   
	const char *server_addr = "127.0.0.1";
	if(!arg_check(argc))
	{
		printf("failure");
		exit(EXIT_FAILURE);
	}
	struct myServer s = myServer.handle_create(server_addr,8080);
	printf("%d",s.server_socket);
	while (1)
    {
        int ret = 0;
        if (0 == (ret = handle_data(&s)))
            exit(EXIT_FAILURE);
    }

	return 0;
}
