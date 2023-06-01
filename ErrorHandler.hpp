//
// Created by Twiiz on 2023/5/31.
//

#ifndef UNIMAGE_ERRORHANDLER_HPP
#define UNIMAGE_ERRORHANDLER_HPP

#include <string>
#include <functional>

class ErrorHandler
{
    std::string _message{};
public:
    void setError(const std::string& message);

    const std::string& getError() const;

    void setErrorAndThrow(const std::string& message);

    bool run(const std::function<void()>& callfunc);
};


#endif //UNIMAGE_ERRORHANDLER_HPP
