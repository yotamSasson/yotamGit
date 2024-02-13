#include <stdio.h> /*print*/
#include <sys/socket.h> /*socket*/
#include <netinet/in.h> /*INADDR_ANY*/
#include <string.h>
#include <unistd.h> /*close*/

#include "tcp_udp.h"

#define PORT (1234)
#define ADDRESS (NULL)

int main (void)
{
    char buffer[10] = {0};
    int sockfd;
    struct sockaddr_in pong_addr;
    int i = 0;
    int pingfd1 = 0;
    FILE *file = fopen("UDPlogfile.txt", "w+");
    if (file == NULL)
    {
        perror("Error opening the file");
        return FAIL;
    }

    sockfd = SocketInitBlocking(PORT, ADDRESS, &pong_addr, SOCK_DGRAM, SO_REUSEADDR);

    for (i = 0; i < 10; ++i)
    {
        sendto(sockfd, "Ping", strlen("Ping"), 0, (struct sockaddr *)&pong_addr, sizeof(struct sockaddr));
        fprintf(file, "UDP client ping\n");

        int msg_len = recvfrom(sockfd, buffer, sizeof(buffer), 0, NULL, NULL);
        buffer[msg_len] = '\0';
        printf("%s\n", buffer);
        
        sleep(1);
    }

    fprintf(file, "UDP client close\n");

    close(sockfd);
    fclose(file);
    return 0;
}
