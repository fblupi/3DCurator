#ifndef PREFERENCESDIALOG_H
#define PREFERENCESDIALOG_H

#include <QDialog>
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
	explicit PreferencesDialog(Language *language, QWidget *parent = 0);

	/**
	 * Destructor
	 */
	~PreferencesDialog();

private slots:
	/**
	 * Ok button selected
	 */
	void accept();

	/** 
	 * Cancel button selected
	 */
	void reject();

	/**
	 * Get locale from index
	 * @params index	index of the locale in the QCombo
	 */
	QString getLocaleFromIndex(const int index);

	/**
	 * Get index from locale
	 * @params locale	locale of the language
	 */
	int getIndexFromLocale(const QString locale);

private:
	Ui::PreferencesDialog *ui; /**< Dialog GUI pointer */
	Language *language; /**< Language pointer */
	QString locale; /**< Selected locale */
};

#endif // PREFERENCESDIALOG_H
