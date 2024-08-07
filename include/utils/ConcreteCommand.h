#ifndef CONCRETECOMMAND_H
#define CONCRETECOMMAND_H

#include "Command.h"
#include "Receiver.h"
#include <functional>

class ConcreteCommand : public Command {
    public:
        ConcreteCommand(Receiver *receiver);
       

        int execute(std::string message);

    private:
        Receiver* receiver;

};

ConcreteCommand::ConcreteCommand(Receiver* receiver)
    : receiver(receiver) {}

int ConcreteCommand::execute(std::string message) {
    return receiver->action(message);
}

#endif