#ifndef JSONSET_H
#define JSONSET_H

#include<string>
#include<utils/json.hpp>

class JsonSet{
    public:
    JsonSet(): header(""), body(""){}
    JsonSet(std::string header, std::string body): header(header), body(body){}
    ~JsonSet() {};


    void setHeader(std::string header){ this->header = header; }
    void setBody(std::string body){ this->body = body; } 

    std::string getHeader(){return header;}
    std::string getBody(){return body;}
    
    NLOHMANN_DEFINE_TYPE_INTRUSIVE(JsonSet, header, body);

    private:
        std::string header;
        std::string body; 
    
};


#endif