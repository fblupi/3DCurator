#ifndef SLICEPLANE_H
#define SLICEPLANE_H

#include <vtkObjectFactory.h>
#include <vtkSmartPointer.h>
#include <vtkImagePlaneWidget.h>
#include <vtkImageViewer2.h>
#include <vtkImageData.h>

#include "Widget/imagePlaneWidget.h"

/** 
 * @class SlicePlane
 * Class with the cutting plane in the sculpture data
 */
class SlicePlane {
public:
	/**
	 * Constructor
	 */
	SlicePlane();

	/**
	 * Destructor
	 */
	~SlicePlane();

	/**
	 * GetPlane
	 * @return	Pointer to ImagePlaneWidget
	 */
	vtkSmartPointer<ImagePlaneWidget> getPlane() const;

	/**
	 * Set connection with the volue
	 * @param	imageData	Volume data
	 */
	void setInputData(vtkSmartPointer<vtkImageData> imageData);

	/** 
	 * Set viewer where slices will be shown
	 * @param	viewer	Viewer where slices will be shown
	 */
	void setViewer(vtkSmartPointer<vtkImageViewer2> viewer);

	/**
	 * Makes the plane visible/invisible
	 * @param	onOff	Visibility on or off
	 */
	void enable(const bool onOff);

	/**
	 * Makes visible the slice with the volume
	 * @param	onOff	Visibility on or off
	 */
	void show(const bool onOff);

	/**
	 * Set the origin of the plane in a point
	 * @param	x	X coordinate
	 * @param	y	Y coordinate
	 * @param	z	Z coordinate
	 */
	void setOrigin(const double x, const double y, const double z);

	/**
	 * Set the plane in sagital position (YZ axis)
	 */
	void setSagital();

	/**
	 * Set the plane in coronal position (XZ axis)
	 */
	void setCoronal();

	/**
	 * Set the plane in axial position (XY axis)
	 */
	void setAxial();

private:
	vtkSmartPointer<ImagePlaneWidget> plane; /**< Cutting plane in the sculpture data */
	double centers[3]; /**< Center positions for sagital, coronal and axial planes */
};

#endif // SLICEPLANE_H