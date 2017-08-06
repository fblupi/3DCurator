#ifndef SEGMENTEDVOLUMEDIALOG_H
#define SEGMENTEDVOLUMEDIALOG_H

#include <vtkSmartPointer.h>
#include <vtkImageData.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkSmartVolumeMapper.h>
#include <vtkVolumeProperty.h>

#include <QDialog>
#include <QPixmap>
#include <QBitmap>
#include <QMessageBox>
#include <QFileDialog>

#include <Core/TransferFunction.h>

namespace Ui {
	class SegmentedVolumeDialog;
}

/**
 * @class SegmentedVolumeDialog
 * Class of the line selection dialog
 */
class SegmentedVolumeDialog : public QDialog {
	Q_OBJECT

public:
	/**
	 * Constructor
	 */
	explicit SegmentedVolumeDialog(QWidget *parent = 0);

	/**
	 * Destructor
	 */
	~SegmentedVolumeDialog();

	/**
	 * Set 3D image data that will ve displayed
	 * @params	imageData	3D image data
	 */
	void setImageData(vtkSmartPointer<vtkImageData> imageData);

	/**
	 * Set transfer function
	 * @params	tf	Transfer function
	 */
	void setTransferFunction(TransferFunction* tf);

	/**
	 * Render volume with its transfer function
	 */
	void render();

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
	Ui::SegmentedVolumeDialog *ui; /**< Dialog GUI pointer */
	vtkSmartPointer<vtkImageData> imageData; /**< Image data that will be displayed */
	TransferFunction *tf; /**< Transfer function to render the volume */
};

#endif // SEGMENTEDVOLUMEDIALOG_H
