//
// Created by Alex on 12.04.2023.
//
#pragma once

#ifndef A6_915_MINDRILA_MIHAIL_1_ADMINISTRATORTRENCHCOATSERVICE_H
#define A6_915_MINDRILA_MIHAIL_1_ADMINISTRATORTRENCHCOATSERVICE_H

#endif //A6_915_MINDRILA_MIHAIL_1_ADMINISTRATORTRENCHCOATSERVICE_H

#include "../Repositories/TrenchCoatRepository.h"
#include "../Domain/IdGenerator.h"
#include "../Domain/TrenchCoatValidator.h"
#include "../Repositories/FileShoppingBasket.h"

class AdministratorTrenchCoatService
{
private:
    TrenchCoatRepository &store_trench_coat_repository;
    TrenchCoatValidator trench_coat_validator;
public:
    AdministratorTrenchCoatService(TrenchCoatRepository &given_trench_coat_repository, TrenchCoatValidator &given_trench_coat_validator);

    ~AdministratorTrenchCoatService() = default;

    void addTrenchCoatToRepository(const std::string &size, const std::string &colour, double price, int quantity,
                              const std::string &photo_link);

    void removeTrenchCoatFromRepositoryById(int id);

    void updateTrenchCoatFromRepositoryById(int id, const std::string &size, const std::string &colour, double price,
                                            int quantity,
                                            const std::string &photo_link);

    std::vector<TrenchCoat> getTrenchCoats();



    bool
    isTrenchCoatInRepositoryByAttributes(const std::string &size, const std::string &colour, double price, int quantity,
                                         const std::string &photo_link);

};