//
// Created by Alex on 04.05.2023.
//

#include "../../include/Repositories/CSVShoppingBasket.h"
#include <fstream>
#include "../../include/Repositories/FileException.h"
#include <cstdlib>

void CSVShoppingBasket::writeToFile()
{
    if(!this->file_path.empty())
    {
        std::ofstream trench_coat_file(this->file_path);
        if (!trench_coat_file.is_open())
            throw FileException("The data file could not be opened.");
        for (auto trench_coat: this->shopping_basket_repository)
            trench_coat_file << trench_coat << '\n';

        trench_coat_file.close();
    }
}

void CSVShoppingBasket::displayShoppingBasket()
{
    std::string command = "open " + this->file_path;
    system(command.c_str());
}
