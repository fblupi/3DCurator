#include "PreferencesDialog.h"
#include "ui_preferencesdialog.h"

PreferencesDialog::PreferencesDialog(QSettings *settings, Backgrounds *backgrounds, Language *language, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PreferencesDialog),
    settings(settings),
    backgrounds(backgrounds),
    language(language)
{
    ui->setupUi(this);
    setupBackgrounds();
    setupLanguage();

    // Connect button actions
    QObject::connect(ui->okButton, SIGNAL(clicked()), this, SLOT(accept()));
    QObject::connect(ui->cancelButton, SIGNAL(clicked()), this, SLOT(reject()));
}

PreferencesDialog::~PreferencesDialog() {
    delete ui;
}

void PreferencesDialog::setupBackgrounds() {
    ui->volumeBackground->setStyleSheet("background-color: " + backgrounds->getVolumeBackground().name());
    ui->volumeDeletingBackground->setStyleSheet("background-color: " + backgrounds->getVolumeDeletingBackground().name());
    ui->volumeSegmentingBackground->setStyleSheet("background-color: " + backgrounds->getVolumeSegmentingBackground().name());
    ui->meshBackground->setStyleSheet("background-color: " + backgrounds->getMeshBackground().name());
}

void PreferencesDialog::setupLanguage() {
    ui->languageInput->setCurrentIndex(getIndexFromLocale(language->getLocale()));
}

void PreferencesDialog::accept() {
    processLanguage();
    done(0);
}

void PreferencesDialog::reject() {
    done(-1);
}

void PreferencesDialog::processLanguage() {
    QString l = getLocaleFromIndex(ui->languageInput->currentIndex());
    language->setLocale(l);
    settings->setValue("locale", l);
}

QString PreferencesDialog::getLocaleFromIndex(int index) {
    switch (index) {
        case 0:
            return "en_US";
        case 1:
            return "es_ES";
        default:
            return "en_US";
    }
}

int PreferencesDialog::getIndexFromLocale(const QString &locale) {
    if (locale == "es_ES") {
        return 1;
    } else {
        return 0;
    }
}

void PreferencesDialog::on_meshBackground_pressed() {
    QColor color = QColorDialog::getColor(backgrounds->getMeshBackground());
    if (color.isValid()) {
        backgrounds->setMeshBackground(color);
        settings->setValue("mesh_bg", QVariant(color.rgb()));
        ui->meshBackground->setStyleSheet("background-color: " + backgrounds->getMeshBackground().name());
    }
}


void PreferencesDialog::on_volumeBackground_pressed() {
    QColor color = QColorDialog::getColor(backgrounds->getVolumeBackground());
    if (color.isValid()) {
        backgrounds->setVolumeBackground(color);
        settings->setValue("volume_bg", QVariant(color.rgb()));
        ui->volumeBackground->setStyleSheet("background-color: " + backgrounds->getVolumeBackground().name());
    }
}

void PreferencesDialog::on_volumeDeletingBackground_pressed() {
    QColor color = QColorDialog::getColor(backgrounds->getVolumeDeletingBackground());
    if (color.isValid()) {
        backgrounds->setVolumeDeletingBackground(color);
        settings->setValue("volume_del_bg", QVariant(color.rgb()));
        ui->volumeDeletingBackground->setStyleSheet("background-color: " + backgrounds->getVolumeDeletingBackground().name());
    }
}

void PreferencesDialog::on_volumeSegmentingBackground_pressed() {
    QColor color = QColorDialog::getColor(backgrounds->getVolumeSegmentingBackground());
    if (color.isValid()) {
        backgrounds->setVolumeSegmentingBackground(color);
        settings->setValue("volume_seg_bg", QVariant(color.rgb()));
        ui->volumeSegmentingBackground->setStyleSheet("background-color: " + backgrounds->getVolumeSegmentingBackground().name());
    }
}
