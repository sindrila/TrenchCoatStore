#include "../../Include/Services/AdministratorTrenchCoatService.h"
#include "../../Include/Services/AdminTrenchCoatServiceException.h"
#include "../../include/Repositories/TrenchCoatRepositoryException.h"

AdministratorTrenchCoatService::AdministratorTrenchCoatService(TrenchCoatRepository &given_trench_coat_repository,
                                                               TrenchCoatValidator &given_trench_coat_validator)
        : store_trench_coat_repository{given_trench_coat_repository},
          trench_coat_validator{given_trench_coat_validator}
{
}

void AdministratorTrenchCoatService::addTrenchCoatToRepository(const std::string &size, const std::string &colour,
                                                               double price, int quantity,
                                                               const std::string &photo_link)
{
    if (this->isTrenchCoatInRepositoryByAttributes(size, colour, price, quantity, photo_link))
        throw AdminTrenchCoatServiceException("Trench coat already exists.");

    this->store_trench_coat_repository.addTrenchCoatToRepository(size, colour, price, quantity, photo_link);
}

bool
AdministratorTrenchCoatService::isTrenchCoatInRepositoryByAttributes(const std::string &size, const std::string &colour,
                                                                     double price, int quantity,
                                                                     const std::string &photo_link)
{
    return this->store_trench_coat_repository.isTrenchCoatInRepositoryByAttributes(size, colour, price, quantity,
                                                                                   photo_link);
}



void AdministratorTrenchCoatService::removeTrenchCoatFromRepositoryById(int id)
{
    try
    {
        this->store_trench_coat_repository.removeTrenchCoatFromRepository(id);
    }
    catch (const TrenchCoatRepositoryException &e)
    {
        throw AdminTrenchCoatServiceException("There is no trench coat with the given ID.");
    }
}

void AdministratorTrenchCoatService::updateTrenchCoatFromRepositoryById(int id, const std::string &size,
                                                                        const std::string &colour, double price,
                                                                        int quantity, const std::string &photo_link)
{
    this->trench_coat_validator.validateTrenchCoatData(TrenchCoat(id, size, colour, price, quantity, photo_link));
    try
    {
        this->store_trench_coat_repository.updateTrenchCoatFromRepository(id, size, colour, price, quantity,
                                                                          photo_link);
    }
    catch (const TrenchCoatRepositoryException &e)
    {
        throw AdminTrenchCoatServiceException("Trench coat does not exist.");
    }
}

std::vector<TrenchCoat> AdministratorTrenchCoatService::getTrenchCoats()
{
    return this->store_trench_coat_repository.getTrenchCoats();
}


