//
// Created by Alex on 18.05.2023.
//
#pragma once

#ifndef A89_915_MINDRILA_MIHAIL_FAKETRENCHCOATREPOSITORY_H
#define A89_915_MINDRILA_MIHAIL_FAKETRENCHCOATREPOSITORY_H

#include "TrenchCoatRepository.h"

class FakeTrenchCoatRepository : public TrenchCoatRepository
{
public:
    FakeTrenchCoatRepository() : isTrenchCoatInRepositoryByAttributesOption{false}, throwsRemoveTrenchCoatRepositoryException(false) {};

    ~FakeTrenchCoatRepository() = default;

    bool isTrenchCoatInRepositoryByAttributesOption;
    bool throwsRemoveTrenchCoatRepositoryException;

    void addTrenchCoatToRepository(const std::string &size, const std::string &colour, double price, int quantity,
                                   const std::string &photo_link) override;
    bool isTrenchCoatInRepositoryByAttributes(const std::string &size, const std::string &colour, double price, int quantity, const std::string &photo_link) override;
    void removeTrenchCoatFromRepository(int id) override;
};


#endif //A89_915_MINDRILA_MIHAIL_FAKETRENCHCOATREPOSITORY_H
