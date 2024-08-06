#ifndef TCPSERVER_H
#define TCPSERVER_H

#include<winsock2.h>
#include<string>



class TcpServer{
    public:
        TcpServer(int port);
        ~TcpServer();

        bool start();
        void stop();

    private:
        SOCKET serverSocket;
        int port;
        bool running;

        void handleClient(SOCKET clientSocket);


};



#endif //TCPSERVER_H