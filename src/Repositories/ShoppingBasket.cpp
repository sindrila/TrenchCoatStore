//
// Created by Alex on 04.05.2023.
//

#include "../../include/Repositories/ShoppingBasket.h"

void ShoppingBasket::addTrenchCoatToShoppingBasket(const std::string &size, const std::string &colour, double price,
                                                   int quantity, const std::string &photo_link)
{
    auto trench_coat_to_add = TrenchCoat(this->id_generator.getNextId(), size, colour, price, quantity,
                                         photo_link);

    this->trench_coat_validator.validateTrenchCoatData(trench_coat_to_add);

    this->shopping_basket_repository.push_back(trench_coat_to_add);

}

std::vector<TrenchCoat> ShoppingBasket::getTrenchCoatsInShoppingBasket()
{
    std::vector<TrenchCoat> current_trench_coats;
    current_trench_coats.reserve(this->shopping_basket_repository.size());

    for (const auto &trench_coat: this->shopping_basket_repository)
        current_trench_coats.push_back(trench_coat);
    return current_trench_coats;
}

int ShoppingBasket::getNumberOfCoatsInShoppingBasket()
{
    return this->shopping_basket_repository.size();
}
