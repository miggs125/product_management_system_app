#ifndef AMA_ERROR_STATE_H
#define AMA_ERROR_STATE_H

#include<iostream>

namespace AMA{

    class ErrorState {
        char* errorMessage;
        
        public:

        explicit ErrorState(const char* errorMessage = nullptr);
        ErrorState(const ErrorState& em) = delete;
        
        ErrorState& operator=(const ErrorState& em) = delete;
        virtual ~ErrorState();
        void clear();
        bool isClear() const;
        void message(const char* str);
        const char* message()const;
    };

    std::ostream& operator<<(std::ostream& os, ErrorState&);

}

#endif