#include <iostream>
#include<json.hpp>
#include <memory>
#include <functional>

#include "TcpServer.h"
#include "Receiver.h"
#include "ConcreteCommand.h"
#include "Invoker.h"


using json = nlohmann::json;


#pragma comment(lib, "ws2_32.lib")


TcpServer::TcpServer(int port) : port(port), serverSocket(INVALID_SOCKET), running(false) {
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);
}

TcpServer::~TcpServer() {
    stop();
    WSACleanup();
}

bool TcpServer::start() {
    sockaddr_in serverAddress = {0};

    serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (serverSocket == INVALID_SOCKET) {
        std::cerr << "Socket creation failed." << std::endl;
        return false;
    }

    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(port);

    if (bind(serverSocket, (sockaddr*)&serverAddress, sizeof(serverAddress)) == SOCKET_ERROR) {
        std::cerr << "Bind failed." << std::endl;
        return false;
    }

    if (listen(serverSocket, SOMAXCONN) == SOCKET_ERROR) {
        std::cerr << "Listen failed." << std::endl;
        return false;
    }

    running = true;
    std::cout << "Server is listening on port " << port << "..." << std::endl;

    while (running) {
        SOCKET clientSocket = accept(serverSocket, NULL, NULL);
        if (clientSocket != INVALID_SOCKET) {
            handleClient(clientSocket);
        }
    }

    return true;
}

void TcpServer::stop() {
    running = false;
    if (serverSocket != INVALID_SOCKET) {
        closesocket(serverSocket);
    }
}

void TcpServer::handleClient(SOCKET clientSocket) {
    char buffer[1024];
    int result = recv(clientSocket, buffer, sizeof(buffer), 0);
    try{
        if (result > 0) {
        std::string receivedMessage(buffer, result);
        std::cout << "Received message: " << receivedMessage << std::endl;

        json j = json::parse(receivedMessage);
        std::string content = j["content"];
        std::cout << "Content: " << content << std::endl;

        json response;
        response["type"] = "response";
        response["content"] = "Message received!";
        response["timestamp"] = "2024-08-05T10:00:00Z";
        std::string responseMessage = response.dump();

        send(clientSocket, responseMessage.c_str(), responseMessage.size(), 0);
        }
    }
    catch(const json::exception& e){
        const char* m = e.what();
        std::cout << "message: " << m << '\n' << "exception id: " << e.id << std::endl;  
        send(clientSocket, m, strlen(m), 0);
    }
    
    closesocket(clientSocket);
}