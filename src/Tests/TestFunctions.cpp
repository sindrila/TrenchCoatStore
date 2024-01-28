#include <cassert>
#include "../../include/Domain/IdGenerator.h"
#include "../../include/Tests/TestFunctions.h"
#include "../../include/Repositories/TrenchCoatRepository.h"
#include "../../include/Services/AdministratorTrenchCoatService.h"
#include <sstream>
#include "../../include/Services/AdminTrenchCoatServiceException.h"
#include "../../include/Repositories/TrenchCoatRepositoryException.h"
#include "../../include/Services/UserTrenchCoatService.h"
#include "../../include/Domain/TrenchCoatValidator.h"
#include "../../include/Repositories/FakeTrenchCoatRepository.h"
#include "../../include/Domain/FakeTrenchCoatValidator.h"

void testIdGenerator()
{
    IdGenerator id_generator;
    assert(id_generator.getNextId() == 1);
    assert(id_generator.getNextId() == 2);
    for (int i = 3; i <= 100; i++)
    {
        assert(id_generator.getNextId() == i);
    }
}

void testAdministratorTrenchCoatService()
{
    TrenchCoatRepository repository;
    TrenchCoatValidator validator;
    AdministratorTrenchCoatService service(repository, validator);

    service.addTrenchCoatToRepository("M", "pink", 250, 10, "https://example.com");
    assert(service.isTrenchCoatInRepositoryByAttributes("M", "pink", 250, 10, "https://example.com") == true);
    try
    {
        service.addTrenchCoatToRepository("M", "pink", 250, 10, "https://example.com");
        assert(false);
    } catch (const AdminTrenchCoatServiceException &service_exception)
    {
        assert(true);
    }
    service.addTrenchCoatToRepository("L", "purple", 150, 20, "https://example.com");
    service.addTrenchCoatToRepository("S", "red", 100, 30, "https://example.com");
    service.addTrenchCoatToRepository("XS", "blue", 200, 40, "https://example.com");
    service.removeTrenchCoatFromRepositoryById(1);
    assert(service.isTrenchCoatInRepositoryByAttributes("M", "pink", 250, 10, "https://example.com") == false);
    assert(service.isTrenchCoatInRepositoryByAttributes("L", "purple", 150, 20, "https://example.com") == true);
    try
    {
        service.removeTrenchCoatFromRepositoryById(1);
        assert(false);
    }
    catch (const AdminTrenchCoatServiceException &service_exception)
    {
        assert(true);
    }
    service.updateTrenchCoatFromRepositoryById(2, "L", "pink", 199.9, 10, "https://example2.com");
    assert(service.isTrenchCoatInRepositoryByAttributes("L", "purple", 150, 20, "https://example.com") == false);
    assert(service.isTrenchCoatInRepositoryByAttributes("L", "pink", 199.9, 10, "https://example2.com") == true);
    std::vector<TrenchCoat> trench_coats_copy = service.getTrenchCoats();
    TrenchCoat last_trench_coat_added = trench_coats_copy.back();
    assert(service.isTrenchCoatInRepositoryByAttributes(last_trench_coat_added.getSize(),
                                                        last_trench_coat_added.getColour(),
                                                        last_trench_coat_added.getPrice(),
                                                        last_trench_coat_added.getQuantity(),
                                                        last_trench_coat_added.getPhotoLink()));

    try
    {
        service.updateTrenchCoatFromRepositoryById(6, "M", "turquoise", 14, 144, "www.google.com");
        assert(false);
    }
    catch (const AdminTrenchCoatServiceException &service_exception)
    {
        assert(true);
    }
}

void testTrenchCoat()
{
    TrenchCoat coat(1, "M", "Black", 100.0, 2, "https://example.com/trenchcoat.jpg");

    assert(coat.getId() == 1);
    assert(coat.getSize() == "M");
    assert(coat.getColour() == "Black");
    assert(coat.getPrice() == 100.0);
    assert(coat.getQuantity() == 2);
    assert(coat.getPhotoLink() == "https://example.com/trenchcoat.jpg");

    coat.setSize("L");
    assert(coat.getSize() == "L");

    coat.setColour("Blue");
    assert(coat.getColour() == "Blue");

    coat.setPrice(120.0);
    assert(coat.getPrice() == 120.0);

    coat.setQuantity(3);
    assert(coat.getQuantity() == 3);

    coat.setPhotoLink("https://example.com/newtrenchcoat.jpg");
    assert(coat.getPhotoLink() == "https://example.com/newtrenchcoat.jpg");

    TrenchCoat coat2(1, "M", "Black", 100.0, 2, "https://example.com/trenchcoat.jpg");
    TrenchCoat coat3(2, "L", "Blue", 120.0, 3, "https://example.com/newtrenchcoat.jpg");
    assert(coat == coat2);
    assert(coat == coat3);

    assert(coat != coat3);
    assert(coat != coat2);

    TrenchCoat coat_copy(coat);
    assert(coat_copy == coat);

    TrenchCoat coat4(1, "M", "Black", 200.0, 10, "https://example.com/photo.jpg");
    std::stringstream stream;
    stream << coat4;
    std::string output = stream.str();
    std::string expected_output = "M,Black,200,10,https://example.com/photo.jpg";
    assert(output == expected_output);
}

