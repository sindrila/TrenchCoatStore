//
// Created by Alex on 18.05.2023.
//

#include "../../include/Domain/FakeTrenchCoatValidator.h"

void FakeTrenchCoatValidator::validateTrenchCoatData(const TrenchCoat &trench_coat_to_validate)
{
    if (throwsTrenchCoatException)
    {
        std::vector<std::string> error_messages;
        error_messages.emplace_back("TrenchCoatException thrown in FakeTrenchCoatRepository::addTrenchCoatToRepository");
        throw TrenchCoatException(error_messages);
    }
}
