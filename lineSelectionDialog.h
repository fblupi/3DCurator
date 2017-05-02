#ifndef LINESELECTIONDIALOG_H
#define LINESELECTIONDIALOG_H

#include <QDialog>
#include <QPixmap>
#include <QBitmap>

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

class LineSelectionDialog : public QDialog {
	Q_OBJECT

public:
	explicit LineSelectionDialog(QWidget *parent = 0);
	~LineSelectionDialog();
	void setImage(std::string filename);

private slots:
	void accept();
	void reject();

private:
	Ui::LineSelectionDialog *ui;
};

#endif // LINESELECTIONDIALOG_H
