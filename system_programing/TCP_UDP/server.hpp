#ifndef MY_PROJECT_SERVER__
#define MY_PROJECT_SERVER__

#include <sys/select.h> //fd_set
#include <map>

namespace dev
{
class ServerSelector
{
public:
    ServerSelector();
    void Register(int fd, int(*handler)(int)); 
    int Run();
    ~ServerSelector();

private:
    fd_set readfds;
    int maxfd;
    std::map<int, int (*)(int)>fdContainer;
}; 

int TCPAccept(int sockfd);

int TCPPong(int sockfd);

int UDPPong(int sockfd);

int StdinPong(int sockfd);
}
#endif
