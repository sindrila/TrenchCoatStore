#include "../../include/UI/UIClass.h"
#include "../../include/Services/AdminTrenchCoatServiceException.h"
#include <utility>
#include "../../include/Repositories/FileException.h"

UIClass::UIClass(AdministratorTrenchCoatService &admin_service, UserTrenchCoatService &user_service) : admin_service{
        admin_service}, user_service{user_service}
{}

std::string UIClass::readClothingSize(const std::string &message_for_reading)
{
    std::string clothing_size;
    if (!message_for_reading.empty())
        std::cout << message_for_reading;
    else
        std::cout << "> ";
    std::getline(std::cin, clothing_size);

    std::transform(clothing_size.begin(), clothing_size.end(), clothing_size.begin(), [](unsigned char character)
    { return std::toupper(character); });
    return clothing_size;
}

void UIClass::printUserTrenchCoatAttributes(const TrenchCoat &trench_coat_to_print)
{
    std::cout << "\n";
    std::cout << "Trench coat id: " << trench_coat_to_print.getId() << "\n";
    std::cout << "Size: " << trench_coat_to_print.getSize() << "\n";
    std::cout << "Colour: " << trench_coat_to_print.getColour() << "\n";
    std::cout << "Price: " << trench_coat_to_print.getPrice() << "\n";
    std::cout << "Quantity: " << trench_coat_to_print.getQuantity() << "\n";
}

void UIClass::showTrenchCoatImage(int count, const TrenchCoat &current_trench_coat)
{
    CURL *curl;
    curl = curl_easy_init();
    FILE *fp;
    std::string filename = "image" + std::to_string(count) + ".jpg";
    fp = fopen(filename.c_str(), "wb");
    const std::string &photo_link = current_trench_coat.getPhotoLink();

    curl_easy_setopt(curl, CURLOPT_URL, photo_link.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, NULL);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
    CURLcode res = curl_easy_perform(curl);
    fclose(fp);
    if (res != CURLE_OK)
    {
        fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
    } else
    {
        cv::Mat image = cv::imread(filename);

        if (image.empty())
        {
            std::cout << "Could not open or find the image\n";
        } else
        {
            cv::imshow("Display window", image);
            cv::waitKey(WAIT_KEY);
        }
    }
    curl_easy_cleanup(curl);
}

void UIClass::shoppingCartMenu()
{

    std::vector<TrenchCoat> trench_coats_in_shopping_cart = this->user_service.getTrenchCoatsInShoppingCart();

    if (!trench_coats_in_shopping_cart.empty())
    {
        std::cout << "Welcome the your shopping cart! Here is what you added to it:" << '\n';

        bool keep_showing_cart = true;
        auto trench_coat_iterator = trench_coats_in_shopping_cart.begin();

        this->saveShoppingBasketToFile();

        int index_of_trench_coat = 1;
        while (keep_showing_cart)
        {
            auto trench_coat = *trench_coat_iterator;

            std::cout << '\n' << "Total cost is: " << this->user_service.getCurrentPriceInShoppingCart() << '\n';

            this->printUserTrenchCoatAttributes(trench_coat);
            this->showTrenchCoatImage(index_of_trench_coat, trench_coat);

            int choice;
            bool tried_to_read = false;


            if (trench_coats_in_shopping_cart.size() > 1)
            {
                std::cout << "Choose an option:" << '\n';
                std::cout << "1. Next trench coat." << '\n';
                std::cout << "2. Display file trench coats in app." << '\n';
                std::cout << "0. Exit" << '\n';
                do
                {
                    if (tried_to_read)
                        std::cout << "Not a valid choice. Try again.\n";
                    choice = this->readInteger("Please choose a value between 0 and 2.\n> ");
                    tried_to_read = true;
                } while (choice != STOP_SHOWING_COATS and choice != NEXT_TRENCH_COAT and choice != OPEN_SHOPPING_BASKET);
                switch (choice)
                {
                    case STOP_SHOWING_COATS:
                    {
                        keep_showing_cart = false;
                        break;
                    }
                    case NEXT_TRENCH_COAT:
                    {
                        index_of_trench_coat++;
                        trench_coat_iterator++;
                        if (index_of_trench_coat > trench_coats_in_shopping_cart.size())
                        {
                            index_of_trench_coat = 1;
                            trench_coat_iterator = trench_coats_in_shopping_cart.begin();
                        }
                        break;
                    }
                    case OPEN_SHOPPING_BASKET:
                    {
                        this->openShoppingBasketFile();
                        keep_showing_cart = false;
                        break;
                    }
                }
            } else
            {
                std::cout << "This is your only trench coat.\n";
                do
                {
                    if (tried_to_read)
                        std::cout << "Not 1 or 0. Try again.\n";
                    choice = this->readInteger("Enter 1 to open the shopping basket file, or 0 to exit \n");
                    tried_to_read = true;
                } while (choice != STOP_SHOWING_COATS and choice != SINGLE_ITEM_OPEN_SHOPPING_BASKET);
                if (choice == STOP_SHOWING_COATS)
                {
                    keep_showing_cart = false;
                }
                else
                {
                    this->openShoppingBasketFile();
                    break;
                }
            }
        }
    } else
        std::cout << "You did not buy anything, sorry to see you go!";

}

