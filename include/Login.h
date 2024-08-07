#ifndef LOGIN_H
#define LOGIN_H

#include"Receiver.h"
#include<iostream>

class Login : public Receiver{
    public:
        void action(){ std::cout << "123"<<std::endl;}
    private:

};

#endif