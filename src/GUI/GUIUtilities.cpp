//
// Created by Alex on 17.05.2023.
//

#include <QLayout>
#include <QPushButton>
#include "../../include/GUI/GUIUtilities.h"

namespace
{
    const int kButtonFontSize = 30;
    const QString kButtonFontFamily = "Georgia";
    const QFont kButtonFont{kButtonFontFamily, kButtonFontSize};
    const QString buttonStyle = "QPushButton {"
                                "background-color: #262626;"
                                "border: 2px solid #303030;"
                                "border-radius: 16px;"
                                "padding: 3px;"
                                "}"
                                "QPushButton:pressed {"
                                "background-color: #414141;"
                                "}";
}

void removeAllWidgetsFromLayout(QLayout *layout) // NOLINT(misc-no-recursion)
{
    QLayoutItem *child;
    while ((child = layout->takeAt(0)) != nullptr)
    {
        if (child->layout() != nullptr)
        {
            removeAllWidgetsFromLayout(child->layout());
        }
        else if (child->widget() != nullptr)
        {
            delete child->widget();
        }
        else
        {
            delete child;
        }
    }

}

QPushButton* buttonSetup(const QString &text)
{
    auto* button = new QPushButton{text};
    button->setStyleSheet(buttonStyle);
    button->setFont(kButtonFont);
    return button;
}