//
// Created by Alex on 17.05.2023.
//

#ifndef A89_915_MINDRILA_MIHAIL_MAINMENUGUI_H
#define A89_915_MINDRILA_MIHAIL_MAINMENUGUI_H

#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QListWidget>
#include <QLabel>
#include "../Services/AdministratorTrenchCoatService.h"
#include "../Services/UserTrenchCoatService.h"
#include <QComboBox>
class MainMenuGUI : public QWidget
{
    Q_OBJECT
private:
    AdministratorTrenchCoatService &admin_service;
    UserTrenchCoatService &user_service;
public:
    MainMenuGUI(AdministratorTrenchCoatService &admin_service, UserTrenchCoatService &user_service, QWidget *parent = nullptr);
private:
    QVBoxLayout* mainLayout;
    QLabel* mainTitle{};
    QPushButton* adminButton{};
    QPushButton* userButton{};
    QPushButton* nextButton{};
    QComboBox* fileTypeComboBox{};
    QComboBox* sizeOfTrenchCoatsComboBox{};

    void initMainMenuGUI();
    void connectSignalsAndSlots();
    void showFileTypeComboBox();
public slots:
    void onAdminButtonClicked();
    void onUserButtonClicked();
    void hideMainMenu();
    void showUserMenu();
};


#endif //A89_915_MINDRILA_MIHAIL_MAINMENUGUI_H
