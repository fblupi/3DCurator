#include "plano.h"

Plano::Plano() {
	plane = vtkSmartPointer<ImagePlaneWidget>::New();
	centers[0] = centers[1] = centers[2] = 0.0; // el centro inicial es el 0
}

void Plano::setSagital() {
	// coloca el plano sobre los ejes YZ (pero hay que darle la vuelta)
	plane->SetPlaneOrientationToXAxes();
	plane->SetSlicePosition(centers[0]);

	// obtiene los puntos del plano
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

	// hace un giro de 180º sobre el eje X
	plane->SetPoint1(p1[0], p2[1], p2[2]);
	plane->SetPoint2(p1[0], p1[1], p1[2]);
	plane->SetOrigin(p1[0], p1[1], p2[2]);

	plane->UpdatePlacement(); // actualiza el plano con los nuevos puntos y origen
}

void Plano::setCoronal() {
	// coloca el plano sobre los ejes YZ (pero hay que darle la vuelta y ponerlo sobre el XZ)
	plane->SetPlaneOrientationToXAxes();
	plane->SetSlicePosition(centers[0]);

	// obtiene los puntos del plano sagital
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

	// hace un giro de 180º sobre el eje X y otro de 90º sobre el eje Z
	plane->SetPoint1(p2[1], p1[0], p2[2]);
	plane->SetPoint2(p1[1], p1[0], p1[2]);
	plane->SetOrigin(p1[1], p1[0], p2[2]);

	plane->UpdatePlacement(); // actualiza el plano con los nuevos puntos y origen
}

void Plano::setAxial() {
	// coloca el plano sobre los ejes XY
	plane->SetPlaneOrientationToZAxes();
	plane->SetSlicePosition(centers[2]);
}

void Plano::setOrigin(const double x, const double y, const double z) {
	plane->SetOrigin(x, y, z);
	// actualiza el centro
	centers[0] = x;
	centers[1] = y;
	centers[2] = z;
}

void Plano::show(const bool onOff) {
	plane->SetTextureVisibility(onOff); // muestra la imagen del corte
}

void Plano::enable(const bool onOff) {
	plane->SetEnabled(onOff);
}

void Plano::setInputData(vtkSmartPointer<vtkImageData> imageData) {
	plane->SetInputData(imageData);
}

void Plano::setViewer(vtkSmartPointer<vtkImageViewer2> viewer) {
	plane->SetViewer(viewer);
}

vtkSmartPointer<ImagePlaneWidget> Plano::getPlane() const {
	return plane;
}