//
// Created by Alex on 05.04.2023.
//
#pragma once

#ifndef A45_915_MINDRILA_MIHAIL_USERTRENCHCOATSERVICE_H
#define A45_915_MINDRILA_MIHAIL_USERTRENCHCOATSERVICE_H

#endif //A45_915_MINDRILA_MIHAIL_USERTRENCHCOATSERVICE_H

const int MAX_TRENCH_COATS_IN_STORE = 100;


#include "../Repositories/TrenchCoatRepository.h"
#include "../Repositories/ShoppingBasket.h"
#include "../Repositories/FileShoppingBasket.h"
#include "../Domain/TrenchCoat.h"

class UserTrenchCoatService
{
private:
    FileShoppingBasket* shopping_cart;
    double current_price_in_shopping_cart;
    TrenchCoatRepository &store_trench_coat_repository;
    int currentIndexOfTrenchCoatInRepository;
    int currentIndexOfTrenchCoatInShoppingCart;
    std::vector<TrenchCoat> trenchCoatsWithGivenSize;

public:
    explicit UserTrenchCoatService(TrenchCoatRepository &given_store_trench_coat_repository,  FileShoppingBasket *new_file_shopping_basket);

    ~UserTrenchCoatService() = default;

    void addTrenchCoatToShoppingCart(const TrenchCoat &trench_coat_to_add);

    std::vector<TrenchCoat> getTrenchCoatsWithSize(const std::string &clothing_size);
    std::vector<TrenchCoat> getTrenchCoatsInShoppingCart();

    void setFileShoppingBasket(FileShoppingBasket* shoppingCart);
    void setSizeOfTrenchCoatsToShow(const std::string& givenSizeOfTrenchCoats);
    TrenchCoat getNextTrenchCoatInShoppingCart();
    TrenchCoat getNextTrenchCoatInRepository();


    [[nodiscard]] double getCurrentPriceInShoppingCart() const;

    bool userAddedTrenchCoatsToShoppingCart();
    int getNumberOfTrenchCoatsInShoppingCart();
    void addCurrentTrenchCoatToShoppingCart();


    void saveShoppingBasketToFile();
    void openShoppingBasketFile();
};