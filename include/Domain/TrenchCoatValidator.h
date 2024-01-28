//
// Created by Alex on 02.05.2023.
//


#ifndef A6_915_MINDRILA_MIHAIL_1_TRENCHCOATVALIDATOR_H
#define A6_915_MINDRILA_MIHAIL_1_TRENCHCOATVALIDATOR_H

#endif //A6_915_MINDRILA_MIHAIL_1_TRENCHCOATVALIDATOR_H

#pragma once
#include <vector>
#include "TrenchCoat.h"
#include <string>

class TrenchCoatException
{
private:
    std::vector<std::string> message_errors;

public:
    explicit TrenchCoatException(std::vector<std::string> new_message_errors);
    std::vector<std::string> getErrors() const;
    friend std::ostream& operator<<(std::ostream &os, const TrenchCoatException &exception_to_print);
};

class TrenchCoatValidator
{
public:
    TrenchCoatValidator() = default;
    virtual void validateTrenchCoatData(const TrenchCoat& trench_coat_to_validate);


};