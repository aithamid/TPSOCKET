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

struct Server {
	int server_socket;
    const char * addr = "127.0.0.1";
    int port;
    pollfd * fds;
};
	
extern const struct ServerClass {
	struct Server (*handle_create)(
        const char * addr_ip,
        const int port_num);
} Server;


	
static struct Server handle_create(const char * addr_ip, const int port_num)
{
	return (struct Server){
		.addr=strdup(addr_ip),
        .port=port_num
	};
}
	
const struct ServerClass Server={.handle_create=&handle_create};


// bool server::handle_create(const char * addr_ip, char * port_num)
// {
//     /* Create socket */
//     server_socket = socket(AF_INET, SOCK_STREAM, 0);

//     short port = atoi(port_num);
//     struct sockaddr_in server_addr;
//     memset(&server_addr, '\0', sizeof(server_addr));
//     server_addr.sin_family = AF_INET;
//     server_addr.sin_port = htons(port);
//     inet_aton(addr_ip, &(server_addr.sin_addr));

//     // Bind to server address
//     printf("Binding...\n");
//     if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1)
//     {
//         perror("Error while binding");
//         return false;
//     }

//     // Listen on server socket
//     printf("Listening...\n");
//     if (listen(server_socket, MAXCLI) == -1)
//     {
//         perror("Error while listening");
//         return false;
//     }

//     return true;
// }


