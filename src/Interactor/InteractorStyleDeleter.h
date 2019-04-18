#ifndef INTERACTORSTYLEDELETER_H
#define INTERACTORSTYLEDELETER_H

#include <QProgressDialog>
#include <QIcon>
#include <QMessageBox>
#include <QAbstractButton>
#include <QPointer>
#include <QProgressBar>
#include <QApplication>
#include <QObject>
#include <QCoreApplication>

#include <vtkObjectFactory.h>
#include <vtkSmartPointer.h>
#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderWindow.h>
#include <vtkVolumePicker.h>
#include <vtkImageViewer2.h>

#include "Core/Sculpture.h"
#include "Core/SlicePlane.h"
#include "Segmentation/RegionGrowingDeleter.h"

/**
 * @class InteractorStyleDeleter
 * Class that inherits from vtkInteractorStyleTrackballCamera and deletes voxels using a region growing algorithm when a voxel
 * is picked.
 */
class InteractorStyleDeleter : public vtkInteractorStyleTrackballCamera {
public:
	/**
	 * Constructor
	 */
	static InteractorStyleDeleter* New();

	vtkTypeMacro(vtkInteractorStyleTrackballCamera, InteractorStyleDeleter);

	/**
	 * Set render window where we will pick a voxel
	 * @param	renWin	RenderWindow where we will pick a voxel
	 */
	void SetDefaultRenderWindow(vtkSmartPointer<vtkRenderWindow> renWin);

	/**
	 * Set ImageViewer2 that will be updated when delete
	 * @param	viewer	ImageViewer2 that will be updated when delete
	 */
	void SetViewer(vtkSmartPointer<vtkImageViewer2> viewer);

	/**
	 * Set sculpture where we will delete a region
	 * @param	sculpture	Sculpture where we will delete a region
	 */
	void SetSculpture(Sculpture* sculpture);

	/**
	 * Slice plane that will be updated when delete
	 * @param	slicePlane	Slice plane that will be updated when delete
	 */
	void SetSlicePlane(SlicePlane* slicePlane);

	/**
	 * Left button down event
	 */
	virtual void OnLeftButtonDown() override;

private:
	vtkSmartPointer<vtkRenderWindow> renWin; /**< Render Window where the sculpture is rendered */
	vtkSmartPointer<vtkImageViewer2> viewer; /**< ImageViewer2 that will be updated when delete */
	Sculpture* sculpture; /**< Sculpture where we will delete a region */
	SlicePlane* slicePlane; /**< Slice plane that will be updated when delete */
};

#endif // INTERACTORSTYLEDELETER_H