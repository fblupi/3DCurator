#ifndef SLICEPLANE_H
#define SLICEPLANE_H

#include <vtkObjectFactory.h>
#include <vtkSmartPointer.h>
#include <vtkImagePlaneWidget.h>
#include <vtkImageViewer2.h>
#include <vtkImageData.h>

#include "Widget/ImagePlaneWidget.h"

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
     * Get the origin of the plane
     * @return	Origin of the plane
     */
    double* getOrigin() const;

    /**
     * Get the position of the point defining the first axis of the plane
     * @return	Position of the point defining the first axis of the plane
     */
    double* getPoint1() const;

    /**
     * Get the position of the point defining the first second of the plane
     * @return	Position of the point defining the second axis of the plane
     */
    double* getPoint2() const;

    /**
     * Get slice position in terms of data extent
     * @return	Slice position in terms of data extent
     */
    double getSlicePosition() const;

    /**
     * Set connection with the volume
     * @param	imageData	Volume data
     */
    void setInputData(const vtkSmartPointer<vtkImageData> &imageData);

    /**
     * Set viewer where slices will be shown
     * @param	viewer	Viewer where slices will be shown
     */
    void setViewer(const vtkSmartPointer<vtkImageViewer2> &viewer);

    /**
     * Makes the plane visible/invisible
     * @param	onOff	Visibility on or off
     */
    void enable(bool onOff);

    /**
     * Makes visible the slice with the volume
     * @param	onOff	Visibility on or off
     */
    void show(bool onOff);

    /**
     * Set the origin of the plane in a point
     * @param	x	X coordinate
     * @param	y	Y coordinate
     * @param	z	Z coordinate
     */
    void setOrigin(double x, double y, double z);

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

    /**
     * Set the plane in a custom position
     * @param	origin	Origin of the plane
     * @param	point1	Position of the point defining the first axis of the plane
     * @param	point2	Position of the point defining the second axis of the plane
     * @param	slice	Slice position in terms of data extent
     */
    void setCustomPosition(const double* origin, const double* point1, const double* point2, double slice);

private:
    vtkSmartPointer<ImagePlaneWidget> plane; /**< Cutting plane in the sculpture data */
    double *centers; /**< Center positions for sagital, coronal and axial planes */
};

#endif // SLICEPLANE_H
