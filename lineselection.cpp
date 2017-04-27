#include "lineselection.h"
#include "ui_lineselection.h"

LineSelection::LineSelection(QWidget *parent) : QDialog(parent), ui(new Ui::LineSelection) {
	ui->setupUi(this);
}

LineSelection::~LineSelection() {
	delete ui;
}
