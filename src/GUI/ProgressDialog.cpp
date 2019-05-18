#include "ProgressDialog.h"

ProgressDialog::ProgressDialog(const QString &title, const QString &description) :
    bar(new QProgressBar()),
    progressDialog(new QProgressDialog())
{
    progressDialog->setWindowTitle(title);
    progressDialog->setLabelText(description);
    progressDialog->setWindowIcon(QIcon(":/icons/3DCurator.png"));
    progressDialog->setWindowFlags(progressDialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    progressDialog->setCancelButton(nullptr);
    progressDialog->setModal(true);
    progressDialog->setMinimumWidth(360);
    progressDialog->setBar(bar);
    bar->close();
}

ProgressDialog::~ProgressDialog() = default;

void ProgressDialog::show() {
    progressDialog->show();
    QApplication::processEvents(QEventLoop::ExcludeUserInputEvents);
}

void ProgressDialog::close() {
    progressDialog->close();
}
