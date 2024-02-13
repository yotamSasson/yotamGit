#include <iostream> 
#include <sys/select.h> //select
#include <cstring> //strlen, strcmp
#include <sys/socket.h> //socket
#include <unistd.h> //close
#include <arpa/inet.h> //addr
#include <fstream> //ofstream

#include "server.hpp"
#include "tcp_udp.h"

namespace dev
{

/************************ Constructor ************************/
ServerSelector::ServerSelector() : maxfd(0)
{
    FD_ZERO(&readfds);
}

/************************ Distructor ************************/

ServerSelector::~ServerSelector() 
{
    FD_ZERO(&readfds);
    for (std::map<int, int (*)(int)>::iterator it = fdContainer.begin(); it != fdContainer.end(); ++it)
    {
       close(it->first);
    }
}

/************************ Member Function ************************/
void ServerSelector::Register(int fd, int (*handler)(int))
{
    fdContainer[fd] = handler;
    FD_SET(fd, &readfds);
    maxfd = std::max(maxfd, fd);
}

int ServerSelector::Run()
{
    struct timeval timeout;
    int exit_flag = false;
    std::map<int, int (*)(int)>::iterator fd;
    
    while (!exit_flag)
    {
        timeout.tv_sec = 7;
        timeout.tv_usec = 0;
        fd_set tmp_fds = readfds;

        int ready = select(maxfd + 1, &tmp_fds, NULL, NULL, &timeout);
        if (-1 == ready)
        {
            perror("select");
            return FAIL;
        }
        else if (0 == ready)
        {
            std::ofstream logfile("logfile.txt",std::ios_base::app); //open the file in append mode
            logfile << "Time out"<< std::endl;
        }
        else if (ready > 0)
        {
            for (fd = fdContainer.begin(); fd != fdContainer.end(); ++fd)
            {
                if(FD_ISSET(fd->first, &tmp_fds))
                {
                    int newfd = fdContainer[fd->first](fd->first);
                    if (fd->first != newfd && newfd > 0)
                    {
                        Register(newfd, TCPPong);
                    }
                    else if (STDIN_CLOSE == newfd)
                    {
                        exit_flag = true;
                    }
                    else if (0 > newfd)
                    {
                        FD_CLR(fd->first, &readfds);
                    }
                }
            }

        }
    }

    return SUCCESS;
}

/************************ Handlers ************************/
int TCPAccept(int sockfd)
{
    int newfd = TCPServerAccept(sockfd);
    return newfd;
}

int TCPPong(int sockfd)
{
    int msg_len = 0;
    char buffer[10] = {0};

    if ((msg_len = recv(sockfd, buffer, sizeof(buffer), 0)) > 0)
    {
        buffer[msg_len] = '\0';
        std::cout<< buffer <<std::endl;

        send(sockfd, "Pong", strlen("Pong"), 0);
    }
    if (0 >= msg_len)
    {
        close(sockfd);
        return FAIL;
    }
    return sockfd;
}

int UDPPong(int sockfd)
{
    int msg_len = 0;
    char buffer[10] = {0};
    struct sockaddr_in client_addr;
    socklen_t addr_len = sizeof(client_addr);

    if ((msg_len = recvfrom(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr *)&client_addr, &addr_len)) > 0)
    {
        buffer[msg_len] = '\0';
        std::cout<< buffer <<std::endl;

        sendto(sockfd, "Pong", strlen("Pong"), 0, (struct sockaddr *)&client_addr, addr_len);
    }

    if (0 >= msg_len)
    {
        close(sockfd);
        return FAIL;
    }
    return sockfd;
}

int StdinPong(int sockfd)
{
    int msg_len = 0;
    char buffer[10] = {0};

    if ((msg_len = read(sockfd, buffer, sizeof(buffer))) > 0)
    {
        buffer[msg_len] = '\0';
        if (strcmp(buffer, "quit\n") == 0)
        {
            close(sockfd);
            return STDIN_CLOSE;
        }

        sleep(1);

        write(sockfd, "Pong\n", strlen("Pong\n"));
    }

    if (0 >= msg_len)
    {
        perror("recv");
        close(sockfd);
        return FAIL;
    }
    return sockfd;
}

}
