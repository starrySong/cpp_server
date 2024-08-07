#ifndef SERVERSOCKET_H
#define SERVERSOCKET_H


#include <iostream>
#include <winsock2.h>
#include <thread>
#include <vector>
#include <string>

#include<utils/json.hpp>
#include"config/MessageConfig.h"
#include"dto/JsonSet.h"

#pragma comment(lib, "ws2_32.lib")

using json = nlohmann::json;

class SocketServer {
public:
    SocketServer(int port) : port(port), serverSocket(INVALID_SOCKET) {}
    ~SocketServer() { cleanup(); }

    bool start();
    void stop();
    
private:
    void handleClient(SOCKET clientSocket);
    void cleanup();

    int port;
    SOCKET serverSocket;
    std::vector<std::thread> threads;
    MessageConfig messageInfo;
};

bool SocketServer::start() {
    WSADATA wsaData;
    sockaddr_in serverAddr;

    // Initialize Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "Failed to initialize Winsock" << std::endl;
        return false;
    }

    // Create a socket
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == INVALID_SOCKET) {
        std::cerr << "Failed to create socket" << std::endl;
        WSACleanup();
        return false;
    }

    // Set up the server address
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(port);

    // Bind the socket
    if (bind(serverSocket, (sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        std::cerr << "Bind failed" << std::endl;
        cleanup();
        return false;
    }

    // Listen for incoming connections
    if (listen(serverSocket, SOMAXCONN) == SOCKET_ERROR) {
        std::cerr << "Listen failed" << std::endl;
        cleanup();
        return false;
    }

    std::cout << "Server listening on port " << port << std::endl;

    // Accept and handle client connections
    sockaddr_in clientAddr;
    int clientAddrSize = sizeof(clientAddr);
    SOCKET clientSocket;

    while (true) {
        clientSocket = accept(serverSocket, (sockaddr*)&clientAddr, &clientAddrSize);
        if (clientSocket == INVALID_SOCKET) {
            std::cerr << "Accept failed" << std::endl;
            continue;
        }

        std::cout << "Client connected" << std::endl;

        // Create a new thread to handle the client
        threads.emplace_back(std::thread(&SocketServer::handleClient, this, clientSocket));
    }

    return true;
}

void SocketServer::stop() {
    closesocket(serverSocket);
    WSACleanup();
}

void SocketServer::handleClient(SOCKET clientSocket) {
    char buffer[1024];
    int bytesRead;

    while ((bytesRead = recv(clientSocket, buffer, sizeof(buffer) - 1, 0)) > 0) {
        buffer[bytesRead] = '\0'; // Null-terminate the string
        std::cout << "Received: " << buffer << std::endl;

        //char*[] -> string 변환
        std::string receivedData(buffer);

        //json parse
        json jsonData = json::parse(receivedData);
        std::string header = jsonData["header"];
        JsonSet jss;

        std::string flag = messageInfo.run(receivedData);

        if (flag.compare("Success") == 0){
            jss.setHeader(header);
            jss.setBody("Success");

        }
        else{
            jss.setHeader(header);
            jss.setBody("Fail");
        }

        json response = jss;
        std::string responseStr = response.dump();

        send(clientSocket, responseStr.c_str(), responseStr.size(), 0);
    }

    std::cout << "Client disconnected" << std::endl;
    closesocket(clientSocket);
}

void SocketServer::cleanup() {
    for (auto& th : threads) {
        if (th.joinable()) {
            th.join();
        }
    }

    if (serverSocket != INVALID_SOCKET) {
        closesocket(serverSocket);
    }
    WSACleanup();
}



#endif