#ifndef CONCRETECOMMAND_H
#define CONCRETECOMMAND_H

#include "Command.h"
#include "Receiver.h"
#include <functional>

class ConcreteCommand : public Command {
    public:
        ConcreteCommand(Receiver *receiver);
       

        void execute();

    private:
        Receiver* receiver;

};


#endif