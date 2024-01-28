//
// Created by Alex on 28.05.2023.
//

#ifndef A89_915_MINDRILA_MIHAIL_USERGUI_H
#define A89_915_MINDRILA_MIHAIL_USERGUI_H

#include <QWidget>
#include "../Domain/TrenchCoat.h"
#include "../Services/UserTrenchCoatService.h"
#include "GUIUtilities.h"


QT_BEGIN_NAMESPACE
namespace Ui
{
    class UserGUI;
}
QT_END_NAMESPACE

class UserGUI : public QWidget
{
Q_OBJECT

public:
    explicit UserGUI(std::string  givenSizeOfTrenchCoatsToShow, UserTrenchCoatService& givenService, std::string  givenTypeOfSaveFile, QWidget *parent = nullptr);

    ~UserGUI() override;

private:
    UserTrenchCoatService& userService;
    std::string typeOfSaveFile;
    Ui::UserGUI *ui;
    std::unique_ptr<FileShoppingBasket> shopping_basket;
    void showTrenchCoatImage(const TrenchCoat& trenchCoatToShow);
    void connectSignalsAndSlots();
    std::string sizeOfTrenchCoatsToShow;
    void openShoppingCartInApp();

public slots:
    void showNextTrenchCoatImageInRepository();
    void addCurrentTrenchCoatToShoppingBasket();
    void showShoppingCart();
    void showStorefront();
    void showNextTrenchCoatInShoppingCart();
};


#endif //A89_915_MINDRILA_MIHAIL_USERGUI_H
