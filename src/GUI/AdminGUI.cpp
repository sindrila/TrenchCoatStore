//
// Created by Alex on 17.05.2023.
//

#include <QLineEdit>
#include <QFormLayout>
#include <sstream>
#include <QMessageBox>
#include "../../include/GUI/GUIUtilities.h"
#include "../../include/GUI/AdminGUI.h"
#include "../../include/Services/AdminTrenchCoatServiceException.h"
#include <QApplication>
#include <QScreen>
#include <QHBoxLayout>
AdminGUI::AdminGUI(AdministratorTrenchCoatService &givenAdminService, QWidget *parent) : adminService(givenAdminService), QWidget(parent)
{
    adminMainLayout = new QHBoxLayout{this};
    setLayout(adminMainLayout);
    this->initAdminGUI();
}

void AdminGUI::populateList()
{
    this->trenchCoatListWidget->clear();
    trenchCoatListWidget->setMinimumSize(700, 100);
    trenchCoatListWidget->setSpacing(2);
    std::vector<TrenchCoat> trenchCoats = this->adminService.getTrenchCoats();

    QFont itemFont{"Andale Mono", 18, QFont::Thin};
    for (const auto& trenchCoat : trenchCoats)
    {
        std::stringstream buffer;
        buffer << "ID: " << trenchCoat.getId() << " | Size: " << trenchCoat.getSize() << " | Colour: " << trenchCoat.getColour() << " | Price: " << trenchCoat.getPrice() << " | Quantity: " << trenchCoat.getQuantity();
        auto *item = new QListWidgetItem{QString::fromStdString(buffer.str())};
        item->setFont(itemFont);
        trenchCoatListWidget->addItem(item);
    }
}

int AdminGUI::getSelectedIndex()
{
    QModelIndexList indexList = this->trenchCoatListWidget->selectionModel()->selectedIndexes();
    if (indexList.empty())
        return -1;
    int index = indexList.at(0).row();
    return index;
}

