#ifndef RECEIVER_H
#define RECEIVER_H
#include <string>
class Receiver {
public:
    virtual int action(std::string message) = 0;
};

#endif // RECEIVER_H