#ifndef INTERACTORSTYLESEGMENTATION_H
#define INTERACTORSTYLESEGMENTATION_H

#include <vector>
#include <array>
#include <stdio.h>

#include <QPixmap>
#include <QBitmap>
#include <QMessageBox>
#include <QProgressDialog>
#include <QProgressBar>
#include <QPointer>
#include <QIcon>
#include <QApplication>
#include <QObject>
#include <QCoreApplication>

#include <vtkObjectFactory.h>
#include <vtkSmartPointer.h>
#include <vtkInteractorStyleImage.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkCellPicker.h>
#include <vtkVolumePicker.h>
#include <vtkResliceCursorPicker.h>
#include <vtkPointPlacer.h>
#include <vtkRenderer.h>
#include <vtkXMLImageDataWriter.h>

#include "Core/SlicePlane.h"
#include "Core/Sculpture.h"
#include "Util/Measures.h"
#include "Util/Utils.h"
#include "GUI/LineSelectionDialog.h"
#include "GUI/SegmentedVolumeDialog.h"
#include "Segmentation/WoodSegmentation.h"
#include "Settings/Backgrounds.h"

/**
 * @class InteractorStyleSegmentation
 * Class that inherits from vtkInteractorStyleSegmentation and overrides left button mouse click event to launch segmentation process
 */
class InteractorStyleSegmentation : public vtkInteractorStyleImage {
public:
    /**
     * Constructor
     */
    static InteractorStyleSegmentation* New();

    vtkTypeMacro(vtkInteractorStyleImage, InteractorStyleSegmentation);

    /**
     * Set plane in which will find the value of the voxel selected
     * @param	slicePlane	Plane in which will find the value of the voxel selected
     */
    void SetSlicePlane(SlicePlane* slicePlane);

    /**
     * Set sculpture that we will segment
     * @param	sculpture	Sculpture that we will segment
     */
    void SetSculpture(Sculpture* sculpture);

    /**
     * Set backgrounds with the background color info
     * @param backgrounds   Backgrounds with the background color info
     */
    void SetBackgrounds(Backgrounds* backgrounds);

    /**
     * Left button down mouse event
     */
    void OnLeftButtonDown() override;

private:
    vtkSmartPointer<vtkImageViewer2> viewer; /**< ImageViewer2 that will be updated when segment */
    SlicePlane* slicePlane; /**< Plane in which will find the value of the voxel selected */
    Sculpture* sculpture; /**< Sculpture that we will segment */
    Backgrounds* backgrounds; /**< Backgrounds pointer */
};

#endif // INTERACTORSTYLESEGMENTATION_H