void AdminGUI::initAdminGUI()
{
    trenchCoatListWidget = new QListWidget{};
    this->populateList();
    adminMainLayout->addWidget(this->trenchCoatListWidget);
    auto* buttonsLayout = new QGridLayout{};
    addButton = buttonSetup("Add");
    addButton->setMinimumSize(100, 50);
    removeButton = buttonSetup("Remove");
    removeButton->setMinimumSize(150, 50);
    updateButton = buttonSetup("Update");
    updateButton->setMinimumSize(150, 50);
    buttonsLayout->addWidget(addButton, 0, 0);
    buttonsLayout->addWidget(removeButton, 0, 1);
    buttonsLayout->addWidget(updateButton, 0, 2);

    QFormLayout* sizeFormLayout;
    QFormLayout* colourFormLayout;
    QFormLayout* priceFormLayout;
    QFormLayout* quantityFormLayout;
    QFormLayout* photoLinkFormLayout;

    QFont lineEditFont{"Georgia" ,20, QFont::Thin};
    QFont formLayoutFont{"Georgia" ,20, QFont::Thin};
    auto* formLayout = new QVBoxLayout{};
    sizeLineEdit = new QLineEdit{};
    sizeLineEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    sizeLineEdit->setMinimumHeight(30);
    sizeLineEdit->setFont(lineEditFont);
    sizeFormLayout = new QFormLayout{};
    sizeFormLayout->addRow("Size:", sizeLineEdit);
    sizeFormLayout->labelForField(sizeLineEdit)->setFont(formLayoutFont);
    sizeFormLayout->setFieldGrowthPolicy(QFormLayout::ExpandingFieldsGrow);
    sizeFormLayout->setVerticalSpacing(10);
    formLayout->addLayout(sizeFormLayout);

    colourLineEdit = new QLineEdit{};
    colourLineEdit->setFont(lineEditFont);
    colourLineEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    colourLineEdit->setMinimumHeight(30);
    colourFormLayout = new QFormLayout{};
    colourFormLayout->addRow("Colour:", colourLineEdit);
    colourFormLayout->labelForField(colourLineEdit)->setFont(formLayoutFont);
    colourFormLayout->setFieldGrowthPolicy(QFormLayout::ExpandingFieldsGrow);
    colourFormLayout->setVerticalSpacing(10);
    formLayout->addLayout(colourFormLayout);

    priceLineEdit = new QLineEdit{};
    priceLineEdit->setFont(lineEditFont);
    priceLineEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    priceLineEdit->setMinimumHeight(30);
    priceFormLayout = new QFormLayout{};
    priceFormLayout->addRow("Price:", priceLineEdit);
    priceFormLayout->labelForField(priceLineEdit)->setFont(formLayoutFont);
    priceFormLayout->setFieldGrowthPolicy(QFormLayout::ExpandingFieldsGrow);
    priceFormLayout->setVerticalSpacing(10);
    formLayout->addLayout(priceFormLayout);

    quantityLineEdit = new QLineEdit{};
    quantityLineEdit->setFont(lineEditFont);
    quantityLineEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    quantityLineEdit->setMinimumHeight(30);
    quantityFormLayout = new QFormLayout{};
    quantityFormLayout->addRow("Quantity:", quantityLineEdit);
    quantityFormLayout->labelForField(quantityLineEdit)->setFont(formLayoutFont);
    quantityFormLayout->setFieldGrowthPolicy(QFormLayout::ExpandingFieldsGrow);
    quantityFormLayout->setVerticalSpacing(10);
    formLayout->addLayout(quantityFormLayout);

    photoLinkLineEdit = new QLineEdit{};
    photoLinkLineEdit->setFont(lineEditFont);
    photoLinkLineEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    photoLinkLineEdit->setMinimumHeight(30);
    photoLinkFormLayout = new QFormLayout{};
    photoLinkFormLayout->addRow("Photo Link:", photoLinkLineEdit);
    photoLinkFormLayout->labelForField(photoLinkLineEdit)->setFont(formLayoutFont);
    photoLinkFormLayout->setFieldGrowthPolicy(QFormLayout::ExpandingFieldsGrow);
    photoLinkFormLayout->setVerticalSpacing(10);
    formLayout->addLayout(photoLinkFormLayout);
    formLayout->addLayout(buttonsLayout);
    this->adminMainLayout->addLayout(formLayout);

    this->connectSignalsAndSlots();
    QRect screenGeometry = QApplication::screens().at(0)->geometry();
    int x = (screenGeometry.width() - this->adminMainLayout->sizeHint().width()) / 2;
    int y = (screenGeometry.height() - this->adminMainLayout->sizeHint().height()) / 2;
    this->setGeometry(x, y, this->adminMainLayout->sizeHint().width(), this->adminMainLayout->sizeHint().height());
    this->setWindowTitle("Admin");
}
void AdminGUI::connectSignalsAndSlots()
{
    QObject::connect(trenchCoatListWidget, &QListWidget::clicked, this, [&]()
    {
        int index = getSelectedIndex();

        auto trenchCoat = this->adminService.getTrenchCoats()[index];
         this->sizeLineEdit->setText(QString::fromStdString(trenchCoat.getSize()));
         this->colourLineEdit->setText(QString::fromStdString(trenchCoat.getColour()));
         this->priceLineEdit->setText(QString::number(trenchCoat.getPrice()));
         this->quantityLineEdit->setText(QString::number(trenchCoat.getQuantity()));
        this->photoLinkLineEdit->setText(QString::fromStdString(trenchCoat.getPhotoLink()));
    });
    QObject::connect(addButton, &QPushButton::clicked, this, [&]()
    {
        try
        {
            this->adminService.addTrenchCoatToRepository(this->sizeLineEdit->text().toStdString(), this->colourLineEdit->text().toStdString(), this->priceLineEdit->text().toDouble(), this->quantityLineEdit->text().toInt(), this->photoLinkLineEdit->text().toStdString());
            this->populateList();
            this->trenchCoatListWidget->setCurrentRow(int(this->adminService.getTrenchCoats().size() - 1));
        }
        catch (const AdminTrenchCoatServiceException& e)
        {
            QMessageBox::critical(this, "Error", e.what());
        }
        catch (const TrenchCoatException& e)
        {
            std::stringstream buffer;
            buffer << e;
            QMessageBox::critical(this, "Error", QString::fromStdString(buffer.str()));
        }
    });
    QObject::connect(removeButton, &QPushButton::clicked, this, [&]()
    {
        try
        {
            int index = getSelectedIndex();
            auto trenchCoatToRemove = this->adminService.getTrenchCoats()[index];
            this->adminService.removeTrenchCoatFromRepositoryById(trenchCoatToRemove.getId());
            this->populateList();
        }
        catch (const AdminTrenchCoatServiceException& e)
        {
            QMessageBox::critical(this, "Error", e.what());
        }
    });
    QObject::connect(updateButton, &QPushButton::clicked, this, [&]()
    {
        try
        {
            int index = getSelectedIndex();
            auto trenchCoatToUpdate = this->adminService.getTrenchCoats()[index];
            this->adminService.updateTrenchCoatFromRepositoryById(trenchCoatToUpdate.getId(), this->sizeLineEdit->text().toStdString(), this->colourLineEdit->text().toStdString(), this->priceLineEdit->text().toDouble(), this->quantityLineEdit->text().toInt(), this->photoLinkLineEdit->text().toStdString());
            this->populateList();
            this->trenchCoatListWidget->setCurrentRow(index);
        }
        catch (const AdminTrenchCoatServiceException& e)
        {
            QMessageBox::critical(this, "Error", e.what());
        }
        catch (const TrenchCoatException& e)
        {
            std::stringstream buffer;
            buffer << e;
            QMessageBox::critical(this, "Error", QString::fromStdString(buffer.str()));
        }
    });
}