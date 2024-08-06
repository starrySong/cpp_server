#include "Invoker.h"
#include <iostream>

void Invoker::setCommand(const std::string& message, std::unique_ptr<Command> command) {
    commands[message] = std::move(command);
}

void Invoker::pressButton(const std::string& message) {
    if (commands.find(message) != commands.end()) {
        commands[message]->execute();
    } else {
        std::cout << "No command for message: " << message << std::endl;
    }
}
