#ifndef INTERACTORSTYLEIMAGE_H
#define INTERACTORSTYLEIMAGE_H

#include <QLabel>
#include <QPixmap>
#include <QBitmap>

#include <vtkObjectFactory.h>
#include <vtkSmartPointer.h>
#include <vtkInteractorStyleImage.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkCellPicker.h>

#include "Core/SlicePlane.h"
#include "Core/Sculpture.h"

/**
 * @class InteractorStyleImage
 * Class that inherits from vtkInteractorStyleImage and overrides the left button click mouse event to not change the color and window level and 
 * the mouse move event to show density value of a voxel
 */
class InteractorStyleImage : public vtkInteractorStyleImage {
public:
	/**
	 * Constructor
	 */
	static InteractorStyleImage* New();

	vtkTypeMacro(vtkInteractorStyleImage, InteractorStyleImage);
	
	/**
	 * Set plane in which will find the value of the voxel selected
	 * @param	slicePlane	Plane in which will find the value of the voxel selected
	 */
	void SetSlicePlane(SlicePlane* slicePlane);

	/**
	 * Set the QLabel where the density value will be shown
	 * @param	label	QLabel where the density value will be shown
	 */
	void SetLabel(QLabel* label);
	
	/**
	 * Mouse move event
	 */
	virtual void OnMouseMove();

	/**
	 * Left button down mouse event
	 */
	virtual void OnLeftButtonDown();

private:
	SlicePlane* slicePlane; /**< Plane in which will find the value of the voxel selected */
	QLabel* label; /**< QLabel where the density value will be shown */
};

#endif // INTERACTORSTYLEIMAGE_H