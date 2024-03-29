#include <exception>
#include <string>

#ifndef RUNERROR_H
#define RUNERROR_H


class InitException : public std::exception {
private:
    std::string message;
public:
    InitException(const std::string& msg) : message(msg) {}

    // 예외 메시지를 반환하는 함수를 오버라이드합니다.
    const char* what() const noexcept override {
        return message.c_str();
    }
};


#endif