#ifndef MY_PROJECT_TCP__
#define MY_PROJECT_TCP__

typedef enum status
{
	SUCCESS = 0,
	FAIL = -1,
	STDIN_CLOSE = -2,
    CLIENT_CLOSE = -3
}status_t;

/*
    return the server fd
*/
int TCPInitServer(int port, char *address, int backlog, int optname);
/*
    return the client fd
*/
int TCPClient(int port , char *address, int optname);
/*
    return the new socket fd after accepting the connection 
*/
int TCPServerAccept(int serverfd);
/*
    return the socket fd
*/
int SocketInitNonBlocking(int port, char *address, struct sockaddr_in *server_addr, int type, int optname);

int SocketInitBlocking(int port, char *address, struct sockaddr_in *server_addr, int type, int optname);
/*
    return the socket fd to an address 
*/
int SocketInitAndBind(int port, char *address, int type, int optname);


int Server(char *protocol, int port, char *address);


#endif

 