/********************************************************************************
** Form generated from reading UI file 'lineselection.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LINESELECTION_H
#define UI_LINESELECTION_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QVBoxLayout>
#include "QVTKWidget.h"

QT_BEGIN_NAMESPACE

class Ui_Dialog
{
public:
    QGridLayout *gridLayout;
    QVTKWidget *imageWidget;
    QGroupBox *linesGroupBox;
    QVBoxLayout *verticalLayout;
    QRadioButton *redRadioButton;
    QRadioButton *blueRadioButton;
    QRadioButton *greenRadioButton;
    QRadioButton *cyanRadioButton;
    QRadioButton *magentaRadioButton;
    QRadioButton *yellowRadioButton;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QStringLiteral("Dialog"));
        Dialog->resize(640, 480);
        gridLayout = new QGridLayout(Dialog);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        imageWidget = new QVTKWidget(Dialog);
        imageWidget->setObjectName(QStringLiteral("imageWidget"));
        imageWidget->setMinimumSize(QSize(400, 400));

        gridLayout->addWidget(imageWidget, 0, 0, 1, 1);

        linesGroupBox = new QGroupBox(Dialog);
        linesGroupBox->setObjectName(QStringLiteral("linesGroupBox"));
        verticalLayout = new QVBoxLayout(linesGroupBox);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        redRadioButton = new QRadioButton(linesGroupBox);
        redRadioButton->setObjectName(QStringLiteral("redRadioButton"));

        verticalLayout->addWidget(redRadioButton);

        blueRadioButton = new QRadioButton(linesGroupBox);
        blueRadioButton->setObjectName(QStringLiteral("blueRadioButton"));

        verticalLayout->addWidget(blueRadioButton);

        greenRadioButton = new QRadioButton(linesGroupBox);
        greenRadioButton->setObjectName(QStringLiteral("greenRadioButton"));

        verticalLayout->addWidget(greenRadioButton);

        cyanRadioButton = new QRadioButton(linesGroupBox);
        cyanRadioButton->setObjectName(QStringLiteral("cyanRadioButton"));

        verticalLayout->addWidget(cyanRadioButton);

        magentaRadioButton = new QRadioButton(linesGroupBox);
        magentaRadioButton->setObjectName(QStringLiteral("magentaRadioButton"));

        verticalLayout->addWidget(magentaRadioButton);

        yellowRadioButton = new QRadioButton(linesGroupBox);
        yellowRadioButton->setObjectName(QStringLiteral("yellowRadioButton"));

        verticalLayout->addWidget(yellowRadioButton);


        gridLayout->addWidget(linesGroupBox, 0, 1, 1, 1);

        buttonBox = new QDialogButtonBox(Dialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout->addWidget(buttonBox, 1, 0, 1, 2);


        retranslateUi(Dialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), Dialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), Dialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QApplication::translate("Dialog", "Dialog", Q_NULLPTR));
        linesGroupBox->setTitle(QApplication::translate("Dialog", "L\303\255nea", Q_NULLPTR));
        redRadioButton->setText(QApplication::translate("Dialog", "Rojo", Q_NULLPTR));
        blueRadioButton->setText(QApplication::translate("Dialog", "Azul", Q_NULLPTR));
        greenRadioButton->setText(QApplication::translate("Dialog", "Verde", Q_NULLPTR));
        cyanRadioButton->setText(QApplication::translate("Dialog", "Cyan", Q_NULLPTR));
        magentaRadioButton->setText(QApplication::translate("Dialog", "Magenta", Q_NULLPTR));
        yellowRadioButton->setText(QApplication::translate("Dialog", "Amarillo", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LINESELECTION_H
