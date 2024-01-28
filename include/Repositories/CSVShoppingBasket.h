//
// Created by Alex on 04.05.2023.
//
#pragma once

#ifndef A7_915_MINDRILA_MIHAIL_1_CSVSHOPPINGBASKET_H
#define A7_915_MINDRILA_MIHAIL_1_CSVSHOPPINGBASKET_H

#endif //A7_915_MINDRILA_MIHAIL_1_CSVSHOPPINGBASKET_H

#include "FileShoppingBasket.h"

class CSVShoppingBasket : public FileShoppingBasket
{
public:
    CSVShoppingBasket(const std::string& new_file_path) : FileShoppingBasket(new_file_path) {};
    ~CSVShoppingBasket() = default;

    void writeToFile() override;
    void displayShoppingBasket() override;
};
