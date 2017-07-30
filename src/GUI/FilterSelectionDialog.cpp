#include "FilterSelectionDialog.h"
#include "ui_filterselectiondialog.h"

#include <iostream>

FilterSelectionDialog::FilterSelectionDialog(QWidget *parent) : QDialog(parent), ui(new Ui::FilterSelectionDialog) {
	ui->setupUi(this);

	// Connect button actions
	QObject::connect(ui->okButton, SIGNAL(clicked()), this, SLOT(accept()));
	QObject::connect(ui->cancelButton, SIGNAL(clicked()), this, SLOT(reject()));
}

FilterSelectionDialog::~FilterSelectionDialog() {
	delete ui;
}

int FilterSelectionDialog::getGaussianReps() const {
	return ui->gaussianReps->value();
}

void FilterSelectionDialog::accept() {
	done(GAUSSIAN);
}

void FilterSelectionDialog::reject() {
	done(CANCEL);
}