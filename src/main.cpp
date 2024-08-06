#include <winsock2.h>
#include <iostream>

#include "TcpServer.h"


#define PORT 65432
#define BUFFER_SIZE 1024

int main() {
    TcpServer *tcpServer = new TcpServer(PORT);

    tcpServer->start();

    tcpServer->stop();


    delete tcpServer;
    return 0;
}
