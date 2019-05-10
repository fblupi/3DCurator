#include "LineSelectionDialog.h"
#include "ui_lineselectiondialog.h"

LineSelectionDialog::LineSelectionDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LineSelectionDialog)
{
    ui->setupUi(this);

    // Connect button actions
    QObject::connect(ui->okButton, SIGNAL(clicked()), this, SLOT(accept()));
    QObject::connect(ui->cancelButton, SIGNAL(clicked()), this, SLOT(reject()));
}

LineSelectionDialog::~LineSelectionDialog() {
    delete ui;
}

void LineSelectionDialog::setImage(const std::string &filename) {
    // Set image from filename
    QPixmap pixmap(filename.c_str());
    ui->image->setPixmap(pixmap);
    ui->image->setMask(pixmap.mask());
}

bool LineSelectionDialog::getCompleteUp() const {
    return ui->completeUp->isChecked();
}

bool LineSelectionDialog::getCompleteDown() const {
    return ui->completeDown->isChecked();
}

void LineSelectionDialog::accept() {
    if (ui->greenRadioButton->isChecked()) {
        done(LINE_GREEN);
    } else if (ui->blueRadioButton->isChecked()) {
        done(LINE_BLUE);
    } else if (ui->cyanRadioButton->isChecked()) {
        done(LINE_CYAN);
    } else if (ui->magentaRadioButton->isChecked()) {
        done(LINE_MAGENTA);
    } else if (ui->yellowRadioButton->isChecked()) {
        done(LINE_YELLOW);
    } else {
        done(LINE_RED);
    }
}

void LineSelectionDialog::reject() {
    done(LINE_CANCEL);
}
