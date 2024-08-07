#ifndef MESSAGECONFIG_H
#define MeSSAGECONFIG_H

#include"Login.h"
#include"OpenServer.h"
#include "Invoker.h"

class MessageConfig {
    public:
        MessageConfig();
        void run(std::string message);
    private:
        Login *login;
        OpenServer *openServer;
        Invoker *invoker;

        void setup();

};
//메시지 초기화
MessageConfig::MessageConfig(){
    invoker = new Invoker();

    //내가 선언한 메시지 초기화
    login = new Login();
    openServer = new OpenServer();

    setup();
}

void MessageConfig::setup(){
    //custom message add...
    invoker->setCommand("login",std::make_unique<ConcreteCommand>(login));
    invoker->setCommand("open_server",std::make_unique<ConcreteCommand>(openServer));
}
void MessageConfig::run(std::string message){
    invoker->pressButton(message);
}

#endif