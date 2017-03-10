/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "QVTKWidget.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionOpenDICOM;
    QAction *actionExit;
    QAction *actionExportVolumeImage;
    QAction *actionExportSliceImage;
    QAction *actionImportPreset;
    QAction *actionExportPreset;
    QAction *actionDeleteVolumeParts;
    QAction *actionOpenDICOM_2;
    QAction *actionUpdateMesh;
    QAction *actionEnableDisablePlane;
    QAction *actionSagitalPlane;
    QAction *actionAxialPlane;
    QAction *actionCoronalPlane;
    QAction *actionWoodPreset;
    QAction *actionStuccoPreset;
    QAction *actionMetalPreset;
    QAction *actionCompletePreset;
    QAction *actionWoodMesh;
    QAction *actionStuccoMesh;
    QAction *actionMetalMesh;
    QAction *actionExtractMesh;
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *openDICOM;
    QSpacerItem *horizontalSpacer_10;
    QPushButton *deleteVolumeParts;
    QPushButton *exportVolumeImage;
    QGroupBox *rulesBox;
    QGridLayout *gridLayout_3;
    QPushButton *enableDisableSliceRule;
    QPushButton *addSliceRule;
    QSpacerItem *horizontalSpacer_11;
    QPushButton *deleteSliceRule;
    QListWidget *sliceRulesList;
    QPushButton *addVolumeRule;
    QListWidget *volumeRulesList;
    QPushButton *deleteVolumeRule;
    QPushButton *enableDisableVolumeRule;
    QSpacerItem *verticalSpacer_2;
    QSpacerItem *horizontalSpacer_12;
    QLabel *volumeRuleLabel;
    QLabel *sliceRuleLabel;
    QVTKWidget *volumeWidget;
    QLabel *labelFolder;
    QTabWidget *mainTab;
    QWidget *tabSlices;
    QVBoxLayout *verticalLayout_4;
    QGroupBox *planeOptions;
    QHBoxLayout *horizontalLayout;
    QPushButton *enableDisablePlane;
    QSpacerItem *horizontalSpacer_9;
    QPushButton *sagitalPlane;
    QPushButton *axialPlane;
    QPushButton *coronalPlane;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *exportSliceImage;
    QVTKWidget *slicesWidget;
    QLabel *coordsAndValueLabel;
    QWidget *tabTransferFunction;
    QGridLayout *gridLayout_84;
    QPushButton *exportPreset;
    QGroupBox *defaultPresetsBox;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_6;
    QPushButton *completePreset;
    QPushButton *woodPreset;
    QPushButton *stuccoPreset;
    QPushButton *metalPreset;
    QSpacerItem *horizontalSpacer_5;
    QLabel *labelTFName;
    QLabel *labelTFDescription;
    QLineEdit *tfDescription;
    QLineEdit *tfName;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QVBoxLayout *verticalLayout_5;
    QGroupBox *colorTFBox;
    QGridLayout *gridLayout_85;
    QSlider *colorTFMinSlider;
    QSlider *colorTFMaxSlider;
    QVTKWidget *colorTFWidget;
    QGroupBox *scalarTFBox;
    QGridLayout *gridLayout_87;
    QVTKWidget *scalarTFWidget;
    QSlider *scalarTFMinSlider;
    QSlider *scalarTFMaxSlider;
    QGroupBox *gradientTFBox;
    QGridLayout *gridLayout_88;
    QVTKWidget *gradientTFWidget;
    QSlider *gradientTFMinSlider;
    QSlider *gradientTFMaxSlider;
    QPushButton *importPreset;
    QWidget *extractMeshTab;
    QGridLayout *gridLayout_2;
    QPushButton *extractMesh;
    QSpacerItem *horizontalSpacer_8;
    QSlider *isoValueSlider;
    QGroupBox *extractMeshPresets;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer;
    QPushButton *extractMeshWood;
    QPushButton *extractMeshStucco;
    QPushButton *extractMeshMetal;
    QSpacerItem *horizontalSpacer_7;
    QVTKWidget *meshWidget;
    QWidget *tabProperties;
    QGridLayout *gridLayout_83;
    QGroupBox *materialProperties;
    QGridLayout *gridLayout_86;
    QDoubleSpinBox *diffuseValue;
    QLabel *specularLabel;
    QLabel *ambientLabel;
    QLabel *diffuseLabel;
    QDoubleSpinBox *ambientValue;
    QDoubleSpinBox *specularValue;
    QDoubleSpinBox *powerValue;
    QLabel *powerLabel;
    QSpacerItem *horizontalSpacer_13;
    QSpacerItem *horizontalSpacer_16;
    QSpacerItem *horizontalSpacer_14;
    QSpacerItem *horizontalSpacer_15;
    QPushButton *restoreMaterial;
    QPushButton *updateProperties;
    QSpacerItem *verticalSpacer;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_4;
    QLabel *meshBackgroundLabel;
    QPushButton *meshBackground;
    QPushButton *volumeDeletingBackground;
    QLabel *volumeBackgroundLabel;
    QPushButton *restoreBackgrounds;
    QPushButton *volumeBackground;
    QLabel *volumeDeletingBackgroundLabel;
    QSpacerItem *horizontalSpacer_17;
    QSpacerItem *horizontalSpacer_18;
    QSpacerItem *horizontalSpacer_19;
    QSpacerItem *horizontalSpacer_4;
    QSpacerItem *horizontalSpacer_3;
    QMenuBar *menuBar;
    QMenu *menuArchivo;
    QMenu *menuEditar;
    QMenu *menuHerramientas;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1143, 696);
        QIcon icon;
        icon.addFile(QStringLiteral(":/icons/3DCurator.png"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        actionOpenDICOM = new QAction(MainWindow);
        actionOpenDICOM->setObjectName(QStringLiteral("actionOpenDICOM"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/icons/folder.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionOpenDICOM->setIcon(icon1);
        actionOpenDICOM->setShortcutContext(Qt::WindowShortcut);
        actionExit = new QAction(MainWindow);
        actionExit->setObjectName(QStringLiteral("actionExit"));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/icons/power.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionExit->setIcon(icon2);
        actionExportVolumeImage = new QAction(MainWindow);
        actionExportVolumeImage->setObjectName(QStringLiteral("actionExportVolumeImage"));
        actionExportSliceImage = new QAction(MainWindow);
        actionExportSliceImage->setObjectName(QStringLiteral("actionExportSliceImage"));
        actionImportPreset = new QAction(MainWindow);
        actionImportPreset->setObjectName(QStringLiteral("actionImportPreset"));
        actionExportPreset = new QAction(MainWindow);
        actionExportPreset->setObjectName(QStringLiteral("actionExportPreset"));
        actionDeleteVolumeParts = new QAction(MainWindow);
        actionDeleteVolumeParts->setObjectName(QStringLiteral("actionDeleteVolumeParts"));
        actionOpenDICOM_2 = new QAction(MainWindow);
        actionOpenDICOM_2->setObjectName(QStringLiteral("actionOpenDICOM_2"));
        actionOpenDICOM_2->setIcon(icon1);
        actionUpdateMesh = new QAction(MainWindow);
        actionUpdateMesh->setObjectName(QStringLiteral("actionUpdateMesh"));
        actionEnableDisablePlane = new QAction(MainWindow);
        actionEnableDisablePlane->setObjectName(QStringLiteral("actionEnableDisablePlane"));
        actionSagitalPlane = new QAction(MainWindow);
        actionSagitalPlane->setObjectName(QStringLiteral("actionSagitalPlane"));
        actionAxialPlane = new QAction(MainWindow);
        actionAxialPlane->setObjectName(QStringLiteral("actionAxialPlane"));
        actionCoronalPlane = new QAction(MainWindow);
        actionCoronalPlane->setObjectName(QStringLiteral("actionCoronalPlane"));
        actionWoodPreset = new QAction(MainWindow);
        actionWoodPreset->setObjectName(QStringLiteral("actionWoodPreset"));
        actionStuccoPreset = new QAction(MainWindow);
        actionStuccoPreset->setObjectName(QStringLiteral("actionStuccoPreset"));
        actionMetalPreset = new QAction(MainWindow);
        actionMetalPreset->setObjectName(QStringLiteral("actionMetalPreset"));
        actionCompletePreset = new QAction(MainWindow);
        actionCompletePreset->setObjectName(QStringLiteral("actionCompletePreset"));
        actionWoodMesh = new QAction(MainWindow);
        actionWoodMesh->setObjectName(QStringLiteral("actionWoodMesh"));
        actionStuccoMesh = new QAction(MainWindow);
        actionStuccoMesh->setObjectName(QStringLiteral("actionStuccoMesh"));
        actionMetalMesh = new QAction(MainWindow);
        actionMetalMesh->setObjectName(QStringLiteral("actionMetalMesh"));
        actionExtractMesh = new QAction(MainWindow);
        actionExtractMesh->setObjectName(QStringLiteral("actionExtractMesh"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setMaximumSize(QSize(16777215, 62));
        groupBox->setFlat(false);
        horizontalLayout_4 = new QHBoxLayout(groupBox);
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        openDICOM = new QPushButton(groupBox);
        openDICOM->setObjectName(QStringLiteral("openDICOM"));
        openDICOM->setIcon(icon1);
        openDICOM->setIconSize(QSize(21, 21));

        horizontalLayout_4->addWidget(openDICOM);

        horizontalSpacer_10 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_10);

        deleteVolumeParts = new QPushButton(groupBox);
        deleteVolumeParts->setObjectName(QStringLiteral("deleteVolumeParts"));
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/icons/eraser.png"), QSize(), QIcon::Normal, QIcon::Off);
        deleteVolumeParts->setIcon(icon3);
        deleteVolumeParts->setIconSize(QSize(21, 21));

        horizontalLayout_4->addWidget(deleteVolumeParts);

        exportVolumeImage = new QPushButton(groupBox);
        exportVolumeImage->setObjectName(QStringLiteral("exportVolumeImage"));
        QIcon icon4;
        icon4.addFile(QStringLiteral(":/icons/save.png"), QSize(), QIcon::Normal, QIcon::Off);
        exportVolumeImage->setIcon(icon4);
        exportVolumeImage->setIconSize(QSize(21, 21));

        horizontalLayout_4->addWidget(exportVolumeImage);


        gridLayout->addWidget(groupBox, 0, 0, 1, 1);

        rulesBox = new QGroupBox(centralWidget);
        rulesBox->setObjectName(QStringLiteral("rulesBox"));
        rulesBox->setMinimumSize(QSize(160, 0));
        rulesBox->setMaximumSize(QSize(160, 16777215));
        gridLayout_3 = new QGridLayout(rulesBox);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        enableDisableSliceRule = new QPushButton(rulesBox);
        enableDisableSliceRule->setObjectName(QStringLiteral("enableDisableSliceRule"));
        QIcon icon5;
        icon5.addFile(QStringLiteral(":/icons/eye.png"), QSize(), QIcon::Normal, QIcon::Off);
        enableDisableSliceRule->setIcon(icon5);
        enableDisableSliceRule->setIconSize(QSize(21, 21));

        gridLayout_3->addWidget(enableDisableSliceRule, 6, 0, 1, 1);

        addSliceRule = new QPushButton(rulesBox);
        addSliceRule->setObjectName(QStringLiteral("addSliceRule"));
        QIcon icon6;
        icon6.addFile(QStringLiteral(":/icons/plus.png"), QSize(), QIcon::Normal, QIcon::Off);
        addSliceRule->setIcon(icon6);
        addSliceRule->setIconSize(QSize(21, 21));

        gridLayout_3->addWidget(addSliceRule, 6, 3, 1, 1);

        horizontalSpacer_11 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_11, 6, 1, 1, 1);

        deleteSliceRule = new QPushButton(rulesBox);
        deleteSliceRule->setObjectName(QStringLiteral("deleteSliceRule"));
        QIcon icon7;
        icon7.addFile(QStringLiteral(":/icons/minus.png"), QSize(), QIcon::Normal, QIcon::Off);
        deleteSliceRule->setIcon(icon7);
        deleteSliceRule->setIconSize(QSize(21, 21));

        gridLayout_3->addWidget(deleteSliceRule, 6, 2, 1, 1);

        sliceRulesList = new QListWidget(rulesBox);
        sliceRulesList->setObjectName(QStringLiteral("sliceRulesList"));

        gridLayout_3->addWidget(sliceRulesList, 5, 0, 1, 4);

        addVolumeRule = new QPushButton(rulesBox);
        addVolumeRule->setObjectName(QStringLiteral("addVolumeRule"));
        addVolumeRule->setIcon(icon6);
        addVolumeRule->setIconSize(QSize(21, 21));

        gridLayout_3->addWidget(addVolumeRule, 2, 3, 1, 1);

        volumeRulesList = new QListWidget(rulesBox);
        volumeRulesList->setObjectName(QStringLiteral("volumeRulesList"));

        gridLayout_3->addWidget(volumeRulesList, 1, 0, 1, 4);

        deleteVolumeRule = new QPushButton(rulesBox);
        deleteVolumeRule->setObjectName(QStringLiteral("deleteVolumeRule"));
        deleteVolumeRule->setIcon(icon7);
        deleteVolumeRule->setIconSize(QSize(21, 21));

        gridLayout_3->addWidget(deleteVolumeRule, 2, 2, 1, 1);

        enableDisableVolumeRule = new QPushButton(rulesBox);
        enableDisableVolumeRule->setObjectName(QStringLiteral("enableDisableVolumeRule"));
        enableDisableVolumeRule->setIcon(icon5);
        enableDisableVolumeRule->setIconSize(QSize(21, 21));

        gridLayout_3->addWidget(enableDisableVolumeRule, 2, 0, 1, 1);

        verticalSpacer_2 = new QSpacerItem(10, 10, QSizePolicy::Minimum, QSizePolicy::Fixed);

        gridLayout_3->addItem(verticalSpacer_2, 3, 0, 1, 1);

        horizontalSpacer_12 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_12, 2, 1, 1, 1);

        volumeRuleLabel = new QLabel(rulesBox);
        volumeRuleLabel->setObjectName(QStringLiteral("volumeRuleLabel"));

        gridLayout_3->addWidget(volumeRuleLabel, 0, 0, 1, 2);

        sliceRuleLabel = new QLabel(rulesBox);
        sliceRuleLabel->setObjectName(QStringLiteral("sliceRuleLabel"));

        gridLayout_3->addWidget(sliceRuleLabel, 4, 0, 1, 2);


        gridLayout->addWidget(rulesBox, 0, 2, 3, 1);

        volumeWidget = new QVTKWidget(centralWidget);
        volumeWidget->setObjectName(QStringLiteral("volumeWidget"));
        volumeWidget->setMinimumSize(QSize(400, 400));

        gridLayout->addWidget(volumeWidget, 1, 0, 1, 1);

        labelFolder = new QLabel(centralWidget);
        labelFolder->setObjectName(QStringLiteral("labelFolder"));
        labelFolder->setMaximumSize(QSize(16777215, 13));

        gridLayout->addWidget(labelFolder, 2, 0, 1, 1);

        mainTab = new QTabWidget(centralWidget);
        mainTab->setObjectName(QStringLiteral("mainTab"));
        tabSlices = new QWidget();
        tabSlices->setObjectName(QStringLiteral("tabSlices"));
        verticalLayout_4 = new QVBoxLayout(tabSlices);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        planeOptions = new QGroupBox(tabSlices);
        planeOptions->setObjectName(QStringLiteral("planeOptions"));
        planeOptions->setMinimumSize(QSize(0, 0));
        planeOptions->setMaximumSize(QSize(16777215, 72));
        planeOptions->setTitle(QStringLiteral("Plano"));
        planeOptions->setFlat(false);
        planeOptions->setCheckable(false);
        horizontalLayout = new QHBoxLayout(planeOptions);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        enableDisablePlane = new QPushButton(planeOptions);
        enableDisablePlane->setObjectName(QStringLiteral("enableDisablePlane"));
        QIcon icon8;
        icon8.addFile(QStringLiteral(":/icons/eye-slash.png"), QSize(), QIcon::Normal, QIcon::Off);
        enableDisablePlane->setIcon(icon8);
        enableDisablePlane->setIconSize(QSize(21, 21));

        horizontalLayout->addWidget(enableDisablePlane);

        horizontalSpacer_9 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_9);

        sagitalPlane = new QPushButton(planeOptions);
        sagitalPlane->setObjectName(QStringLiteral("sagitalPlane"));
        sagitalPlane->setMinimumSize(QSize(0, 40));
        QIcon icon9;
        icon9.addFile(QStringLiteral(":/icons/sagital.png"), QSize(), QIcon::Normal, QIcon::Off);
        sagitalPlane->setIcon(icon9);
        sagitalPlane->setIconSize(QSize(40, 40));

        horizontalLayout->addWidget(sagitalPlane);

        axialPlane = new QPushButton(planeOptions);
        axialPlane->setObjectName(QStringLiteral("axialPlane"));
        axialPlane->setMinimumSize(QSize(0, 40));
        QIcon icon10;
        icon10.addFile(QStringLiteral(":/icons/axial.png"), QSize(), QIcon::Normal, QIcon::Off);
        axialPlane->setIcon(icon10);
        axialPlane->setIconSize(QSize(40, 40));

        horizontalLayout->addWidget(axialPlane);

        coronalPlane = new QPushButton(planeOptions);
        coronalPlane->setObjectName(QStringLiteral("coronalPlane"));
        coronalPlane->setMinimumSize(QSize(0, 40));
        QIcon icon11;
        icon11.addFile(QStringLiteral(":/icons/coronal.png"), QSize(), QIcon::Normal, QIcon::Off);
        coronalPlane->setIcon(icon11);
        coronalPlane->setIconSize(QSize(40, 40));

        horizontalLayout->addWidget(coronalPlane);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        exportSliceImage = new QPushButton(planeOptions);
        exportSliceImage->setObjectName(QStringLiteral("exportSliceImage"));
        exportSliceImage->setIcon(icon4);
        exportSliceImage->setIconSize(QSize(21, 21));

        horizontalLayout->addWidget(exportSliceImage);


        verticalLayout_4->addWidget(planeOptions);

        slicesWidget = new QVTKWidget(tabSlices);
        slicesWidget->setObjectName(QStringLiteral("slicesWidget"));
        slicesWidget->setMinimumSize(QSize(0, 0));

        verticalLayout_4->addWidget(slicesWidget);

        coordsAndValueLabel = new QLabel(tabSlices);
        coordsAndValueLabel->setObjectName(QStringLiteral("coordsAndValueLabel"));
        coordsAndValueLabel->setMaximumSize(QSize(16777215, 20));

        verticalLayout_4->addWidget(coordsAndValueLabel);

        mainTab->addTab(tabSlices, QString());
        tabTransferFunction = new QWidget();
        tabTransferFunction->setObjectName(QStringLiteral("tabTransferFunction"));
        gridLayout_84 = new QGridLayout(tabTransferFunction);
        gridLayout_84->setSpacing(6);
        gridLayout_84->setContentsMargins(11, 11, 11, 11);
        gridLayout_84->setObjectName(QStringLiteral("gridLayout_84"));
        exportPreset = new QPushButton(tabTransferFunction);
        exportPreset->setObjectName(QStringLiteral("exportPreset"));
        exportPreset->setIcon(icon4);
        exportPreset->setIconSize(QSize(21, 21));

        gridLayout_84->addWidget(exportPreset, 1, 7, 1, 1);

        defaultPresetsBox = new QGroupBox(tabTransferFunction);
        defaultPresetsBox->setObjectName(QStringLiteral("defaultPresetsBox"));
        defaultPresetsBox->setMaximumSize(QSize(16777215, 96));
        horizontalLayout_2 = new QHBoxLayout(defaultPresetsBox);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_6);

        completePreset = new QPushButton(defaultPresetsBox);
        completePreset->setObjectName(QStringLiteral("completePreset"));
        QIcon icon12;
        icon12.addFile(QStringLiteral(":/icons/complete.png"), QSize(), QIcon::Normal, QIcon::Off);
        completePreset->setIcon(icon12);
        completePreset->setIconSize(QSize(50, 50));

        horizontalLayout_2->addWidget(completePreset);

        woodPreset = new QPushButton(defaultPresetsBox);
        woodPreset->setObjectName(QStringLiteral("woodPreset"));
        QIcon icon13;
        icon13.addFile(QStringLiteral(":/icons/wood.png"), QSize(), QIcon::Normal, QIcon::Off);
        woodPreset->setIcon(icon13);
        woodPreset->setIconSize(QSize(50, 50));

        horizontalLayout_2->addWidget(woodPreset);

        stuccoPreset = new QPushButton(defaultPresetsBox);
        stuccoPreset->setObjectName(QStringLiteral("stuccoPreset"));
        QIcon icon14;
        icon14.addFile(QStringLiteral(":/icons/stucco.png"), QSize(), QIcon::Normal, QIcon::Off);
        stuccoPreset->setIcon(icon14);
        stuccoPreset->setIconSize(QSize(50, 50));

        horizontalLayout_2->addWidget(stuccoPreset);

        metalPreset = new QPushButton(defaultPresetsBox);
        metalPreset->setObjectName(QStringLiteral("metalPreset"));
        QIcon icon15;
        icon15.addFile(QStringLiteral(":/icons/metal.png"), QSize(), QIcon::Normal, QIcon::Off);
        metalPreset->setIcon(icon15);
        metalPreset->setIconSize(QSize(50, 50));

        horizontalLayout_2->addWidget(metalPreset);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_5);


        gridLayout_84->addWidget(defaultPresetsBox, 0, 1, 1, 9);

        labelTFName = new QLabel(tabTransferFunction);
        labelTFName->setObjectName(QStringLiteral("labelTFName"));

        gridLayout_84->addWidget(labelTFName, 1, 3, 1, 1);

        labelTFDescription = new QLabel(tabTransferFunction);
        labelTFDescription->setObjectName(QStringLiteral("labelTFDescription"));

        gridLayout_84->addWidget(labelTFDescription, 1, 5, 1, 1);

        tfDescription = new QLineEdit(tabTransferFunction);
        tfDescription->setObjectName(QStringLiteral("tfDescription"));
        tfDescription->setMinimumSize(QSize(120, 0));

        gridLayout_84->addWidget(tfDescription, 1, 6, 1, 1);

        tfName = new QLineEdit(tabTransferFunction);
        tfName->setObjectName(QStringLiteral("tfName"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(tfName->sizePolicy().hasHeightForWidth());
        tfName->setSizePolicy(sizePolicy);
        tfName->setMaximumSize(QSize(150, 16777215));

        gridLayout_84->addWidget(tfName, 1, 4, 1, 1);

        scrollArea = new QScrollArea(tabTransferFunction);
        scrollArea->setObjectName(QStringLiteral("scrollArea"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(scrollArea->sizePolicy().hasHeightForWidth());
        scrollArea->setSizePolicy(sizePolicy1);
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QStringLiteral("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 452, 693));
        verticalLayout_5 = new QVBoxLayout(scrollAreaWidgetContents);
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setContentsMargins(11, 11, 11, 11);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        colorTFBox = new QGroupBox(scrollAreaWidgetContents);
        colorTFBox->setObjectName(QStringLiteral("colorTFBox"));
        gridLayout_85 = new QGridLayout(colorTFBox);
        gridLayout_85->setSpacing(6);
        gridLayout_85->setContentsMargins(11, 11, 11, 11);
        gridLayout_85->setObjectName(QStringLiteral("gridLayout_85"));
        colorTFMinSlider = new QSlider(colorTFBox);
        colorTFMinSlider->setObjectName(QStringLiteral("colorTFMinSlider"));
        colorTFMinSlider->setMinimum(-9024);
        colorTFMinSlider->setMaximum(0);
        colorTFMinSlider->setValue(-9024);
        colorTFMinSlider->setOrientation(Qt::Horizontal);

        gridLayout_85->addWidget(colorTFMinSlider, 1, 0, 1, 1);

        colorTFMaxSlider = new QSlider(colorTFBox);
        colorTFMaxSlider->setObjectName(QStringLiteral("colorTFMaxSlider"));
        colorTFMaxSlider->setMaximum(10976);
        colorTFMaxSlider->setValue(10976);
        colorTFMaxSlider->setOrientation(Qt::Horizontal);

        gridLayout_85->addWidget(colorTFMaxSlider, 1, 1, 1, 1);

        colorTFWidget = new QVTKWidget(colorTFBox);
        colorTFWidget->setObjectName(QStringLiteral("colorTFWidget"));
        colorTFWidget->setMinimumSize(QSize(0, 160));

        gridLayout_85->addWidget(colorTFWidget, 0, 0, 1, 2);

        colorTFWidget->raise();
        colorTFMinSlider->raise();
        colorTFMaxSlider->raise();

        verticalLayout_5->addWidget(colorTFBox);

        scalarTFBox = new QGroupBox(scrollAreaWidgetContents);
        scalarTFBox->setObjectName(QStringLiteral("scalarTFBox"));
        gridLayout_87 = new QGridLayout(scalarTFBox);
        gridLayout_87->setSpacing(6);
        gridLayout_87->setContentsMargins(11, 11, 11, 11);
        gridLayout_87->setObjectName(QStringLiteral("gridLayout_87"));
        scalarTFWidget = new QVTKWidget(scalarTFBox);
        scalarTFWidget->setObjectName(QStringLiteral("scalarTFWidget"));
        scalarTFWidget->setMinimumSize(QSize(0, 160));

        gridLayout_87->addWidget(scalarTFWidget, 0, 0, 1, 2);

        scalarTFMinSlider = new QSlider(scalarTFBox);
        scalarTFMinSlider->setObjectName(QStringLiteral("scalarTFMinSlider"));
        scalarTFMinSlider->setMinimum(-9024);
        scalarTFMinSlider->setMaximum(0);
        scalarTFMinSlider->setValue(-9024);
        scalarTFMinSlider->setOrientation(Qt::Horizontal);

        gridLayout_87->addWidget(scalarTFMinSlider, 2, 0, 1, 1);

        scalarTFMaxSlider = new QSlider(scalarTFBox);
        scalarTFMaxSlider->setObjectName(QStringLiteral("scalarTFMaxSlider"));
        scalarTFMaxSlider->setMaximum(10976);
        scalarTFMaxSlider->setValue(10976);
        scalarTFMaxSlider->setOrientation(Qt::Horizontal);

        gridLayout_87->addWidget(scalarTFMaxSlider, 2, 1, 1, 1);


        verticalLayout_5->addWidget(scalarTFBox);

        gradientTFBox = new QGroupBox(scrollAreaWidgetContents);
        gradientTFBox->setObjectName(QStringLiteral("gradientTFBox"));
        gridLayout_88 = new QGridLayout(gradientTFBox);
        gridLayout_88->setSpacing(6);
        gridLayout_88->setContentsMargins(11, 11, 11, 11);
        gridLayout_88->setObjectName(QStringLiteral("gridLayout_88"));
        gradientTFWidget = new QVTKWidget(gradientTFBox);
        gradientTFWidget->setObjectName(QStringLiteral("gradientTFWidget"));
        gradientTFWidget->setMinimumSize(QSize(0, 160));

        gridLayout_88->addWidget(gradientTFWidget, 0, 0, 1, 2);

        gradientTFMinSlider = new QSlider(gradientTFBox);
        gradientTFMinSlider->setObjectName(QStringLiteral("gradientTFMinSlider"));
        gradientTFMinSlider->setMinimum(-9024);
        gradientTFMinSlider->setMaximum(0);
        gradientTFMinSlider->setSliderPosition(-9024);
        gradientTFMinSlider->setOrientation(Qt::Horizontal);

        gridLayout_88->addWidget(gradientTFMinSlider, 1, 0, 1, 1);

        gradientTFMaxSlider = new QSlider(gradientTFBox);
        gradientTFMaxSlider->setObjectName(QStringLiteral("gradientTFMaxSlider"));
        gradientTFMaxSlider->setMaximum(10976);
        gradientTFMaxSlider->setValue(10976);
        gradientTFMaxSlider->setOrientation(Qt::Horizontal);

        gridLayout_88->addWidget(gradientTFMaxSlider, 1, 1, 1, 1);


        verticalLayout_5->addWidget(gradientTFBox);

        scrollArea->setWidget(scrollAreaWidgetContents);

        gridLayout_84->addWidget(scrollArea, 2, 1, 1, 9);

        importPreset = new QPushButton(tabTransferFunction);
        importPreset->setObjectName(QStringLiteral("importPreset"));
        importPreset->setIcon(icon1);
        importPreset->setIconSize(QSize(21, 21));

        gridLayout_84->addWidget(importPreset, 1, 2, 1, 1);

        mainTab->addTab(tabTransferFunction, QString());
        extractMeshTab = new QWidget();
        extractMeshTab->setObjectName(QStringLiteral("extractMeshTab"));
        gridLayout_2 = new QGridLayout(extractMeshTab);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        extractMesh = new QPushButton(extractMeshTab);
        extractMesh->setObjectName(QStringLiteral("extractMesh"));
        extractMesh->setIcon(icon4);
        extractMesh->setIconSize(QSize(21, 21));

        gridLayout_2->addWidget(extractMesh, 3, 4, 1, 1);

        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_8, 3, 3, 1, 1);

        isoValueSlider = new QSlider(extractMeshTab);
        isoValueSlider->setObjectName(QStringLiteral("isoValueSlider"));
        isoValueSlider->setMinimum(-1024);
        isoValueSlider->setMaximum(3071);
        isoValueSlider->setValue(-750);
        isoValueSlider->setOrientation(Qt::Horizontal);

        gridLayout_2->addWidget(isoValueSlider, 1, 2, 1, 3);

        extractMeshPresets = new QGroupBox(extractMeshTab);
        extractMeshPresets->setObjectName(QStringLiteral("extractMeshPresets"));
        extractMeshPresets->setMaximumSize(QSize(16777215, 96));
        horizontalLayout_3 = new QHBoxLayout(extractMeshPresets);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);

        extractMeshWood = new QPushButton(extractMeshPresets);
        extractMeshWood->setObjectName(QStringLiteral("extractMeshWood"));
        extractMeshWood->setIcon(icon13);
        extractMeshWood->setIconSize(QSize(50, 50));

        horizontalLayout_3->addWidget(extractMeshWood);

        extractMeshStucco = new QPushButton(extractMeshPresets);
        extractMeshStucco->setObjectName(QStringLiteral("extractMeshStucco"));
        extractMeshStucco->setIcon(icon14);
        extractMeshStucco->setIconSize(QSize(50, 50));

        horizontalLayout_3->addWidget(extractMeshStucco);

        extractMeshMetal = new QPushButton(extractMeshPresets);
        extractMeshMetal->setObjectName(QStringLiteral("extractMeshMetal"));
        extractMeshMetal->setIcon(icon15);
        extractMeshMetal->setIconSize(QSize(50, 50));

        horizontalLayout_3->addWidget(extractMeshMetal);

        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_7);


        gridLayout_2->addWidget(extractMeshPresets, 0, 2, 1, 3);

        meshWidget = new QVTKWidget(extractMeshTab);
        meshWidget->setObjectName(QStringLiteral("meshWidget"));
        meshWidget->setMinimumSize(QSize(350, 350));

        gridLayout_2->addWidget(meshWidget, 2, 2, 1, 3);

        mainTab->addTab(extractMeshTab, QString());
        tabProperties = new QWidget();
        tabProperties->setObjectName(QStringLiteral("tabProperties"));
        tabProperties->setLayoutDirection(Qt::LeftToRight);
        gridLayout_83 = new QGridLayout(tabProperties);
        gridLayout_83->setSpacing(6);
        gridLayout_83->setContentsMargins(11, 11, 11, 11);
        gridLayout_83->setObjectName(QStringLiteral("gridLayout_83"));
        materialProperties = new QGroupBox(tabProperties);
        materialProperties->setObjectName(QStringLiteral("materialProperties"));
        gridLayout_86 = new QGridLayout(materialProperties);
        gridLayout_86->setSpacing(6);
        gridLayout_86->setContentsMargins(11, 11, 11, 11);
        gridLayout_86->setObjectName(QStringLiteral("gridLayout_86"));
        diffuseValue = new QDoubleSpinBox(materialProperties);
        diffuseValue->setObjectName(QStringLiteral("diffuseValue"));
        diffuseValue->setMaximum(1);
        diffuseValue->setSingleStep(0.1);
        diffuseValue->setValue(0);

        gridLayout_86->addWidget(diffuseValue, 1, 3, 1, 1);

        specularLabel = new QLabel(materialProperties);
        specularLabel->setObjectName(QStringLiteral("specularLabel"));

        gridLayout_86->addWidget(specularLabel, 2, 1, 1, 1);

        ambientLabel = new QLabel(materialProperties);
        ambientLabel->setObjectName(QStringLiteral("ambientLabel"));

        gridLayout_86->addWidget(ambientLabel, 0, 1, 1, 1);

        diffuseLabel = new QLabel(materialProperties);
        diffuseLabel->setObjectName(QStringLiteral("diffuseLabel"));

        gridLayout_86->addWidget(diffuseLabel, 1, 1, 1, 1);

        ambientValue = new QDoubleSpinBox(materialProperties);
        ambientValue->setObjectName(QStringLiteral("ambientValue"));
        ambientValue->setMaximum(1);
        ambientValue->setSingleStep(0.1);
        ambientValue->setValue(0);

        gridLayout_86->addWidget(ambientValue, 0, 3, 1, 1);

        specularValue = new QDoubleSpinBox(materialProperties);
        specularValue->setObjectName(QStringLiteral("specularValue"));
        specularValue->setMaximum(1);
        specularValue->setSingleStep(0.1);
        specularValue->setValue(0);

        gridLayout_86->addWidget(specularValue, 2, 3, 1, 1);

        powerValue = new QDoubleSpinBox(materialProperties);
        powerValue->setObjectName(QStringLiteral("powerValue"));
        powerValue->setMinimum(1);
        powerValue->setMaximum(50);
        powerValue->setValue(1);

        gridLayout_86->addWidget(powerValue, 3, 3, 1, 1);

        powerLabel = new QLabel(materialProperties);
        powerLabel->setObjectName(QStringLiteral("powerLabel"));

        gridLayout_86->addWidget(powerLabel, 3, 1, 1, 1);

        horizontalSpacer_13 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_86->addItem(horizontalSpacer_13, 0, 2, 1, 1);

        horizontalSpacer_16 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_86->addItem(horizontalSpacer_16, 3, 2, 1, 1);

        horizontalSpacer_14 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_86->addItem(horizontalSpacer_14, 1, 2, 1, 1);

        horizontalSpacer_15 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_86->addItem(horizontalSpacer_15, 2, 2, 1, 1);

        restoreMaterial = new QPushButton(materialProperties);
        restoreMaterial->setObjectName(QStringLiteral("restoreMaterial"));

        gridLayout_86->addWidget(restoreMaterial, 5, 1, 1, 1);

        updateProperties = new QPushButton(materialProperties);
        updateProperties->setObjectName(QStringLiteral("updateProperties"));

        gridLayout_86->addWidget(updateProperties, 5, 2, 1, 2);

        ambientLabel->raise();
        ambientValue->raise();
        diffuseLabel->raise();
        diffuseValue->raise();
        specularLabel->raise();
        specularValue->raise();
        powerLabel->raise();
        powerValue->raise();
        updateProperties->raise();
        restoreMaterial->raise();

        gridLayout_83->addWidget(materialProperties, 0, 0, 1, 2);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_83->addItem(verticalSpacer, 4, 0, 1, 1);

        groupBox_2 = new QGroupBox(tabProperties);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        gridLayout_4 = new QGridLayout(groupBox_2);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        meshBackgroundLabel = new QLabel(groupBox_2);
        meshBackgroundLabel->setObjectName(QStringLiteral("meshBackgroundLabel"));

        gridLayout_4->addWidget(meshBackgroundLabel, 3, 0, 1, 1);

        meshBackground = new QPushButton(groupBox_2);
        meshBackground->setObjectName(QStringLiteral("meshBackground"));

        gridLayout_4->addWidget(meshBackground, 3, 2, 1, 1);

        volumeDeletingBackground = new QPushButton(groupBox_2);
        volumeDeletingBackground->setObjectName(QStringLiteral("volumeDeletingBackground"));

        gridLayout_4->addWidget(volumeDeletingBackground, 2, 2, 1, 1);

        volumeBackgroundLabel = new QLabel(groupBox_2);
        volumeBackgroundLabel->setObjectName(QStringLiteral("volumeBackgroundLabel"));

        gridLayout_4->addWidget(volumeBackgroundLabel, 0, 0, 1, 1);

        restoreBackgrounds = new QPushButton(groupBox_2);
        restoreBackgrounds->setObjectName(QStringLiteral("restoreBackgrounds"));

        gridLayout_4->addWidget(restoreBackgrounds, 4, 0, 1, 1);

        volumeBackground = new QPushButton(groupBox_2);
        volumeBackground->setObjectName(QStringLiteral("volumeBackground"));
        volumeBackground->setMinimumSize(QSize(0, 0));
        volumeBackground->setAutoFillBackground(true);

        gridLayout_4->addWidget(volumeBackground, 0, 2, 1, 1);

        volumeDeletingBackgroundLabel = new QLabel(groupBox_2);
        volumeDeletingBackgroundLabel->setObjectName(QStringLiteral("volumeDeletingBackgroundLabel"));

        gridLayout_4->addWidget(volumeDeletingBackgroundLabel, 2, 0, 1, 1);

        horizontalSpacer_17 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_4->addItem(horizontalSpacer_17, 0, 1, 1, 1);

        horizontalSpacer_18 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_4->addItem(horizontalSpacer_18, 2, 1, 1, 1);

        horizontalSpacer_19 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_4->addItem(horizontalSpacer_19, 3, 1, 1, 1);


        gridLayout_83->addWidget(groupBox_2, 1, 0, 1, 2);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_83->addItem(horizontalSpacer_4, 0, 2, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_83->addItem(horizontalSpacer_3, 1, 2, 1, 1);

        mainTab->addTab(tabProperties, QString());

        gridLayout->addWidget(mainTab, 0, 1, 3, 1);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1143, 21));
        menuArchivo = new QMenu(menuBar);
        menuArchivo->setObjectName(QStringLiteral("menuArchivo"));
        menuEditar = new QMenu(menuBar);
        menuEditar->setObjectName(QStringLiteral("menuEditar"));
        menuHerramientas = new QMenu(menuBar);
        menuHerramientas->setObjectName(QStringLiteral("menuHerramientas"));
        MainWindow->setMenuBar(menuBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuArchivo->menuAction());
        menuBar->addAction(menuEditar->menuAction());
        menuBar->addAction(menuHerramientas->menuAction());
        menuArchivo->addAction(actionOpenDICOM);
        menuArchivo->addSeparator();
        menuArchivo->addAction(actionExportVolumeImage);
        menuArchivo->addAction(actionExportSliceImage);
        menuArchivo->addSeparator();
        menuArchivo->addAction(actionExit);
        menuEditar->addAction(actionEnableDisablePlane);
        menuEditar->addAction(actionSagitalPlane);
        menuEditar->addAction(actionAxialPlane);
        menuEditar->addAction(actionCoronalPlane);
        menuEditar->addSeparator();
        menuEditar->addAction(actionCompletePreset);
        menuEditar->addAction(actionWoodPreset);
        menuEditar->addAction(actionStuccoPreset);
        menuEditar->addAction(actionMetalPreset);
        menuEditar->addSeparator();
        menuEditar->addAction(actionDeleteVolumeParts);
        menuEditar->addSeparator();
        menuEditar->addAction(actionWoodMesh);
        menuEditar->addAction(actionStuccoMesh);
        menuEditar->addAction(actionMetalMesh);
        menuHerramientas->addAction(actionImportPreset);
        menuHerramientas->addAction(actionExportPreset);
        menuHerramientas->addSeparator();
        menuHerramientas->addAction(actionExtractMesh);

        retranslateUi(MainWindow);

        mainTab->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "3DCurator", Q_NULLPTR));
        actionOpenDICOM->setText(QApplication::translate("MainWindow", "Abrir...", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionOpenDICOM->setToolTip(QApplication::translate("MainWindow", "<html><head/><body><p>Abrir</p></body></html>", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        actionOpenDICOM->setShortcut(QApplication::translate("MainWindow", "Ctrl+O", Q_NULLPTR));
        actionExit->setText(QApplication::translate("MainWindow", "Salir", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionExit->setToolTip(QApplication::translate("MainWindow", "Salir", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        actionExit->setShortcut(QApplication::translate("MainWindow", "Ctrl+Q", Q_NULLPTR));
        actionExportVolumeImage->setText(QApplication::translate("MainWindow", "Exportar figura...", Q_NULLPTR));
        actionExportVolumeImage->setShortcut(QApplication::translate("MainWindow", "Ctrl+F", Q_NULLPTR));
        actionExportSliceImage->setText(QApplication::translate("MainWindow", "Exportar corte...", Q_NULLPTR));
        actionExportSliceImage->setShortcut(QApplication::translate("MainWindow", "Ctrl+S", Q_NULLPTR));
        actionImportPreset->setText(QApplication::translate("MainWindow", "Importar preset...", Q_NULLPTR));
        actionImportPreset->setShortcut(QApplication::translate("MainWindow", "Ctrl+Shift+I", Q_NULLPTR));
        actionExportPreset->setText(QApplication::translate("MainWindow", "Exportar preset...", Q_NULLPTR));
        actionExportPreset->setShortcut(QApplication::translate("MainWindow", "Ctrl+Shift+E", Q_NULLPTR));
        actionDeleteVolumeParts->setText(QApplication::translate("MainWindow", "Borrar partes", Q_NULLPTR));
        actionDeleteVolumeParts->setShortcut(QApplication::translate("MainWindow", "Ctrl+Shift+D", Q_NULLPTR));
        actionOpenDICOM_2->setText(QApplication::translate("MainWindow", "Abrir...", Q_NULLPTR));
        actionUpdateMesh->setText(QApplication::translate("MainWindow", "Generar malla", Q_NULLPTR));
        actionEnableDisablePlane->setText(QApplication::translate("MainWindow", "Mostrar/Esconder plano", Q_NULLPTR));
        actionEnableDisablePlane->setShortcut(QApplication::translate("MainWindow", "Ctrl+Shift+H", Q_NULLPTR));
        actionSagitalPlane->setText(QApplication::translate("MainWindow", "Plano sagital", Q_NULLPTR));
        actionSagitalPlane->setShortcut(QApplication::translate("MainWindow", "Ctrl+Shift+S", Q_NULLPTR));
        actionAxialPlane->setText(QApplication::translate("MainWindow", "Plano axial", Q_NULLPTR));
        actionAxialPlane->setShortcut(QApplication::translate("MainWindow", "Ctrl+Shift+A", Q_NULLPTR));
        actionCoronalPlane->setText(QApplication::translate("MainWindow", "Plano coronal", Q_NULLPTR));
        actionCoronalPlane->setShortcut(QApplication::translate("MainWindow", "Ctrl+Shift+C", Q_NULLPTR));
        actionWoodPreset->setText(QApplication::translate("MainWindow", "Preset madera", Q_NULLPTR));
        actionWoodPreset->setShortcut(QApplication::translate("MainWindow", "F2", Q_NULLPTR));
        actionStuccoPreset->setText(QApplication::translate("MainWindow", "Preset estuco", Q_NULLPTR));
        actionStuccoPreset->setShortcut(QApplication::translate("MainWindow", "F3", Q_NULLPTR));
        actionMetalPreset->setText(QApplication::translate("MainWindow", "Preset metal", Q_NULLPTR));
        actionMetalPreset->setShortcut(QApplication::translate("MainWindow", "F4", Q_NULLPTR));
        actionCompletePreset->setText(QApplication::translate("MainWindow", "Preset completo", Q_NULLPTR));
        actionCompletePreset->setShortcut(QApplication::translate("MainWindow", "F1", Q_NULLPTR));
        actionWoodMesh->setText(QApplication::translate("MainWindow", "Malla madera", Q_NULLPTR));
        actionStuccoMesh->setText(QApplication::translate("MainWindow", "Malla estuco", Q_NULLPTR));
        actionMetalMesh->setText(QApplication::translate("MainWindow", "Malla metal", Q_NULLPTR));
        actionExtractMesh->setText(QApplication::translate("MainWindow", "Extraer malla...", Q_NULLPTR));
        actionExtractMesh->setShortcut(QApplication::translate("MainWindow", "Ctrl+Shift+M", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("MainWindow", "Volumen", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        openDICOM->setToolTip(QApplication::translate("MainWindow", "Abrir directorio DICOM", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        openDICOM->setText(QString());
#ifndef QT_NO_TOOLTIP
        deleteVolumeParts->setToolTip(QApplication::translate("MainWindow", "Borrar partes", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        deleteVolumeParts->setText(QString());
#ifndef QT_NO_TOOLTIP
        exportVolumeImage->setToolTip(QApplication::translate("MainWindow", "Guardar imagen volumen", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        exportVolumeImage->setText(QString());
        rulesBox->setTitle(QApplication::translate("MainWindow", "Reglas", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        enableDisableSliceRule->setToolTip(QApplication::translate("MainWindow", "Mostrar/Esconder regla", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        enableDisableSliceRule->setText(QString());
#ifndef QT_NO_TOOLTIP
        addSliceRule->setToolTip(QApplication::translate("MainWindow", "A\303\261adir regla", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        addSliceRule->setText(QString());
#ifndef QT_NO_TOOLTIP
        deleteSliceRule->setToolTip(QApplication::translate("MainWindow", "Eliminar regla", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        deleteSliceRule->setText(QString());
#ifndef QT_NO_TOOLTIP
        addVolumeRule->setToolTip(QApplication::translate("MainWindow", "A\303\261adir regla", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        addVolumeRule->setText(QString());
#ifndef QT_NO_TOOLTIP
        deleteVolumeRule->setToolTip(QApplication::translate("MainWindow", "Eliminar regla", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        deleteVolumeRule->setText(QString());
#ifndef QT_NO_TOOLTIP
        enableDisableVolumeRule->setToolTip(QApplication::translate("MainWindow", "Mostrar/Esconder regla", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        enableDisableVolumeRule->setText(QString());
        volumeRuleLabel->setText(QApplication::translate("MainWindow", "Volumen", Q_NULLPTR));
        sliceRuleLabel->setText(QApplication::translate("MainWindow", "Cortes", Q_NULLPTR));
        labelFolder->setText(QApplication::translate("MainWindow", "Carpeta", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        enableDisablePlane->setToolTip(QApplication::translate("MainWindow", "Mosrtar/Esconder plano", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        enableDisablePlane->setText(QString());
#ifndef QT_NO_TOOLTIP
        sagitalPlane->setToolTip(QApplication::translate("MainWindow", "Plano sagital", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        sagitalPlane->setText(QString());
#ifndef QT_NO_TOOLTIP
        axialPlane->setToolTip(QApplication::translate("MainWindow", "Plano axial", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        axialPlane->setText(QString());
#ifndef QT_NO_TOOLTIP
        coronalPlane->setToolTip(QApplication::translate("MainWindow", "Plano coronal", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        coronalPlane->setText(QString());
#ifndef QT_NO_TOOLTIP
        exportSliceImage->setToolTip(QApplication::translate("MainWindow", "Guardar imagen corte", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        exportSliceImage->setText(QString());
        coordsAndValueLabel->setText(QApplication::translate("MainWindow", "HU: Fuera de rango", Q_NULLPTR));
        mainTab->setTabText(mainTab->indexOf(tabSlices), QApplication::translate("MainWindow", "Cortes", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        exportPreset->setToolTip(QApplication::translate("MainWindow", "Exportar preset", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        exportPreset->setText(QString());
        defaultPresetsBox->setTitle(QApplication::translate("MainWindow", "Presets", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        completePreset->setToolTip(QApplication::translate("MainWindow", "Preset completo", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        completePreset->setText(QString());
#ifndef QT_NO_TOOLTIP
        woodPreset->setToolTip(QApplication::translate("MainWindow", "Preset madera", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        woodPreset->setText(QString());
#ifndef QT_NO_TOOLTIP
        stuccoPreset->setToolTip(QApplication::translate("MainWindow", "Preset estuco", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        stuccoPreset->setText(QString());
#ifndef QT_NO_TOOLTIP
        metalPreset->setToolTip(QApplication::translate("MainWindow", "Preset metal", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        metalPreset->setText(QString());
        labelTFName->setText(QApplication::translate("MainWindow", "Nombre", Q_NULLPTR));
        labelTFDescription->setText(QApplication::translate("MainWindow", "Descripci\303\263n", Q_NULLPTR));
        tfDescription->setText(QString());
        tfName->setText(QString());
        colorTFBox->setTitle(QApplication::translate("MainWindow", "Color", Q_NULLPTR));
        scalarTFBox->setTitle(QApplication::translate("MainWindow", "Opacidad escalar", Q_NULLPTR));
        gradientTFBox->setTitle(QApplication::translate("MainWindow", "Opacidad gradiente", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        importPreset->setToolTip(QApplication::translate("MainWindow", "Importar preset", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        importPreset->setText(QString());
        mainTab->setTabText(mainTab->indexOf(tabTransferFunction), QApplication::translate("MainWindow", "Funci\303\263n de transferencia", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        extractMesh->setToolTip(QApplication::translate("MainWindow", "Exportar malla", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        extractMesh->setText(QString());
        extractMeshPresets->setTitle(QApplication::translate("MainWindow", "Presets", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        extractMeshWood->setToolTip(QApplication::translate("MainWindow", "Isosuperficie madera", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        extractMeshWood->setText(QString());
#ifndef QT_NO_TOOLTIP
        extractMeshStucco->setToolTip(QApplication::translate("MainWindow", "Isosuperficie estuco", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        extractMeshStucco->setText(QString());
#ifndef QT_NO_TOOLTIP
        extractMeshMetal->setToolTip(QApplication::translate("MainWindow", "Isosuperficie metal", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        extractMeshMetal->setText(QString());
        mainTab->setTabText(mainTab->indexOf(extractMeshTab), QApplication::translate("MainWindow", "Extraer malla", Q_NULLPTR));
        materialProperties->setTitle(QApplication::translate("MainWindow", "Material", Q_NULLPTR));
        specularLabel->setText(QApplication::translate("MainWindow", "Especular", Q_NULLPTR));
        ambientLabel->setText(QApplication::translate("MainWindow", "Ambiente", Q_NULLPTR));
        diffuseLabel->setText(QApplication::translate("MainWindow", "Difusa", Q_NULLPTR));
        powerLabel->setText(QApplication::translate("MainWindow", "Potencia especular", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        restoreMaterial->setToolTip(QApplication::translate("MainWindow", "Restaurar material por defecto", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        restoreMaterial->setText(QApplication::translate("MainWindow", "Restaurar", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        updateProperties->setToolTip(QApplication::translate("MainWindow", "Actualizar material", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        updateProperties->setText(QApplication::translate("MainWindow", "Actualizar", Q_NULLPTR));
        groupBox_2->setTitle(QApplication::translate("MainWindow", "Fondos", Q_NULLPTR));
        meshBackgroundLabel->setText(QApplication::translate("MainWindow", "Malla", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        meshBackground->setToolTip(QApplication::translate("MainWindow", "Color de fondo malla", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        meshBackground->setText(QString());
#ifndef QT_NO_TOOLTIP
        volumeDeletingBackground->setToolTip(QApplication::translate("MainWindow", "Color de fondo borrado", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        volumeDeletingBackground->setText(QString());
        volumeBackgroundLabel->setText(QApplication::translate("MainWindow", "Volumen", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        restoreBackgrounds->setToolTip(QApplication::translate("MainWindow", "Restaurar colores de fondo por defecto", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        restoreBackgrounds->setText(QApplication::translate("MainWindow", "Restaurar", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        volumeBackground->setToolTip(QApplication::translate("MainWindow", "Color de fondo volumen", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        volumeBackground->setText(QString());
        volumeDeletingBackgroundLabel->setText(QApplication::translate("MainWindow", "Volumen (borrado)", Q_NULLPTR));
        mainTab->setTabText(mainTab->indexOf(tabProperties), QApplication::translate("MainWindow", "Propiedades", Q_NULLPTR));
        menuArchivo->setTitle(QApplication::translate("MainWindow", "Archivo", Q_NULLPTR));
        menuEditar->setTitle(QApplication::translate("MainWindow", "Editar", Q_NULLPTR));
        menuHerramientas->setTitle(QApplication::translate("MainWindow", "Herramientas", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
