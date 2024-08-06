#include "ConcreteCommand.h"
#include "Receiver.h"

ConcreteCommand::ConcreteCommand(Receiver& receiver, std::function<void()> action)
    : receiver(receiver), action(action) {}

void ConcreteCommand::execute() {
    action();
}