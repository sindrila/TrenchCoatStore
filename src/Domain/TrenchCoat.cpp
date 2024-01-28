//
// Created by Alex on 29.03.2023.
//

#include "../../include/Domain/TrenchCoat.h"


//const std::string &getSize() const {return size;}

TrenchCoat::TrenchCoat(int id, std::string size, std::string colour, double price, int quantity, std::string photo_link)
        : id(id), size(
        std::move(size)), colour(std::move(colour)), price(price), quantity(quantity), photo_link(std::move(photo_link))
{}

const std::string &TrenchCoat::getSize() const
{
    return size;
}

const std::string &TrenchCoat::getColour() const
{
    return colour;
}

double TrenchCoat::getPrice() const
{
    return price;
}

int TrenchCoat::getQuantity() const
{
    return quantity;
}

const std::string &TrenchCoat::getPhotoLink() const
{
    return this->photo_link;
}

void TrenchCoat::setSize(const std::string &new_size)
{
    size = new_size;
}

void TrenchCoat::setColour(const std::string &new_colour)
{
    colour = new_colour;
}

void TrenchCoat::setPrice(double new_price)
{
    price = new_price;
}

void TrenchCoat::setQuantity(int new_quantity)
{
    quantity = new_quantity;
}

void TrenchCoat::setPhotoLink(const std::string &new_photo_link)
{
    photo_link = new_photo_link;
}

bool TrenchCoat::operator==(const TrenchCoat &other_trench_coat) const
{
    return (this->id == other_trench_coat.id) || (this->size == other_trench_coat.size &&
                                                  this->colour == other_trench_coat.colour &&
                                                  this->price == other_trench_coat.price &&
                                                  this->quantity == other_trench_coat.quantity &&
                                                  this->photo_link == other_trench_coat.photo_link);
}

bool TrenchCoat::operator!=(const TrenchCoat &other_trench_coat) const
{
    return this->id != other_trench_coat.id || !(this->size == other_trench_coat.size &&
                                                 this->colour == other_trench_coat.colour &&
                                                 this->price == other_trench_coat.price &&
                                                 this->quantity == other_trench_coat.quantity &&
                                                 this->photo_link == other_trench_coat.photo_link);
}

int TrenchCoat::getId() const
{
    return this->id;
}

std::ostream &operator<<(std::ostream &os, const TrenchCoat &coat)
{
    os << coat.getSize() << "," << coat.getColour() << "," << coat.getPrice() << ","
       << coat.getQuantity() << "," << coat.getPhotoLink();
    return os;
}

TrenchCoat::TrenchCoat(const TrenchCoat& other)
        : id(other.id), size(other.size), colour(other.colour), price(other.price),
          quantity(other.quantity), photo_link(other.photo_link)
{}

std::istream &operator>>(std::istream &is, TrenchCoat &coat) {
    std::string line;
    getline(is, line);

    std::vector<std::string> tokens = tokenizeFromString(line, ',');
    if (tokens.size() != 5)
        return is;

    coat.size = tokens[0];
    coat.colour = tokens[1];
    coat.price = std::stod(tokens[2]);
    coat.quantity = std::stoi(tokens[3]);
    coat.photo_link = tokens[4];

    return is;
}

TrenchCoat::TrenchCoat() : id(-1), size(""), colour(""), price(0), quantity(0), photo_link("") {}

void TrenchCoat::setId(int new_id)
{
    this->id = new_id;

}
