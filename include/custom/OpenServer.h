#ifndef OPENSERVER_H
#define OPENSERVER_H

#include"Receiver.h"
#include <iostream>

class OpenServer : public Receiver{
    public:
        int action(std::string mesaage);
    private:

};
int OpenServer::action(std::string message){

    std::cout<<"openServer"<<std::endl;
    return 0;
}
#endif