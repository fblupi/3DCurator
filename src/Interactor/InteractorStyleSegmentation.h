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
	 * Set sculpture that we will segmentate
	 * @param	sculpture	Sculpture that we will segmentate
	 */
	void SetSculpture(Sculpture* sculpture);

	/**
	 * Left button down mouse event
	 */
	virtual void OnLeftButtonDown();

private:
	vtkSmartPointer<vtkImageViewer2> viewer; /**< ImageViewer2 that will be updated when segmentate */
	SlicePlane* slicePlane; /**< Plane in which will find the value of the voxel selected */
	Sculpture* sculpture; /**< Sculpture that we will segmentate */
};

#endif // INTERACTORSTYLESEGMENTATION_H