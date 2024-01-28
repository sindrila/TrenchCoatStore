//
// Created by Alex on 17.05.2023.
//

#include "../../include/GUI/MainMenuGUI.h"
#include <QHBoxLayout>
#include <QLabel>
#include <QFont>
#include <QPushButton>
#include <memory>
#include <QLineEdit>
#include "../../include/GUI/GUIUtilities.h"
#include "../../include/GUI/AdminGUI.h"
#include "../../include/GUI/UserGUI.h"

namespace
{
    const int kTitleLeftMargin = 20;
    const int kTitleRightMargin = 20;
    const int kTitleTopMargin = 0;
    const int kTitleBottomMargin = 0;
    const int kTitleFontSize = 73;
    const QString kTitleFontFamily = "Bodoni 72 Smallcaps";
    const QFont kMainTitleFont{kTitleFontFamily, kTitleFontSize, QFont::Bold};

}

MainMenuGUI::MainMenuGUI(AdministratorTrenchCoatService &admin_service, UserTrenchCoatService &user_service, QWidget *parent)
        : admin_service(admin_service), user_service(user_service), QWidget(parent)
{
    this->mainLayout = new QVBoxLayout{this};
    initMainMenuGUI();
}

void MainMenuGUI::initMainMenuGUI()
{
    mainTitle = new QLabel{"CHERRY KIWI\nTrench Coat Store"};
    mainTitle->setFont(kMainTitleFont);
    mainTitle->setContentsMargins(kTitleLeftMargin, kTitleTopMargin, kTitleRightMargin, kTitleBottomMargin);
    mainTitle->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(mainTitle);

    auto *accessModeButtons = new QHBoxLayout{};
    adminButton = buttonSetup("Administrator");
    userButton = buttonSetup("User");
    accessModeButtons->addWidget(adminButton);
    accessModeButtons->addWidget(userButton);
    mainLayout->addLayout(accessModeButtons);

    this->connectSignalsAndSlots();
}

void MainMenuGUI::connectSignalsAndSlots()
{
    connect(adminButton, &QPushButton::clicked, this, &MainMenuGUI::hideMainMenu);
    connect(adminButton, &QPushButton::clicked, this, &MainMenuGUI::onAdminButtonClicked);
    connect(userButton, &QPushButton::clicked, this, &MainMenuGUI::onUserButtonClicked);
}


void MainMenuGUI::onAdminButtonClicked()
{
    auto* adminGUI = new AdminGUI{admin_service};
    adminGUI->show();
    this->show();
}


void MainMenuGUI::onUserButtonClicked()
{
    this->showFileTypeComboBox();

    connect(nextButton, &QPushButton::clicked, this, &MainMenuGUI::showUserMenu);
}

void MainMenuGUI::hideMainMenu()
{
    this->hide();
}

void MainMenuGUI::showFileTypeComboBox()
{
    delete this->userButton;
    delete this->adminButton;
    fileTypeComboBox = new QComboBox();
    fileTypeComboBox->addItem(QString::fromStdString("HTML"));
    fileTypeComboBox->addItem(QString::fromStdString("CSV"));
    const QString comboBoxStyle = ("QComboBox {"
                                   "background-color: #262626;"
                                   "border: 2px solid #303030;"
                                   "border-radius: 16px;"
                                   "padding: 3px;"
                                   "}");
    fileTypeComboBox->setStyleSheet(comboBoxStyle);
    fileTypeComboBox->setFont(QFont{"Georgia", 30});
    nextButton = buttonSetup("Enter shop");
    sizeOfTrenchCoatsComboBox = new QComboBox();
    sizeOfTrenchCoatsComboBox->addItem(("All sizes."));
    sizeOfTrenchCoatsComboBox->addItem(("XS"));
    sizeOfTrenchCoatsComboBox->addItem(("S"));
    sizeOfTrenchCoatsComboBox->addItem(("M"));
    sizeOfTrenchCoatsComboBox->addItem(("L"));
    sizeOfTrenchCoatsComboBox->addItem(("XL"));
    sizeOfTrenchCoatsComboBox->addItem(("XXL"));
    sizeOfTrenchCoatsComboBox->addItem(("3XL"));

    mainLayout->addWidget(fileTypeComboBox);
    mainLayout->addWidget(sizeOfTrenchCoatsComboBox);
    mainLayout->addWidget(nextButton);
}

void MainMenuGUI::showUserMenu()
{
    std::string typeOfFile = fileTypeComboBox->currentText().toStdString();
    std::string sizeOfTrenchCoatsToShow = sizeOfTrenchCoatsComboBox->currentText().toStdString();
    auto* userGUI = new UserGUI(sizeOfTrenchCoatsToShow, this->user_service, typeOfFile);
    userGUI->show();
}




