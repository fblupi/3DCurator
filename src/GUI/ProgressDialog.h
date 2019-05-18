#ifndef PROGRESSDIALOG_H
#define PROGRESSDIALOG_H

#include <QApplication>
#include <QIcon>
#include <QPointer>
#include <QProgressBar>
#include <QProgressDialog>

/**
 * @class ProgressDialog
 * Progress dialog to be shown when a long task is running
 */
class ProgressDialog {
public:
    /**
     * Constructor
     * @param title         Title of the dialog
     * @param description   Text of the dialog
     */
    ProgressDialog(const QString &title, const QString &description);

    /**
     * Destructor
     */
    ~ProgressDialog();

    /**
     * Shows the dialog
     */
    void show();

    /**
     * Close the dialog
     */
    void close();

private:
    QPointer<QProgressBar> bar; /**< Bar pointer */
    QPointer<QProgressDialog> progressDialog; /**< Dialog pointer */
};

#endif // PROGRESSDIALOG_H
