#ifndef LOGIN_H
#define LOGIN_H

#include"Receiver.h"
#include <iostream>

class Login : public Receiver{
    public:
        int action(std::string message);
    private:

};

int Login::action(std::string message){
    std::cout<<"login"<<std::endl;
    return 0;
}


#endif