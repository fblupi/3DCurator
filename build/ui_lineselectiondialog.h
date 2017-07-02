/********************************************************************************
** Form generated from reading UI file 'lineselectiondialog.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LINESELECTIONDIALOG_H
#define UI_LINESELECTIONDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_LineSelectionDialog
{
public:
    QGridLayout *gridLayout;
    QLabel *image;
    QGroupBox *linesGroupBox;
    QVBoxLayout *verticalLayout;
    QRadioButton *redRadioButton;
    QRadioButton *blueRadioButton;
    QRadioButton *greenRadioButton;
    QRadioButton *cyanRadioButton;
    QRadioButton *magentaRadioButton;
    QRadioButton *yellowRadioButton;
    QSpacerItem *verticalSpacer;
    QSpacerItem *horizontalSpacer;
    QPushButton *cancelButton;
    QPushButton *okButton;

    void setupUi(QDialog *LineSelectionDialog)
    {
        if (LineSelectionDialog->objectName().isEmpty())
            LineSelectionDialog->setObjectName(QStringLiteral("LineSelectionDialog"));
        LineSelectionDialog->resize(609, 547);
        LineSelectionDialog->setMaximumSize(QSize(609, 547));
        gridLayout = new QGridLayout(LineSelectionDialog);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        image = new QLabel(LineSelectionDialog);
        image->setObjectName(QStringLiteral("image"));
        image->setMinimumSize(QSize(500, 500));
        image->setMaximumSize(QSize(500, 500));

        gridLayout->addWidget(image, 0, 0, 2, 2);

        linesGroupBox = new QGroupBox(LineSelectionDialog);
        linesGroupBox->setObjectName(QStringLiteral("linesGroupBox"));
        linesGroupBox->setMaximumSize(QSize(100, 16777215));
        verticalLayout = new QVBoxLayout(linesGroupBox);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        redRadioButton = new QRadioButton(linesGroupBox);
        redRadioButton->setObjectName(QStringLiteral("redRadioButton"));
        redRadioButton->setChecked(true);

        verticalLayout->addWidget(redRadioButton);

        blueRadioButton = new QRadioButton(linesGroupBox);
        blueRadioButton->setObjectName(QStringLiteral("blueRadioButton"));
        blueRadioButton->setChecked(false);

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


        gridLayout->addWidget(linesGroupBox, 0, 2, 1, 1);

        verticalSpacer = new QSpacerItem(20, 326, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 1, 2, 1, 1);

        horizontalSpacer = new QSpacerItem(416, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 2, 0, 1, 1);

        cancelButton = new QPushButton(LineSelectionDialog);
        cancelButton->setObjectName(QStringLiteral("cancelButton"));

        gridLayout->addWidget(cancelButton, 2, 1, 1, 1);

        okButton = new QPushButton(LineSelectionDialog);
        okButton->setObjectName(QStringLiteral("okButton"));

        gridLayout->addWidget(okButton, 2, 2, 1, 1);


        retranslateUi(LineSelectionDialog);

        QMetaObject::connectSlotsByName(LineSelectionDialog);
    } // setupUi

    void retranslateUi(QDialog *LineSelectionDialog)
    {
        LineSelectionDialog->setWindowTitle(QApplication::translate("LineSelectionDialog", "Dialog", Q_NULLPTR));
        image->setText(QString());
        linesGroupBox->setTitle(QApplication::translate("LineSelectionDialog", "L\303\255nea", Q_NULLPTR));
        redRadioButton->setText(QApplication::translate("LineSelectionDialog", "Rojo", Q_NULLPTR));
        blueRadioButton->setText(QApplication::translate("LineSelectionDialog", "Azul", Q_NULLPTR));
        greenRadioButton->setText(QApplication::translate("LineSelectionDialog", "Verde", Q_NULLPTR));
        cyanRadioButton->setText(QApplication::translate("LineSelectionDialog", "Cyan", Q_NULLPTR));
        magentaRadioButton->setText(QApplication::translate("LineSelectionDialog", "Magenta", Q_NULLPTR));
        yellowRadioButton->setText(QApplication::translate("LineSelectionDialog", "Amarillo", Q_NULLPTR));
        cancelButton->setText(QApplication::translate("LineSelectionDialog", "Cancelar", Q_NULLPTR));
        okButton->setText(QApplication::translate("LineSelectionDialog", "OK", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class LineSelectionDialog: public Ui_LineSelectionDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LINESELECTIONDIALOG_H