void UIClass::buyingMenu(const std::string &clothing_size)
{

    std::vector<TrenchCoat> trench_coats_with_given_size = this->user_service.getTrenchCoatsWithSize(
            clothing_size);

    if (trench_coats_with_given_size.empty())
    {
        std::cout << "I'm sorry, but there are no trench coats with the given size in our store.\n";
        std::cout << "Have a good day!\n";
        return;
    }

    bool stop_showing_trench_coats = false;
    while (!stop_showing_trench_coats)
    {
        int index = 0;
        for (const auto &trench_coat: trench_coats_with_given_size)
        {
            if (stop_showing_trench_coats)
                break;
            this->printUserTrenchCoatAttributes(trench_coat);
            this->showTrenchCoatImage(index + 1, trench_coat);

            bool valid_choice = false;
            while (!valid_choice)
            {
                int choice = readInteger("Choose an option:\n"
                                         "1. Add this trench coat to your shopping cart\n"
                                         "2. See next trench coat\n"
                                         "3. See your shopping cart\n> \n");
                switch (choice)
                {
                    case ADD_TRENCH_COAT_TO_CART:
                    {
                        this->user_service.addTrenchCoatToShoppingCart(trench_coat);
                        valid_choice = true;
                        break;
                    }
                    case SEE_NEXT_TRENCH_COAT:
                    {
                        valid_choice = true;
                        break;
                    }
                    case SEE_SHOPPING_CART:
                    {
                        valid_choice = true;
                        stop_showing_trench_coats = true;
                        break;
                    }
                    default:
                    {
                        std::cout << "Sorry, but that is not a valid choice. Try again." << '\n';
                    }
                }
            }
            index++;
        }
    }
}


void UIClass::clothingSizeMenu()
{
    std::cout << "Welcome to the Proper Trench Coats store!\n";
    std::cout << "Please enter a size, and we will provide you with the available trench coats in that size.\n";
    std::cout << "If you would like to see all available trench coats, just press enter.\n";
}

void UIClass::runUserInterface()
{
    this->clothingSizeMenu();

    std::string clothing_size;
    clothing_size = readClothingSize("");

    this->buyingMenu(clothing_size);

    if (this->user_service.userAddedTrenchCoatsToShoppingCart())
    {
        this->shoppingCartMenu();
        std::cout << "Thank you for shopping with us!\n";
    }
}

void UIClass::runAdministratorInterface()
{

    int option;
    while (true)
    {
        printMenu();
        option = readInteger("Option: ");

        switch (option)
        {
            case EXIT_MENU:
                return;
            case ADD_TRENCH_COAT:
                addTrenchCoat();
                break;
            case REMOVE_TRENCH_COAT:
                removeTrenchCoat();
                break;
            case UPDATE_TRENCH_COAT:
                updateTrenchCoat();
                break;
            case LIST_TRENCH_COATS:
                listTrenchCoats();
                break;
            default:
                std::cout << "Invalid option!\n";
                break;
        }
    }
}

void UIClass::printMenu() const
{
    std::cout << "\n" << "1. Add a new trench coat to the repository.\n";
    std::cout << "2. Remove a trench coat from the repository.\n";
    std::cout << "3. Update the information of a trench coat from the repository.\n";
    std::cout << "4. List all trench coats from the repository.\n";
    std::cout << "0. Exit.\n";
}

int UIClass::readInteger(const std::string &message) const
{
    int input;
    std::string line;
    while (true)
    {
        std::cout << message;
        std::getline(std::cin, line);
        std::stringstream ss(line);
        if (ss >> input && ss.eof())
        {
            break;
        }
        std::cout << "Invalid input. Please try again.\n";
    }
    return input;
}

double UIClass::readDouble(const std::string &message) const
{
    double input;
    std::string line;
    while (true)
    {
        std::cout << message;
        std::getline(std::cin, line);
        std::stringstream ss(line);
        if (ss >> input && ss.eof())
        {
            break;
        }
        std::cout << "Invalid input. Please try again.\n";
    }
    return input;
}

