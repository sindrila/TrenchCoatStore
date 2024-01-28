//
// Created by Alex on 04.05.2023.
//

#pragma once

#ifndef A7_915_MINDRILA_MIHAIL_1_HTMLSHOPPINGBASKET_H
#define A7_915_MINDRILA_MIHAIL_1_HTMLSHOPPINGBASKET_H

#endif //A7_915_MINDRILA_MIHAIL_1_HTMLSHOPPINGBASKET_H

#include "FileShoppingBasket.h"

#include <string>

class HTMLShoppingBasket : public FileShoppingBasket
{
public:
    HTMLShoppingBasket(const std::string& new_file_path) : FileShoppingBasket(new_file_path) {};
    ~HTMLShoppingBasket() = default;

    void writeToFile() override;
    void displayShoppingBasket() override;
};