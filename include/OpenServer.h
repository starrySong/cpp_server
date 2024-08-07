#ifndef OPENSERVER_H
#define OPENSERVER_H

#include"Receiver.h"
#include<iostream>

class OpenServer : public Receiver{
    public:
        void action(){ std::cout << "456"<<std::endl;}
    private:

};

#endif