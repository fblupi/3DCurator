#ifndef PREFERENCESDIALOG_H
#define PREFERENCESDIALOG_H

#include <QDialog>
#include <QSettings>
#include <QString>

#include "Settings/Language.h"

namespace Ui {
    class PreferencesDialog;
}

/**
 * @class PreferencesDialog
 * Class of the filter selection dialog
 */
class PreferencesDialog : public QDialog {
    Q_OBJECT

public:
    /**
     * Constructor
     */
    explicit PreferencesDialog(QSettings *settings, Language *language, QWidget *parent = nullptr);

    /**
     * Destructor
     */
    ~PreferencesDialog() override;

private slots:
    /**
     * Ok button selected
     */
    void accept() override;

    /**
     * Cancel button selected
     */
    void reject() override;

    /**
     * Get locale from index
     * @params index	index of the locale in the QCombo
     */
    static QString getLocaleFromIndex(int index);

    /**
     * Get index from locale
     * @params locale	locale of the language
     */
    static int getIndexFromLocale(const QString &locale);

private:
    Ui::PreferencesDialog *ui; /**< Dialog GUI pointer */
    QSettings *settings; /**< Settings pointer */
    Language *language; /**< Language pointer */
};

#endif // PREFERENCESDIALOG_H
