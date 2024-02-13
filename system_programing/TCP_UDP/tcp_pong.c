#include <stdio.h> /*print*/
#include <sys/socket.h> /*socket*/
#include <netinet/in.h> /*INADDR_ANY*/
#include <string.h>
#include <unistd.h> /*close*/

#include "tcp_udp.h"

#define PORT (8083)
#define ADDRESS (NULL)

int main (void)
{
    int pingfd = 0;
    int pongfd = 0;
    int backlog = 1;
    int pingpong_num = 10;
    char protocol[] = "TCP";

    pongfd = Server(protocol, PORT, ADDRESS);
    pingfd = TCPServerAccept(pongfd);

    char buffer[225] = {0};
    int msg_len = 0;

    while ((msg_len = recv(pingfd, buffer, sizeof(buffer), 0)) > 0)
    {
        if (msg_len < 0)
        {
            perror("recv");
            close(pingfd);
            return 1;
        }
        buffer[msg_len] = '\0';
        printf("%s\n", buffer);
        
        send(pingfd, "Pong", strlen("Pong"), 0);

        sleep(1);
    }

    close(pingfd);


    return 0;
}
