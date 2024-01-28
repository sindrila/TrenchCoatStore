//
// Created by Alex on 29.03.2023.
//

#ifndef A45_915_MINDRILA_MIHAIL_TRENCHCOATREPOSITORY_H
#define A45_915_MINDRILA_MIHAIL_TRENCHCOATREPOSITORY_H

#pragma once

#include "../Domain/TrenchCoat.h"
#include "../Domain/IdGenerator.h"
#include "../Domain/TrenchCoatValidator.h"
class TrenchCoatRepository
{
protected:
    std::vector<TrenchCoat> trench_coat_repository;
    std::string data_filename;
    IdGenerator id_generator;
    TrenchCoatValidator trench_coat_validator;
public:
    TrenchCoatRepository();
    explicit TrenchCoatRepository(const std::string& new_data_filename);
    ~TrenchCoatRepository() = default;

    void readTrenchCoatsFromFile();
    void writeTrenchCoatsToFile();

    virtual void addTrenchCoatToRepository(const std::string &size, const std::string &colour,
                                   double price, int quantity,
                                   const std::string &photo_link);

    virtual void removeTrenchCoatFromRepository(int id);

    void updateTrenchCoatFromRepository(int id, const std::string &size,
                                        const std::string &colour, double price,
                                        int quantity, const std::string &photo_link);

//    std::vector<TrenchCoat>::size_type getSizeOfRepository();

    virtual bool
    isTrenchCoatInRepositoryByAttributes(const std::string &size, const std::string &colour, double price, int quantity,
                                         const std::string &photo_link);

    std::vector<TrenchCoat> getTrenchCoats() const;

    int getNumberOfTrenchCoatsInRepository() const;
};


#endif //A45_915_MINDRILA_MIHAIL_TRENCHCOATREPOSITORY_H
