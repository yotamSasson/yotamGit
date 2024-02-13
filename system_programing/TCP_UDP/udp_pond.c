#include <stdio.h> /*print*/
#include <sys/socket.h> /*socket*/
#include <netinet/in.h> /*INADDR_ANY*/
#include <string.h>
#include <unistd.h> /*close*/

#include "tcp_udp.h"

#define PORT (8080)
#define ADDRESS (NULL)

int main (void)
{
    char buffer[225] = {0};
    int sockfd;
    int i = 0;
    struct sockaddr_in ping_addr;
    socklen_t addr_len = sizeof(ping_addr);

    sockfd = SocketInitAndBind(PORT, ADDRESS, SOCK_DGRAM, SO_REUSEADDR);

    for (i = 0; i < 10; ++i)
    {
        int msg_len = recvfrom(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr *)&ping_addr, &addr_len);
        buffer[msg_len] = '\0';
        printf("%s\n", buffer);

        sendto(sockfd, "Pong", strlen("Pong"), 0, (struct sockaddr *)&ping_addr, addr_len);
        sleep(1);
    }

    close(sockfd);
    return 0;
}
