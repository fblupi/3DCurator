#ifndef FILTERSELECTIONDIALOG_H
#define FILTERSELECTIONDIALOG_H

#include <QDialog>
#include <QPixmap>
#include <QBitmap>

#define	CANCEL		-1
#define GAUSSIAN	0
#define MEAN		1
#define	MEDIAN		2

namespace Ui {
	class FilterSelectionDialog;
}

/**
 * @class FilterSelectionDialog
 * Class of the filter selection dialog
 */
class FilterSelectionDialog : public QDialog {
	Q_OBJECT

public:
	/**
	 * Constructor
	 */
	explicit FilterSelectionDialog(QWidget *parent = 0);

	/**
	 * Destructor
	 */
	~FilterSelectionDialog();

	/**
	 * Get the number of repetitions for gaussian filter
	 * @return	Number of repetitions for gaussian filter
	 */
	int getGaussianReps() const;

private slots:
	/**
	 * Ok button selected
	 */
	void accept();

	/** 
	 * Cancel button selected
	 */
	void reject();

private:
	Ui::FilterSelectionDialog *ui; /**< Dialog GUI pointer */
};

#endif // FILTERSELECTIONDIALOG_H
