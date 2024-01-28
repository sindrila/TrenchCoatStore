#pragma clang diagnostic push
#pragma ide diagnostic ignored "readability-static-accessed-through-instance"

#include <QApplication>
#include <QFont>
#include "../include/Repositories/TrenchCoatRepository.h"
#include "../Include/Services/AdministratorTrenchCoatService.h"
#include "../Include/Services/UserTrenchCoatService.h"
#include "../include/UI/UIClass.h"
#include "../include/Tests/TestFunctions.h"
#include "../include/Repositories/CSVShoppingBasket.h"
#include "../include/Repositories/HTMLShoppingBasket.h"
#include "../include/Repositories/FileException.h"
#include "../include/Repositories/FileShoppingBasket.h"
#include "../include/GUI/MainMenuGUI.h"

int main(int argc, char **argv)
{

    testIdGenerator();
    testAdministratorTrenchCoatService();
    testTrenchCoat();
    testUserTrenchCoatService();
    testTrenchCoatRepository();
    testTrenchCoatRepositoryException();
    testAdminTrenchCoatServiceException();

    Add_ValidInput_UniqueTrenchCoat_AdministratorServiceTest();
    Add_InvalidInput_AlreadyExistingTrenchCoat_AdminTrenchCoatServiceException_AdministratorServiceTest();
    Remove_ValidInput_ExistingTrenchCoat_AdministratorServiceTest();
    Remove_InvalidInput_NonExistingTrenchCoat_AdminTrenchCoatServiceException_AdministratorServiceTest();
    std::cout << "All tests passed successfully!\nContinuing..\n";


    QApplication main_app(argc, argv);
    main_app.setApplicationName("Cherry Kiwi Trench Coat Store");
    QFont font("Bodoni 72", 12);
    main_app.setFont(font);

    try {
        auto repo = TrenchCoatRepository("../utils/InitialTrenchCoats.txt");

        TrenchCoatValidator test_validator;
        auto admin_service = AdministratorTrenchCoatService(repo, test_validator);
        auto user_service = UserTrenchCoatService(repo, nullptr);


        auto gui = MainMenuGUI(admin_service, user_service);
        gui.show();

        return main_app.exec();

    }
    catch (FileException &file_exception) {
        std::cout << file_exception.what();
        return 1;
    }
}

#pragma clang diagnostic pop