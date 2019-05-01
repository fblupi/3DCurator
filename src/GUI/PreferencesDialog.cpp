#include "PreferencesDialog.h"
#include "ui_preferencesdialog.h"

PreferencesDialog::PreferencesDialog(QSettings *settings, Language *language, QWidget *parent) : QDialog(parent), ui(new Ui::PreferencesDialog) {
	ui->setupUi(this);

	this->settings = settings;
	this->language = language;
	ui->languageInput->setCurrentIndex(getIndexFromLocale(language->getLocale()));

	// Connect button actions
	QObject::connect(ui->okButton, SIGNAL(clicked()), this, SLOT(accept()));
	QObject::connect(ui->cancelButton, SIGNAL(clicked()), this, SLOT(reject()));
}

PreferencesDialog::~PreferencesDialog() {
	delete ui;
}

void PreferencesDialog::accept() {
	QString locale = getLocaleFromIndex(ui->languageInput->currentIndex());
	language->setLocale(locale);
	settings->setValue("locale", locale);
	done(0);
}

void PreferencesDialog::reject() {
	done(-1);
}

QString PreferencesDialog::getLocaleFromIndex(const int index) {
	switch (index) {
		case 0:
			return "en_US";
			break;
		case 1:
			return "es_ES";
			break;
		default:
			return "en_US";
			break;
	}
}

int PreferencesDialog::getIndexFromLocale(QString locale) {
	if (locale == "es_ES") {
		return 1;
	} else {
		return 0;
	}
}
