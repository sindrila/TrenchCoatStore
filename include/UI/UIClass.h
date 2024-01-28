//
// Created by Alex on 30.03.2023.
//

#ifndef A45_915_MINDRILA_MIHAIL_UICLASS_H
#define A45_915_MINDRILA_MIHAIL_UICLASS_H


#pragma once


const int EXIT_MENU = 0;
const int ADD_TRENCH_COAT = 1;
const int REMOVE_TRENCH_COAT = 2;
const int UPDATE_TRENCH_COAT = 3;
const int LIST_TRENCH_COATS = 4;
const int WAIT_KEY = 1;
const int ADD_TRENCH_COAT_TO_CART = 1;
const int SEE_NEXT_TRENCH_COAT = 2;
const int SEE_SHOPPING_CART = 3;
const int STOP_SHOWING_COATS = 0;
const int NEXT_TRENCH_COAT = 1;
const int ADMIN_MODE = 1;
const int USER_MODE = 2;
const int OPEN_SHOPPING_BASKET = 2;
const int SINGLE_ITEM_OPEN_SHOPPING_BASKET = 1;

#include <string>
#include <sstream>
#include "../Services/AdministratorTrenchCoatService.h"
#include "../Services/UserTrenchCoatService.h"
#include <opencv2/opencv.hpp>
#include <curl/curl.h>

class UIClass
{
private:
    AdministratorTrenchCoatService &admin_service;
    UserTrenchCoatService &user_service;
public:
    UIClass(AdministratorTrenchCoatService &admin_service, UserTrenchCoatService &user_service);

    ~UIClass() = default;

    void run();

    void runAdministratorInterface();

    void runUserInterface();

private:
    void printMenu() const;

    int readInteger(const std::string &message) const;

    double readDouble(const std::string &message) const;

    std::string readString(const std::string &message) const;

    void addTrenchCoat();

    void removeTrenchCoat();

    void updateTrenchCoat();

    void listTrenchCoats() const;

    std::string readClothingSize(const std::string &message_for_reading);

    void showTrenchCoatImage(int count, const TrenchCoat &current_trench_coat);

    void printUserTrenchCoatAttributes(const TrenchCoat &trench_coat_to_print);

    void shoppingCartMenu();

    void clothingSizeMenu();

    void buyingMenu(const std::string &clothing_size);

    void saveShoppingBasketToFile();
    void openShoppingBasketFile();
};


#endif //A45_915_MINDRILA_MIHAIL_UICLASS_H
