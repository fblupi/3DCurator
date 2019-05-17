#ifndef PREFERENCESDIALOG_H
#define PREFERENCESDIALOG_H

#include <QColor>
#include <QColorDialog>
#include <QDialog>
#include <QSettings>
#include <QString>

#include "GUI/MainWindow.h"
#include "Settings/Backgrounds.h"
#include "Settings/Language.h"

class MainWindow;

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
    explicit PreferencesDialog(QSettings *settings, Backgrounds *backgrounds, Language *language, QWidget *parent = nullptr);

    /**
     * Destructor
     */
    ~PreferencesDialog() override;

private slots:
    // GUI events
    void on_meshBackground_pressed();
    void on_volumeBackground_pressed();
    void on_volumeDeletingBackground_pressed();
    void on_volumeSegmentingBackground_pressed();

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
    Backgrounds *backgrounds; /**< Backgrounds pointer */
    Language *language; /**< Language pointer */

    /**
     * Set backgrounds' inputs
     */
    void setupBackgrounds();

    /**
     * Set language input
     */
    void setupLanguage();

    /**
     * Process language settings
     */
    void processLanguage();
};

#endif // PREFERENCESDIALOG_H
