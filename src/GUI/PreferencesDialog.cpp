#include "PreferencesDialog.h"
#include "ui_preferencesdialog.h"

PreferencesDialog::PreferencesDialog(QSettings *settings, Language *language, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PreferencesDialog),
    settings(settings),
    language(language)
{
    ui->setupUi(this);
    ui->languageInput->setCurrentIndex(getIndexFromLocale(language->getLocale()));

    // Connect button actions
    QObject::connect(ui->okButton, SIGNAL(clicked()), this, SLOT(accept()));
    QObject::connect(ui->cancelButton, SIGNAL(clicked()), this, SLOT(reject()));
}

PreferencesDialog::~PreferencesDialog() {
    delete ui;
}

void PreferencesDialog::accept() {
    QString l = getLocaleFromIndex(ui->languageInput->currentIndex());
    language->setLocale(l);
    settings->setValue("locale", l);
    done(0);
}

void PreferencesDialog::reject() {
    done(-1);
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
