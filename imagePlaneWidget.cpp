#include "imagePlaneWidget.h"

vtkStandardNewMacro(ImagePlaneWidget);

void ImagePlaneWidget::OnMouseMove() {
	if (moving && viewer != NULL) { // si se está moviendo --> renderiza
		viewer->Render(); // renderiza
	}
	vtkImagePlaneWidget::OnMouseMove(); // forward events
}

void ImagePlaneWidget::OnRightButtonDown() {
	moving = true; // cuando pulsa el botón derecho del ratón --> empieza a mover
	vtkImagePlaneWidget::OnMiddleButtonDown(); // forward events
}

void ImagePlaneWidget::OnRightButtonUp() {
	moving = false; // cuando suelta el botón derecho del ratón --> deja de mover
	vtkImagePlaneWidget::OnMiddleButtonUp(); // forward events
}

void ImagePlaneWidget::OnMiddleButtonDown() {
	// idle
}

void ImagePlaneWidget::OnMiddleButtonUp() {
	// idle
}

void ImagePlaneWidget::OnLeftButtonDown() {
	// idle
}

void ImagePlaneWidget::OnLeftButtonUp() {
	// idle
}

void ImagePlaneWidget::SetViewer(vtkSmartPointer<vtkImageViewer2> viewer) {
	this->viewer = viewer;
}