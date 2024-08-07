#ifndef USER_H
#define USER_H

#include<string>
#include<iostream>
#include<utils/json.hpp>

class User{
    public:
        User(std::string userName, std::string userId, std::string password): userName(userName), userId(userId), password(password) {}

        void setUserName(std::string userName) {this->userName = userName;}
        void setUserId(std::string userId) {this->userId = userId;}
        void setPassword(std::string password) {this->password = password;}

        std::string getUserName() {return this->userName;}
        std::string getUserId() {return this->userId;}
        std::string getPassword() {return this->password;}

        NLOHMANN_DEFINE_TYPE_INTRUSIVE(User, userName, userId, password);
    private:
        std::string userName;
        std::string userId;
        std::string password;
};

#endif