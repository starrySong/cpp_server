#ifndef MESSAGECONFIG_H
#define MeSSAGECONFIG_H


#include"utils/Invoker.h"
#include<utils/json.hpp>

//내가 만든 헤더 추가 ....
#include"custom/Login.h"
#include"custom/OpenServer.h"

using json = nlohmann::json;

class MessageConfig {
    public:
        MessageConfig();
        ~MessageConfig();
        std::string run(std::string message);
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
MessageConfig::~MessageConfig(){
    
    delete login;
    delete openServer;
    delete invoker;
}

void MessageConfig::setup(){
    //custom message add...
    //메시지 등록
    invoker->setCommand("login", std::make_unique<ConcreteCommand>(login));
    invoker->setCommand("open_server", std::make_unique<ConcreteCommand>(openServer));
}

//메시지 호출
std::string MessageConfig::run(std::string message){
    json js = json::parse(message);
    std::string commandId = js["header"];
    std::string data = js["body"];

    int reuslt = invoker->pressButton(commandId, data);

    return "Success";
}

#endif