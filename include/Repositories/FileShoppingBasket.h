//
// Created by Alex on 04.05.2023.
//
#pragma once

#ifndef A7_915_MINDRILA_MIHAIL_1_FILESHOPPINGBASKET_H
#define A7_915_MINDRILA_MIHAIL_1_FILESHOPPINGBASKET_H

#include <string>
#include "ShoppingBasket.h"
class FileShoppingBasket : public ShoppingBasket
{
protected:
    std::string file_path;
public:
    FileShoppingBasket(const std::string& new_file_path) : file_path(new_file_path) {}
    virtual ~FileShoppingBasket() = default;

    virtual void writeToFile() = 0;
    virtual void displayShoppingBasket() = 0;
};


#endif //A7_915_MINDRILA_MIHAIL_1_FILESHOPPINGBASKET_H