std::string UIClass::readString(const std::string &message) const
{
    std::string input;
    bool tried_to_read = false;
    while (input.empty())
    {
        if (tried_to_read)
        {
            std::cout << "Invalid input. Please try again.\n";
        }
        std::cout << message;
        std::getline(std::cin, input);
        tried_to_read = true;
    }

    return input;
}

void UIClass::addTrenchCoat()
{
    try
    {
        std::string size = this->readClothingSize("Size: ");
        std::string colour = readString("Colour: ");
        double price = readDouble("Price: ");
        int quantity = readInteger("Quantity: ");
        std::string photo_link = readString("Photograph: ");
        admin_service.addTrenchCoatToRepository(size, colour, price, quantity, photo_link);
    }
    catch (const AdminTrenchCoatServiceException &add_exception)
    {
        std::cout << "\nCould not add the trench coat:\n";
        std::cout << add_exception.what() << "\n";
        std::cout << "Try again.\n";
    }
    catch (const TrenchCoatException &creation_exception)
    {
        std::cout << "\nCould not add the trench coat:\n";
        std::cout << creation_exception;
        std::cout << "Try again.\n";
    }
}

void UIClass::removeTrenchCoat()
{
    listTrenchCoats();
    std::cout << "Please enter the trench coat id you want to remove.\n";
    while (true)
    {
        try
        {
            int trench_coat_id = readInteger("Trench coat id: ");
            admin_service.removeTrenchCoatFromRepositoryById(trench_coat_id);
            break;
        }
        catch (const AdminTrenchCoatServiceException &remove_exception)
        {
            std::cout << "\nCould not remove the trench coat:\n";
            std::cout << remove_exception.what() << "\n";
            std::cout << "Try again.\n";
        }
    }
}

void UIClass::listTrenchCoats() const
{
    std::vector<TrenchCoat> trench_coats_in_repository = admin_service.getTrenchCoats();

    for (const auto &trench_coat: trench_coats_in_repository)
    {
        std::cout << "\n";
        std::cout << "Trench coat id: " << trench_coat.getId() << '\n';
        std::cout << "Size: " << trench_coat.getSize() << '\n';
        std::cout << "Colour: " << trench_coat.getColour() << '\n';
        std::cout << "Price: " << trench_coat.getPrice() << '\n';
        std::cout << "Quantity: " << trench_coat.getQuantity() << '\n';
        std::cout << "Photograph: " << trench_coat.getPhotoLink() << '\n';
    }
}

void UIClass::updateTrenchCoat()
{
    listTrenchCoats();
    std::cout << "Please enter the trench coat id you want to update.\n";
    while (true)
    {
        try
        {
            int trench_coat_id = this->readInteger("Trench coat id: ");
            std::string size = this->readClothingSize("Size: ");
            std::string colour = this->readString("Colour: ");
            double price = this->readDouble("Price: ");
            int quantity = this->readInteger("Quantity: ");
            std::string photo_link = this->readString("Photograph: ");
            this->admin_service.updateTrenchCoatFromRepositoryById(trench_coat_id, size, colour, price, quantity,
                                                                   photo_link);
            break;
        }
        catch (const AdminTrenchCoatServiceException &update_exception)
        {
            std::cout << "\nCould not update the trench coat:\n";
            std::cout << update_exception.what() << "\n";
            std::cout << "Try again.\n";
        }
        catch (const TrenchCoatException &creation_exception)
        {
            std::cout << "\nCould not update the trench coat:\n";
            std::cout << creation_exception;
            std::cout << "Try again.\n";
        }
    }
}

void UIClass::run()
{

    int choice;
    do
    {
        std::cout << "Welcome to the trench coat app!\n";
        std::cout << "How would you like to open the app?\n";
        std::cout << "1. Administrator mode.\n";
        std::cout << "2. User mode.\n";
        std::cout << "0. Exit.\n";
        choice = this->readInteger("> ");
        switch (choice)
        {
            case ADMIN_MODE:
            {
                this->runAdministratorInterface();
                break;
            }
            case USER_MODE:
            {
                this->runUserInterface();
                break;
            }
            case EXIT_MENU:
                break;
            default:
                std::cout << "Invalid input. Try again.\n";
        }
    } while (choice != EXIT_MENU);

}

void UIClass::saveShoppingBasketToFile()
{
    std::cout << "Saving the trench coats to the current path (file shopping_basket).\n";
    try
    {
        this->user_service.saveShoppingBasketToFile();
    }
    catch (FileException& file_exception)
    {
        std::cout << file_exception.what();
    }
}

void UIClass::openShoppingBasketFile()
{
    std::cout << "Opening...\n";
    this->user_service.openShoppingBasketFile();
}
