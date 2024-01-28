//
// Created by Alex on 04.05.2023.
//

#pragma once

#ifndef A7_915_MINDRILA_MIHAIL_1_SHOPPINGBASKET_H
#define A7_915_MINDRILA_MIHAIL_1_SHOPPINGBASKET_H

#endif //A7_915_MINDRILA_MIHAIL_1_SHOPPINGBASKET_H

#include <vector>
#include "../Domain/TrenchCoat.h"
#include "../Domain/TrenchCoatValidator.h"
#include "../Domain/IdGenerator.h"

class ShoppingBasket
{
protected:
    std::vector<TrenchCoat> shopping_basket_repository;
    TrenchCoatValidator trench_coat_validator;
    IdGenerator id_generator;

public:
    ShoppingBasket() = default;
    ~ShoppingBasket() = default;
    void addTrenchCoatToShoppingBasket(const std::string &size, const std::string &colour,
                                       double price, int quantity,
                                       const std::string &photo_link);
    std::vector<TrenchCoat> getTrenchCoatsInShoppingBasket();
    int getNumberOfCoatsInShoppingBasket();
};