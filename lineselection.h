#ifndef LINESELECTION_H
#define LINESELECTION_H

#include <QDialog>

namespace Ui {
	class LineSelection;
}

class LineSelection : public QDialog {
	Q_OBJECT

public:
	explicit LineSelection(QWidget *parent = 0);
	~LineSelection();

private:
	Ui::LineSelection *ui;
};

#endif // LINESELECTION_H
