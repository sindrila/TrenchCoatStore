//
// Created by Alex on 18.05.2023.
//

#include "../../include/Repositories/FakeTrenchCoatRepository.h"
#include "../../include/Domain/FakeTrenchCoatValidator.h"
#include "../../include/Repositories/TrenchCoatRepositoryException.h"
void
FakeTrenchCoatRepository::addTrenchCoatToRepository(const std::string &size, const std::string &colour, double price,
                                                    int quantity, const std::string &photo_link)
{}

bool FakeTrenchCoatRepository::isTrenchCoatInRepositoryByAttributes(const std::string &size, const std::string &colour,
                                                                    double price, int quantity,
                                                                    const std::string &photo_link)
{
    return this->isTrenchCoatInRepositoryByAttributesOption;
}

void FakeTrenchCoatRepository::removeTrenchCoatFromRepository(int id)
{
    if (throwsRemoveTrenchCoatRepositoryException)
        throw TrenchCoatRepositoryException("Fake test throws exception.");
}
