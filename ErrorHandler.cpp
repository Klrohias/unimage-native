//
// Created by Twiiz on 2023/5/31.
//

#include <stdexcept>
#include "ErrorHandler.hpp"

void ErrorHandler::setError(const std::string& message)
{
    _message = message;
}

const std::string& ErrorHandler::getError() const
{
    return _message;
}

void ErrorHandler::setErrorAndThrow(const std::string& message)
{
    _message = message;
    throw std::runtime_error(message);
}

bool ErrorHandler::run(const std::function<void()>& callfunc)
{
    try {
        callfunc();
        return true;
    } catch (const std::runtime_error& ex) {
        return false;
    }
}
