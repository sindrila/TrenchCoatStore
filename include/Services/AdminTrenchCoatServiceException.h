//
// Created by Alex on 11.04.2023.
//

#ifndef A6_915_MINDRILA_MIHAIL_1_TRENCHCOATREPOSITORYEXCEPTION_H
#define A6_915_MINDRILA_MIHAIL_1_TRENCHCOATREPOSITORYEXCEPTION_H

#endif //A6_915_MINDRILA_MIHAIL_1_TRENCHCOATREPOSITORYEXCEPTION_H

#include <exception>
#include <string>
#include <utility>

class AdminTrenchCoatServiceException : public std::exception
{
private:
    std::string exception_message;
public:
    AdminTrenchCoatServiceException() : exception_message("An error occurred in the admin trench coat service.") {}
    explicit AdminTrenchCoatServiceException(std::string given_message) : exception_message(std::move(given_message)) {};

    const char* what() const noexcept override
    {
        return this->exception_message.c_str();
    }
};