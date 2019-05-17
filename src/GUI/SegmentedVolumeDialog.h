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
    explicit SegmentedVolumeDialog(vtkSmartPointer<vtkImageData> imageData, TransferFunction* tf, QColor background, QWidget *parent = nullptr);

    /**
     * Destructor
     */
    ~SegmentedVolumeDialog() override;

    /**
     * Render volume with its transfer function
     */
    void render();

private slots:
    /**
     * Ok button selected
     */
    void accept() override;

    /**
     * Cancel button selected
     */
    void reject() override;

private:
    Ui::SegmentedVolumeDialog *ui; /**< Dialog GUI pointer */
    vtkSmartPointer<vtkImageData> imageData; /**< Image data that will be displayed */
    TransferFunction *tf; /**< Transfer function to render the volume */
    QColor background; /**< Widget background color */
};

#endif // SEGMENTEDVOLUMEDIALOG_H
