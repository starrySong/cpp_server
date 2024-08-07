#ifndef COMMAND_H
#define COMMAND_H

class Command{
    public:
        virtual ~Command() = default;
        virtual int execute(std::string message) = 0;
};

#endif //end 