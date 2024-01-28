//
// Created by Alex on 12.04.2023.
//
#include "../../Include/Services/UserTrenchCoatService.h"
#include "../../include/Repositories/HTMLShoppingBasket.h"
#include "../../include/Repositories/CSVShoppingBasket.h"

UserTrenchCoatService::UserTrenchCoatService(TrenchCoatRepository &given_store_trench_coat_repository,
                                             FileShoppingBasket *new_file_shopping_basket) :
        shopping_cart{new_file_shopping_basket}, current_price_in_shopping_cart{0}, store_trench_coat_repository(
        given_store_trench_coat_repository), currentIndexOfTrenchCoatInRepository{-1},
        currentIndexOfTrenchCoatInShoppingCart{-1}
{}

std::vector<TrenchCoat> UserTrenchCoatService::getTrenchCoatsWithSize(const std::string &clothing_size)
{
    std::vector<TrenchCoat> trench_coats_in_repository = this->store_trench_coat_repository.getTrenchCoats();

    if (clothing_size.empty())
        return trench_coats_in_repository;

    std::vector<TrenchCoat> trench_coats_with_given_size;
    auto has_same_size = [clothing_size](auto trench_coat_to_compare_with)
    { return trench_coat_to_compare_with.getSize() == clothing_size; };

    std::copy_if(trench_coats_in_repository.begin(), trench_coats_in_repository.end(),
                 std::back_inserter(trench_coats_with_given_size),
                 has_same_size);

    return trench_coats_with_given_size;
}

double UserTrenchCoatService::getCurrentPriceInShoppingCart() const
{
    return this->current_price_in_shopping_cart;
}

void UserTrenchCoatService::addTrenchCoatToShoppingCart(const TrenchCoat &trench_coat_to_add)
{
    this->shopping_cart->addTrenchCoatToShoppingBasket(trench_coat_to_add.getSize(),
                                                       trench_coat_to_add.getColour(),
                                                       trench_coat_to_add.getPrice(),
                                                       trench_coat_to_add.getQuantity(),
                                                       trench_coat_to_add.getPhotoLink());
    this->current_price_in_shopping_cart += trench_coat_to_add.getPrice();
}


std::vector<TrenchCoat> UserTrenchCoatService::getTrenchCoatsInShoppingCart()
{
    return this->shopping_cart->getTrenchCoatsInShoppingBasket();
}

bool UserTrenchCoatService::userAddedTrenchCoatsToShoppingCart()
{
    return this->shopping_cart->getNumberOfCoatsInShoppingBasket() != 0;
}

void UserTrenchCoatService::saveShoppingBasketToFile()
{
    if (this->shopping_cart == nullptr)
        return;

    this->shopping_cart->writeToFile();
}

void UserTrenchCoatService::openShoppingBasketFile()
{
    this->saveShoppingBasketToFile();
    this->shopping_cart->displayShoppingBasket();
}

TrenchCoat UserTrenchCoatService::getNextTrenchCoatInRepository()
{
    if (currentIndexOfTrenchCoatInRepository == this->trenchCoatsWithGivenSize.size() - 1)
        currentIndexOfTrenchCoatInRepository = -1;

    return this->trenchCoatsWithGivenSize[++currentIndexOfTrenchCoatInRepository];
}

void UserTrenchCoatService::setSizeOfTrenchCoatsToShow(const std::string &givenSizeOfTrenchCoats)
{
    currentIndexOfTrenchCoatInRepository = -1;
    if (givenSizeOfTrenchCoats == "All sizes.")
        this->trenchCoatsWithGivenSize = this->store_trench_coat_repository.getTrenchCoats();
    else
        this->trenchCoatsWithGivenSize = this->getTrenchCoatsWithSize(givenSizeOfTrenchCoats);
}

void UserTrenchCoatService::addCurrentTrenchCoatToShoppingCart()
{
    TrenchCoat currentlyDisplayedTrenchCoat = this->trenchCoatsWithGivenSize[currentIndexOfTrenchCoatInRepository];
    this->addTrenchCoatToShoppingCart(currentlyDisplayedTrenchCoat);
}

TrenchCoat UserTrenchCoatService::getNextTrenchCoatInShoppingCart()
{
    if (currentIndexOfTrenchCoatInShoppingCart == this->shopping_cart->getNumberOfCoatsInShoppingBasket() - 1)
        currentIndexOfTrenchCoatInShoppingCart = -1;
    return this->shopping_cart->getTrenchCoatsInShoppingBasket()[++currentIndexOfTrenchCoatInShoppingCart];
}

int UserTrenchCoatService::getNumberOfTrenchCoatsInShoppingCart()
{
    return this->shopping_cart->getNumberOfCoatsInShoppingBasket();
}

void UserTrenchCoatService::setFileShoppingBasket(FileShoppingBasket* shoppingCart)
{
    shopping_cart = shoppingCart;
}



