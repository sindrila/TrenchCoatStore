#include "../../include/Repositories/TrenchCoatRepository.h"
#include "../../include/Repositories/TrenchCoatRepositoryException.h"

#include <fstream>
#include "../../include/Repositories/FileException.h"
TrenchCoatRepository::TrenchCoatRepository(const std::string &new_data_filename)
{
    this->data_filename = new_data_filename;
    this->id_generator = IdGenerator();
    this->readTrenchCoatsFromFile();
}

void TrenchCoatRepository::readTrenchCoatsFromFile()
{
    if(!this->data_filename.empty())
    {
        std::ifstream trench_coat_file(this->data_filename);

        if (!trench_coat_file.is_open())
            throw FileException("The data file could not be opened.");

        TrenchCoat trench_coat;
        while (trench_coat_file >> trench_coat)
        {
            trench_coat.setId(this->id_generator.getNextId());
            this->trench_coat_repository.push_back(trench_coat);
        }

        trench_coat_file.close();
    }
}

void TrenchCoatRepository::addTrenchCoatToRepository(const std::string &size, const std::string &colour,
                                                     double price, int quantity,
                                                     const std::string &photo_link)
{
    auto trench_coat_to_add = TrenchCoat(this->id_generator.getNextId(), size, colour, price, quantity,
                                         photo_link);

    this->trench_coat_validator.validateTrenchCoatData(trench_coat_to_add);

    this->trench_coat_repository.push_back(trench_coat_to_add);

    writeTrenchCoatsToFile();
}

//std::vector<TrenchCoat>::size_type TrenchCoatRepository::getSizeOfRepository()
//{
//    return this->trench_coat_repository.size();
//}

bool TrenchCoatRepository::isTrenchCoatInRepositoryByAttributes(const std::string &size, const std::string &colour,
                                                                double price, int quantity,
                                                                const std::string &photo_link)
{
    auto has_same_attributes = [=](const TrenchCoat &trench_coat_to_compare_with)
    {
        return trench_coat_to_compare_with.getSize() == size &&
               trench_coat_to_compare_with.getColour() == colour &&
               trench_coat_to_compare_with.getPrice() == price &&
               trench_coat_to_compare_with.getQuantity() == quantity &&
               trench_coat_to_compare_with.getPhotoLink() == photo_link;
    };

    return std::any_of(this->trench_coat_repository.begin(), this->trench_coat_repository.end(), has_same_attributes);
}

//TrenchCoat TrenchCoatRepository::getTrenchCoatById(int id)
//{
//    auto iterator = std::find_if(this->trench_coat_repository.begin(),
//                                 this->trench_coat_repository.end(),
//                                 [id](const TrenchCoat& trench_coat_to_compare_with)
//                                 { return trench_coat_to_compare_with.getId() == id; });
//    if (iterator == this->trench_coat_repository.end())
//        throw TrenchCoatRepositoryException("Trench coat with given id does not exist.");
//    return *iterator;
//}

void TrenchCoatRepository::removeTrenchCoatFromRepository(int id)
{
    auto trench_coat_iterator = std::find_if(this->trench_coat_repository.begin(),
                                             this->trench_coat_repository.end(),
                                             [id](const TrenchCoat& trench_coat_to_compare)
                                             {return id == trench_coat_to_compare.getId();});

    if (trench_coat_iterator == this->trench_coat_repository.end())
        throw TrenchCoatRepositoryException("Trench coat does not exist.");

    this->trench_coat_repository.erase(trench_coat_iterator);

    writeTrenchCoatsToFile();
}

std::vector<TrenchCoat> TrenchCoatRepository::getTrenchCoats() const
{
    std::vector<TrenchCoat> current_trench_coats;
    current_trench_coats.reserve(this->trench_coat_repository.size());

    for (const auto &trench_coat: this->trench_coat_repository)
        current_trench_coats.push_back(trench_coat);
    return current_trench_coats;
}

void TrenchCoatRepository::updateTrenchCoatFromRepository(int id, const std::string &size,
                                                          const std::string &colour, double price,
                                                          int quantity, const std::string &photo_link)
{
    auto trench_coat_iterator = std::find_if(this->trench_coat_repository.begin(),
                                             this->trench_coat_repository.end(),
                                             [id](const TrenchCoat& trench_coat_to_compare)
                                             {return id == trench_coat_to_compare.getId();});

    if (trench_coat_iterator == this->trench_coat_repository.end())
        throw TrenchCoatRepositoryException("Trench coat does not exist.");

    trench_coat_iterator->setSize(size);
    trench_coat_iterator->setColour(colour);
    trench_coat_iterator->setPrice(price);
    trench_coat_iterator->setQuantity(quantity);
    trench_coat_iterator->setPhotoLink(photo_link);

    writeTrenchCoatsToFile();
}

void TrenchCoatRepository::writeTrenchCoatsToFile()
{

    if(!this->data_filename.empty())
    {
        std::ofstream trench_coat_file(this->data_filename);
        if (!trench_coat_file.is_open())
            throw TrenchCoatRepositoryException("The data file could not pe opened.");
        for (auto trench_coat: this->trench_coat_repository)
            trench_coat_file << trench_coat << '\n';

        trench_coat_file.close();
    }
}

TrenchCoatRepository::TrenchCoatRepository() : data_filename("") {}

int TrenchCoatRepository::getNumberOfTrenchCoatsInRepository() const
{
    return this->trench_coat_repository.size();
}



