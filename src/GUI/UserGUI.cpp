//
// Created by Alex on 28.05.2023.
//

// You may need to build the project (run Qt uic code generator) to get "ui_UserGUI.h" resolved

#include "../../include/GUI/usergui.h"
#include "ui_UserGUI.h"
#include "../../include/Repositories/HTMLShoppingBasket.h"
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QByteArray>
#include <QImage>
#include <QPixmap>
#include "../../include/Repositories/CSVShoppingBasket.h"
#include <utility>


UserGUI::UserGUI(std::string givenSizeOfTrenchCoatsToShow, UserTrenchCoatService &givenService,
                 std::string givenTypeOfSaveFile, QWidget *parent) :
        QWidget(parent), ui(new Ui::UserGUI), typeOfSaveFile(std::move(givenTypeOfSaveFile)), userService(givenService),
        sizeOfTrenchCoatsToShow(std::move(givenSizeOfTrenchCoatsToShow))
{
    ui->setupUi(this);

    if (typeOfSaveFile == "HTML") {
        shopping_basket = std::make_unique<HTMLShoppingBasket>("shopping_carts.html");
    }
    else
        shopping_basket = std::make_unique<CSVShoppingBasket>("shopping_carts.csv");

    this->userService.setFileShoppingBasket(shopping_basket.get());
    this->showStorefront();
    this->connectSignalsAndSlots();
}

UserGUI::~UserGUI()
{
    delete ui;
}

void UserGUI::showTrenchCoatImage(const TrenchCoat &trenchCoatToShow)
{
    auto *manager = new QNetworkAccessManager(this);
    QNetworkRequest request(QUrl(QString::fromStdString(trenchCoatToShow.getPhotoLink())));
    QNetworkReply *reply = manager->get(request);

    connect(reply, &QNetworkReply::finished, this, [this, reply, trenchCoatToShow]
    {
        if (reply->error() == QNetworkReply::NoError) {
            QByteArray data = reply->readAll();
            QImage image;
            image.loadFromData(data);

            int newWidth = 500;
            int newHeight = static_cast<int>(newWidth * (image.height() / image.width()));

            QImage resizedImage = image.scaled(QSize(newWidth, newHeight), Qt::KeepAspectRatio,
                                               Qt::SmoothTransformation);


            QPixmap pixmap = QPixmap::fromImage(resizedImage);
            ui->trenchCoatImageLabel->setPixmap(pixmap);
        } else {
            auto errorFont = QFont("Georgia", 30);
            auto errorMessage = QString("Could not load photo.\nPlease check your internet connection.");

            ui->trenchCoatImageLabel->setText(errorMessage);
            ui->trenchCoatImageLabel->setFont(errorFont);
        }
        reply->deleteLater();
    });
}

void UserGUI::showNextTrenchCoatImageInRepository()
{
    TrenchCoat trenchCoatToShow = this->userService.getNextTrenchCoatInRepository();

    this->showTrenchCoatImage(trenchCoatToShow);
    this->ui->sizeDescriptionLabel->setText(QString::fromStdString(trenchCoatToShow.getSize()));
    this->ui->colourDescriptionLabel->setText(QString::fromStdString(trenchCoatToShow.getColour()));
    this->ui->priceDescriptionLabel->setText(QString::number(trenchCoatToShow.getPrice()));
}

void UserGUI::connectSignalsAndSlots()
{
    connect(this->ui->nextTrenchCoatPushButton, &QPushButton::clicked, this,
            &UserGUI::showNextTrenchCoatImageInRepository);
    connect(this->ui->addToCartButton, &QPushButton::clicked, this, &UserGUI::addCurrentTrenchCoatToShoppingBasket);
    connect(this->ui->shoppingCartButton, &QPushButton::clicked, this, &UserGUI::showShoppingCart);
    connect(this->ui->nextTrenchCoatInCartPushButton, &QPushButton::clicked, this,
            &UserGUI::showNextTrenchCoatInShoppingCart);
    connect(this->ui->backToStorePushButton, &QPushButton::clicked, this, &UserGUI::showStorefront);
    connect(this->ui->openShoppingCartInAppPushButton, &QPushButton::clicked, this, &UserGUI::openShoppingCartInApp);
}

void UserGUI::addCurrentTrenchCoatToShoppingBasket()
{
    this->userService.addCurrentTrenchCoatToShoppingCart();
    this->ui->totalCostDescriptionLabel->setText(QString::number(this->userService.getCurrentPriceInShoppingCart()));
}

void UserGUI::showShoppingCart()
{
    this->ui->storeFrontLabel->hide();
    this->ui->nextTrenchCoatPushButton->hide();
    this->ui->addToCartButton->hide();
    this->ui->shoppingCartButton->hide();
    this->ui->backToStorePushButton->show();

    if (this->userService.getNumberOfTrenchCoatsInShoppingCart() == 0) {
        this->ui->colourDescriptionLabel->setText("N/A");
        this->ui->priceDescriptionLabel->setText("N/A");
        this->ui->sizeDescriptionLabel->setText("N/A");
        this->ui->totalCostDescriptionLabel->setText("0");
        this->ui->trenchCoatImageLabel->setText("Shopping\ncart\nempty.");

    } else {
        if (this->userService.getNumberOfTrenchCoatsInShoppingCart() != 1)
            this->ui->nextTrenchCoatInCartPushButton->show();
        this->showNextTrenchCoatInShoppingCart();
        this->ui->openShoppingCartInAppPushButton->show();
        this->ui->shoppingCartLabel->show();
    }

}

void UserGUI::showNextTrenchCoatInShoppingCart()
{
    TrenchCoat trenchCoatToShow = this->userService.getNextTrenchCoatInShoppingCart();

    this->showTrenchCoatImage(trenchCoatToShow);
    this->ui->sizeDescriptionLabel->setText(QString::fromStdString(trenchCoatToShow.getSize()));
    this->ui->colourDescriptionLabel->setText(QString::fromStdString(trenchCoatToShow.getColour()));
    this->ui->priceDescriptionLabel->setText(QString::number(trenchCoatToShow.getPrice()));
}

void UserGUI::showStorefront()
{

    this->ui->storeFrontLabel->show();
    this->ui->nextTrenchCoatPushButton->show();
    this->ui->addToCartButton->show();
    this->ui->shoppingCartButton->show();
    this->ui->shoppingCartLabel->show();
    this->ui->openShoppingCartInAppPushButton->hide();
    this->ui->nextTrenchCoatInCartPushButton->hide();
    this->ui->backToStorePushButton->hide();

    this->userService.setSizeOfTrenchCoatsToShow(sizeOfTrenchCoatsToShow);
    this->showNextTrenchCoatImageInRepository();
    this->ui->totalCostDescriptionLabel->setText(QString::number(this->userService.getCurrentPriceInShoppingCart()));
}

void UserGUI::openShoppingCartInApp()
{
    this->userService.openShoppingBasketFile();
}
