#include "ConcreteCommand.h"
#include "Receiver.h"

ConcreteCommand::ConcreteCommand(Receiver* receiver)
    : receiver(receiver) {}

void ConcreteCommand::execute() {
    receiver->action();
}