void testUserTrenchCoatService()
{
//    TrenchCoatRepository repository;
//    UserTrenchCoatService user_service(repository);
//
//    std::vector<TrenchCoat> all_coats_in_repo = user_service.getTrenchCoatsWithSize("");

//    std::vector<TrenchCoat> trench_coats_with_size_m_in_repo = user_service.getTrenchCoatsWithSize("M");
//    assert(trench_coats_with_size_m_in_repo.size() == 2);
//    assert(trench_coats_with_size_m_in_repo[0].getId() == 2);
//    assert(trench_coats_with_size_m_in_repo[1].getId() == 9);

//    std::vector<TrenchCoat> test = user_service.getTrenchCoatsWithSize("XXS");
//    assert(test.empty() == true);
//    assert(user_service.userAddedTrenchCoatsToShoppingCart() == false);

//    user_service.addTrenchCoatToShoppingCart(trench_coats_with_size_m_in_repo[0]);
//
//    assert(user_service.getCurrentPriceInShoppingCart() == 200);
//    user_service.addTrenchCoatToShoppingCart(trench_coats_with_size_m_in_repo[1]);
//    assert(user_service.getCurrentPriceInShoppingCart() == 213.6);
//
//    std::vector<TrenchCoat> trench_coats_in_cart = user_service.getTrenchCoatsInShoppingCart();
//    assert(trench_coats_in_cart[0] == trench_coats_with_size_m_in_repo[0]);
//    assert(trench_coats_in_cart[1] == trench_coats_with_size_m_in_repo[1]);
}

void testTrenchCoatRepository()
{
    TrenchCoatRepository repository;
    repository.addTrenchCoatToRepository("M", "Black", 100.0, 2, "https://example.com/trenchcoat.jpg");
    assert(true);
}

void testTrenchCoatRepositoryException()
{
    TrenchCoatRepositoryException exception;
    assert(std::string(exception.what()) == "An error occurred in the trench coat repository.");
    TrenchCoatRepositoryException exception_with_message("Test message");
    assert(std::string(exception_with_message.what()) == "Test message");

}

void testAdminTrenchCoatServiceException()
{
    AdminTrenchCoatServiceException exception;
    assert(std::string(exception.what()) == "An error occurred in the admin trench coat service.");
}


void Add_ValidInput_UniqueTrenchCoat_AdministratorServiceTest()
{
    FakeTrenchCoatRepository fakeRepository;
    FakeTrenchCoatValidator fakeTrenchCoatValidator;
    AdministratorTrenchCoatService testService(fakeRepository, fakeTrenchCoatValidator);
    testService.addTrenchCoatToRepository("M", "blue", 123, 12321, "www.google.com");
    assert(true);
}

void Add_InvalidInput_AlreadyExistingTrenchCoat_AdminTrenchCoatServiceException_AdministratorServiceTest()
{
    FakeTrenchCoatRepository fakeRepository;
    FakeTrenchCoatValidator fakeTrenchCoatValidator;
    AdministratorTrenchCoatService testService(fakeRepository, fakeTrenchCoatValidator);
    fakeRepository.isTrenchCoatInRepositoryByAttributesOption = true;
    try
    {
        testService.addTrenchCoatToRepository("M", "blue", 123, 12321, "www.google.com");
        assert(false);
    }
    catch (const AdminTrenchCoatServiceException& exception)
    {
        assert(true);
    }
}

void Remove_ValidInput_ExistingTrenchCoat_AdministratorServiceTest()
{
    FakeTrenchCoatRepository fakeRepository;
    FakeTrenchCoatValidator fakeTrenchCoatValidator;
    AdministratorTrenchCoatService testService(fakeRepository, fakeTrenchCoatValidator);
    fakeRepository.throwsRemoveTrenchCoatRepositoryException = false;
    testService.removeTrenchCoatFromRepositoryById(2);
}

void Remove_InvalidInput_NonExistingTrenchCoat_AdminTrenchCoatServiceException_AdministratorServiceTest()
{
    FakeTrenchCoatRepository fakeRepository;
    FakeTrenchCoatValidator fakeTrenchCoatValidator;
    AdministratorTrenchCoatService testService(fakeRepository, fakeTrenchCoatValidator);
    fakeRepository.throwsRemoveTrenchCoatRepositoryException = true;
    try
    {
        testService.removeTrenchCoatFromRepositoryById(2);
        assert(false);
    }
    catch (const AdminTrenchCoatServiceException& exception)
    {
        assert(true);
    }
}

