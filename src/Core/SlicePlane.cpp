#include "SlicePlane.h"

SlicePlane::SlicePlane() :
    plane(vtkSmartPointer<ImagePlaneWidget>::New()),
    centers(new double[3])
{
    centers[0] = centers[1] = centers[2] = 0.0;
}

SlicePlane::~SlicePlane() = default;

void SlicePlane::setSagital() {
    // Set plane in YZ axes (but we have to turn it around)
    plane->SetPlaneOrientationToXAxes();
    plane->SetSlicePosition(centers[0]);

    // plane points
    double p1[3] = { plane->GetPoint1()[0], plane->GetPoint1()[1], plane->GetPoint1()[2] };
    double p2[3] = { plane->GetPoint2()[0], plane->GetPoint2()[1], plane->GetPoint2()[2] };

    // Turn 180° over X axis
    plane->SetPoint1(p1[0], p2[1], p2[2]);
    plane->SetPoint2(p1[0], p1[1], p1[2]);
    plane->SetOrigin(p1[0], p1[1], p2[2]);

    plane->UpdatePlacement();
}

void SlicePlane::setCoronal() {
    // Set plane in YZ axes (but we have to turn it around and set to XZ axis)
    plane->SetPlaneOrientationToXAxes();
    plane->SetSlicePosition(centers[0]);

    // plane points
    double p1[3] = {
        plane->GetPoint1()[0],
        plane->GetPoint1()[1],
        plane->GetPoint1()[2]
    };
    double p2[3] = {
        plane->GetPoint2()[0],
        plane->GetPoint2()[1],
        plane->GetPoint2()[2]
    };

    // Turn 180° over X axis and 90° over Z axis
    plane->SetPoint1(p2[1], p1[0], p2[2]);
    plane->SetPoint2(p1[1], p1[0], p1[2]);
    plane->SetOrigin(p1[1], p1[0], p2[2]);

    plane->UpdatePlacement();
}

void SlicePlane::setAxial() {
    // Set plane in XY axes
    plane->SetPlaneOrientationToZAxes();
    plane->SetSlicePosition(centers[2]);
}

void SlicePlane::setCustomPosition(const double* origin, const double* point1, const double* point2, double slice) {
    plane->SetOrigin(origin[0], origin[1], origin[2]);
    plane->SetPoint1(point1[0], point1[1], point1[2]);
    plane->SetPoint2(point2[0], point2[1], point2[2]);
    plane->SetSlicePosition(slice);

    plane->UpdatePlacement();
}

void SlicePlane::setOrigin(double x, double y, double z) {
    plane->SetOrigin(x, y, z);

    centers[0] = x;
    centers[1] = y;
    centers[2] = z;
}

void SlicePlane::show(bool onOff) {
    plane->SetTextureVisibility(onOff);
}

void SlicePlane::enable(bool onOff) {
    plane->SetEnabled(onOff);
}

void SlicePlane::setInputData(const vtkSmartPointer<vtkImageData> &imageData) {
    plane->SetInputData(imageData);
}

void SlicePlane::setViewer(const vtkSmartPointer<vtkImageViewer2> &viewer) {
    plane->SetViewer(viewer);
}

vtkSmartPointer<ImagePlaneWidget> SlicePlane::getPlane() const {
    return plane;
}

double* SlicePlane::getOrigin() const {
    return plane->GetOrigin();
}

double* SlicePlane::getPoint1() const {
    return plane->GetPoint1();
}

double* SlicePlane::getPoint2() const {
    return plane->GetPoint2();
}

double SlicePlane::getSlicePosition() const {
    return plane->GetSlicePosition();
}
