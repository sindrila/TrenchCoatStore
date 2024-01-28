//
// Created by Alex on 17.05.2023.
//
#pragma once

#ifndef A89_915_MINDRILA_MIHAIL_ADMINGUI_H
#define A89_915_MINDRILA_MIHAIL_ADMINGUI_H

#include <QWidget>
#include <QFormLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QListWidget>
#include "../Services/AdministratorTrenchCoatService.h"

class AdminGUI : public QWidget
{
    Q_OBJECT
private:
    AdministratorTrenchCoatService &adminService;
public:
    explicit AdminGUI(AdministratorTrenchCoatService &givenAdminService, QWidget *parent = nullptr);
private:
    QHBoxLayout* adminMainLayout;
    QListWidget* trenchCoatListWidget{};

//    QLineEdit* idLineEdit{};
    QLineEdit* sizeLineEdit{};
    QLineEdit* colourLineEdit{};
    QLineEdit* priceLineEdit{};
    QLineEdit* quantityLineEdit{};
    QLineEdit* photoLinkLineEdit{};
    QPushButton* addButton{};
    QPushButton* removeButton{};
    QPushButton* updateButton{};

    void populateList();
    void initAdminGUI();
    void connectSignalsAndSlots();
    int getSelectedIndex();
};


#endif //A89_915_MINDRILA_MIHAIL_ADMINGUI_H
