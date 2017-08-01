#ifndef FILTERSELECTIONDIALOG_H
#define FILTERSELECTIONDIALOG_H

#include <QDialog>
#include <QPixmap>
#include <QBitmap>

#define	CANCEL		-1
#define GAUSSIAN	0
#define MEAN		1
#define	MEDIAN		2
#define N_3x3		0
#define N_5x5		1
#define N_7x7		2

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
	unsigned int getGaussianReps() const;

	/**
	 * Get the radius of the neigbourhood for mean filter 1 for 3x3, 2 for 5x5 and 3 for 7x7
	 * @return	Radius of the neigbourhood for mean filter
	 */
	unsigned int getMeanRadius() const;

	/**
	 * Get the radius of the neigbourhood for median filter 1 for 3x3, 2 for 5x5 and 3 for 7x7
	 * @return	Radius of the neigbourhood for median filter
	 */
	unsigned int getMedianRadius() const;

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
	 * User has changed the tab page
	 */
	void on_filtersTab_currentChanged();

private:
	Ui::FilterSelectionDialog *ui; /**< Dialog GUI pointer */
	int filterType = GAUSSIAN; /**< Filter selected */
};

#endif // FILTERSELECTIONDIALOG_H
