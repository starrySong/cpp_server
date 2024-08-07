#include <iostream>

#include "ServerSocket.h"

#define PORT 65432

int main() {
   SocketServer server(PORT);

    if (server.start()) {
        std::cout << "Server is running. Press Enter to stop..." << std::endl;
        std::cin.get(); // Wait for user input to stop the server
        server.stop();
    } else {
        std::cerr << "Server failed to start" << std::endl;
    }

    return 0;
}
