//
// Created by Alex on 29.03.2023.
//

#ifndef A45_915_MINDRILA_MIHAIL_TRENCHCOAT_H
#define A45_915_MINDRILA_MIHAIL_TRENCHCOAT_H

#include <string>
#include "IdGenerator.h"
#include <iostream>
#include "../../utils/Utilities.h"

class TrenchCoat
{
private:
    int id;
    std::string size;
    std::string colour;
    double price;
    int quantity;
    std::string photo_link;

public:
    TrenchCoat();
    TrenchCoat(int id, std::string size, std::string colour, double price, int quantity, std::string photo_link);
    TrenchCoat(const TrenchCoat& other);

    int getId() const;
    const std::string &getSize() const;
    const std::string &getColour() const;
    double getPrice() const;
    int getQuantity() const;
    const std::string &getPhotoLink() const;

    void setId(int new_id);
    void setSize(const std::string& new_size);
    void setColour(const std::string& new_colour);
    void setPrice(double new_price);
    void setQuantity(int new_quantity);
    void setPhotoLink(const std::string& new_photo_link);

    bool operator==(const TrenchCoat& other_trench_coat) const;
    bool operator!=(const TrenchCoat& other_trench_coat) const;

    friend std::ostream& operator<<(std::ostream& os, const TrenchCoat& coat);
    friend std::istream& operator>>(std::istream& is, TrenchCoat& coat);
};


#endif //A45_915_MINDRILA_MIHAIL_TRENCHCOAT_H
