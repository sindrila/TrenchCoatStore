//
// Created by Alex on 04.05.2023.
//

#include "../../include/Repositories/HTMLShoppingBasket.h"
#include <fstream>
#include "../../include/Repositories/FileException.h"



void HTMLShoppingBasket::writeToFile()
{
    if (!this->file_path.empty())
    {
        std::ofstream file(this->file_path);

        if (!file.is_open())
            throw FileException("The data file could not be opened.");

        file << "<!DOCTYPE html>\n";
        file << "<html>\n";

        file << "<head>\n";
            file << "\t<title>Shopping Basket</title>";
        file << "</head>\n";

        file <<"<body>\n";
            file << "<table border=\"1\">\n";
                file << "<tr>\n";
                    file << "<td>Size</td>\n";
                    file << "<td>Colour</td>\n";
                    file << "<td>Price</td>\n";
                    file << "<td>Quantity</td>\n";
                    file << "<td>Photo link</td>\n";
                file << "</tr>\n";
                for (auto trench_coat : this->getTrenchCoatsInShoppingBasket())
                {
                    file << "<tr>\n";
                    file << "<td>" << trench_coat.getSize() << "</td>\n";
                    file << "<td>" << trench_coat.getColour() << "</td>\n";
                    file << "<td>" << trench_coat.getPrice() << "</td>\n";
                    file << "<td>" << trench_coat.getQuantity() << "</td>\n";
                    file << "<td><a href=\"" << trench_coat.getPhotoLink() << "\">Link</a></td>\n";
                    file << "</tr>\n";
                }
            file << "</table>\n";
        file << "</body>\n";

        file << "</html>\n";
    }

}

void HTMLShoppingBasket::displayShoppingBasket()
{
    std::string command = "open " + this->file_path;
    system(command.c_str());
}
