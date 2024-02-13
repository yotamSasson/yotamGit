#include <stdio.h> /*print*/
#include <sys/socket.h> /*socket*/
#include <netinet/in.h> /*INADDR_ANY*/
#include <string.h>
#include <unistd.h> /*close*/

#define PORT (8080)
#define ADDRESS (NULL)

#include "tcp_udp.h"

int main (void)
{
    int pingfd1 = 0;
    
    pingfd1 = TCPClient(PORT, ADDRESS, SO_REUSEADDR);

    for (int i = 0; i < 5; ++i)
    {
        send(pingfd1, "Ping", strlen("Ping"), 0);

        char buffer[225] = {0};
        int msg_len = recv(pingfd1, buffer, sizeof(buffer), 0);
        if (msg_len < 0)
        {
            perror("recv");
            close(pingfd1);
            return FAIL;
        }

        buffer[msg_len] = '\0';
        printf("%s\n", buffer);

        sleep(1);
    }

    close(pingfd1);
    return 0;
}
