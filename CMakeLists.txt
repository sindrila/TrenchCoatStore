cmake_minimum_required(VERSION 3.25)
project(TrenchCoatStore)

set(CMAKE_CXX_STANDARD 14)

include_directories(Domain)
include_directories(Repositories)
include_directories(Services)

find_package(OpenCV REQUIRED)
include_directories(/opt/homebrew/Cellar/opencv/4.8.1_2/include/opencv4)
find_package(CURL REQUIRED)
include_directories(${CURL_INCLUDE_DIR})

set(CMAKE_PREFIX_PATH /Users/Alex/Qt/6.5.0/macos/lib/cmake)
find_package(Qt6 COMPONENTS Widgets REQUIRED PATHS /Users/Alex/Qt/6.5.0/macos/lib/cmake)
find_package(Qt6 COMPONENTS Widgets Network REQUIRED) # Add Network component here


set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

add_executable(TrenchCoatStore
        include/Domain/IdGenerator.h
        src/Domain/TrenchCoat.cpp
        include/Domain/TrenchCoat.h
        src/main.cpp include/Repositories/TrenchCoatRepository.h
        src/Repositories/TrenchCoatRepository.cpp
        include/Repositories/TrenchCoatRepositoryException.h
        include/Services/AdministratorTrenchCoatService.h
        src/Services/AdministratorTrenchCoatService.cpp
        include/Services/AdminTrenchCoatServiceException.h
        src/UI/UIClass.cpp include/Services/UserTrenchCoatService.h
        src/Services/UserTrenchCoatService.cpp
        src/Tests/TestFunctions.cpp
        include/Tests/TestFunctions.h
        src/Domain/TrenchCoatValidator.cpp
        include/Domain/TrenchCoatValidator.h
        utils/Utilities.cpp
        utils/Utilities.h
        include/Repositories/FileShoppingBasket.h
        src/Repositories/CSVShoppingBasket.cpp
        include/Repositories/CSVShoppingBasket.h
        src/Repositories/FileException.cpp
        include/Repositories/FileException.h
        src/Repositories/ShoppingBasket.cpp
        include/Repositories/ShoppingBasket.h
        src/Repositories/HTMLShoppingBasket.cpp
        include/Repositories/HTMLShoppingBasket.h src/GUI/MainMenuGUI.cpp include/GUI/MainMenuGUI.h src/GUI/AdminGUI.cpp include/GUI/AdminGUI.h src/GUI/GUIUtilities.cpp include/GUI/GUIUtilities.h src/Repositories/FakeTrenchCoatRepository.cpp include/Repositories/FakeTrenchCoatRepository.h src/Domain/FakeTrenchCoatValidator.cpp include/Domain/FakeTrenchCoatValidator.h src/GUI/UserGUI.cpp include/GUI/UserGUI.h src/GUI/usergui.ui)


target_link_libraries(TrenchCoatStore ${OpenCV_LIBS})
target_link_libraries(TrenchCoatStore ${CURL_LIBRARIES})

target_link_libraries(TrenchCoatStore Qt6::Widgets)
target_link_libraries(TrenchCoatStore Qt6::Network)
