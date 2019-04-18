#include "FilterSelectionDialog.h"
#include "ui_filterselectiondialog.h"

FilterSelectionDialog::FilterSelectionDialog(QWidget *parent) : QDialog(parent), ui(new Ui::FilterSelectionDialog) {
	ui->setupUi(this);

	// Connect button actions
	QObject::connect(ui->okButton, SIGNAL(clicked()), this, SLOT(accept()));
	QObject::connect(ui->cancelButton, SIGNAL(clicked()), this, SLOT(reject()));
}

FilterSelectionDialog::~FilterSelectionDialog() {
	delete ui;
}

unsigned int FilterSelectionDialog::getGaussianReps() const {
	return ui->gaussianReps->value();
}

unsigned int FilterSelectionDialog::getMeanRadius() const {
	switch (ui->meanRadius->currentIndex()) {
	case N_3x3:
		return 1;
		break;
	case N_5x5:
		return 2;
		break;
	case N_7x7:
		return 3;
		break;
	default:
		return 1;
	}
}

unsigned int FilterSelectionDialog::getMedianRadius() const {
	switch (ui->medianRadius->currentIndex()) {
	case N_3x3:
		return 1;
		break;
	case N_5x5:
		return 2;
		break;
	case N_7x7:
		return 3;
		break;
	default:
		return 1;
	}
}

void FilterSelectionDialog::accept() {
	done(filterType);
}

void FilterSelectionDialog::reject() {
	done(CANCEL);
}

void FilterSelectionDialog::on_filtersTab_currentChanged() {
	filterType = ui->filtersTab->currentIndex();
}
