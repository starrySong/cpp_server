#ifndef INVOKER_H
#define INVOKER_H

#include "Command.h"
#include"ConcreteCommand.h"
#include"Receiver.h"

#include <unordered_map>
#include <memory>
#include <string>

class Invoker {
public:
    void setCommand(const std::string& message, std::unique_ptr<Command> command);
    int pressButton(const std::string& message, std::string data);

private:
    std::unordered_map<std::string, std::unique_ptr<Command>> commands;
};

void Invoker::setCommand(const std::string& message, std::unique_ptr<Command> command) {
    commands[message] = std::move(command);
}

int Invoker::pressButton(const std::string& message, std::string data) {
    if (commands.find(message) != commands.end()) {
        commands[message]->execute(data);
        return 0;
    } else {
        std::cout << "No command for message: " << message << std::endl;
        return -1;
    }
}

#endif // INVOKER_H
