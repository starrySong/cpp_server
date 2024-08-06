#ifndef INVOKER_H
#define INVOKER_H

#include "Command.h"
#include <unordered_map>
#include <memory>
#include <string>

class Invoker {
public:
    void setCommand(const std::string& message, std::unique_ptr<Command> command);
    void pressButton(const std::string& message);

private:
    std::unordered_map<std::string, std::unique_ptr<Command>> commands;
};

#endif // INVOKER_H
