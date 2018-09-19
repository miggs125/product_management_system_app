#include <iostream>
#include <cstring>
#include "ErrorState.h"


namespace AMA{

    ErrorState::ErrorState(const char* errorMessage){
        if(errorMessage == nullptr || errorMessage[0] == '\0'){
            this->errorMessage = nullptr;
        } else {
            this->errorMessage = new char[strlen(errorMessage)+1];
            strncpy(this->errorMessage,errorMessage, strlen(errorMessage));
            this->errorMessage[strlen(errorMessage)] = '\0';
        }
    }

    ErrorState::~ErrorState(){
        delete [] errorMessage;
        errorMessage = nullptr;
    }

    void ErrorState::clear(){
        delete [] errorMessage;
        errorMessage = nullptr;
    }

    bool ErrorState::isClear() const{
        bool clear = true;
        if(errorMessage)
            clear = false;
        return clear;
    }

    void ErrorState::message(const char* str){
        clear();
        errorMessage = new char[strlen(str)+1];
        strcpy(errorMessage,str);
    }

    const char* ErrorState::message()const{
        return errorMessage;
    }

    std::ostream& operator<<(std::ostream& os, ErrorState& error){
        if(!error.isClear())
            os << error.message();
        return os;        
    }
}