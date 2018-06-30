#ifndef LINESELECTIONDIALOG_H
#define LINESELECTIONDIALOG_H

#include <QDialog>
#include <QPixmap>
#include <QBitmap>

// Line ids
#define LINE_CANCEL 0
#define LINE_RED 1
#define LINE_GREEN 2
#define LINE_BLUE 3
#define LINE_CYAN 4
#define LINE_MAGENTA 5
#define LINE_YELLOW 6

namespace Ui {
	class LineSelectionDialog;
}

/**
 * @class LineSelectionDialog
 * Class of the line selection dialog
 */
class LineSelectionDialog : public QDialog {
	Q_OBJECT

public:
	/**
	 * Constructor
	 */
	explicit LineSelectionDialog(QWidget *parent = 0);

	/**
	 * Destructor
	 */
	~LineSelectionDialog();

	/**
	 * Set image where lines will be painted
	 * @params	filename	filename of the image where the lines will be painted
	 */
	void setImage(std::string filename);

	/**
	 * Check if it is forced to segmentate every slice to the top
	 * @return	Force or not to segmentate every slice to the top
	 */
	bool getCompleteUp() const;

	/**
	 * Check if it is forced to segmentate every slice to the bottom
	 * @return	Force or not to segmentate every slice to the bottom
	 */
	bool getCompleteDown() const;

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
	Ui::LineSelectionDialog *ui; /**< Dialog GUI pointer */
};

#endif // LINESELECTIONDIALOG_H
