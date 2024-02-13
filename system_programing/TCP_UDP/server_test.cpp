#include <iostream>
#include <unistd.h> //STDOUT_FILENO

#include "server.hpp"
#include "tcp_udp.h"

using namespace dev;
int main (void)
{
    ServerSelector *s = new ServerSelector;

    int port = 8080;
    char protocol[] = "TCP";
    int tcpfd = Server(protocol, port, NULL);
    s->Register(tcpfd, TCPAccept);

    int port2 = 1234;
    char protocol2[] = "UDP";
    int tcpfd2 = Server(protocol2, port2, NULL);
    s->Register(tcpfd2, UDPPong);

    int tcpfd3 = STDIN_FILENO;
    s->Register(tcpfd3, StdinPong);

    s->Run();
    delete s;

    return 0;
}
