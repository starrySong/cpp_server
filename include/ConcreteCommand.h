#ifndef CONCRETECOMMAND_H
#define CONCRETECOMMAND_H

#include "Command.h"
#include "Receiver.h"
#include <functional>

class ConcreteCommand : public Command {
    public:
        ConcreteCommand(Receiver& receiver, std::function<void()> action);

        void execute() override;

    private:
        Receiver& receiver;
        std::function<void()> action;

};


#endif