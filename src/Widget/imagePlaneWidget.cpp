#include "ImagePlaneWidget.h"

vtkStandardNewMacro(ImagePlaneWidget);

void ImagePlaneWidget::OnMouseMove() {
	if (moving && viewer != NULL) {
		viewer->Render();
	}
	vtkImagePlaneWidget::OnMouseMove(); 
}

void ImagePlaneWidget::OnRightButtonDown() {
	moving = true;
	vtkImagePlaneWidget::OnMiddleButtonDown(); // forward events
}

void ImagePlaneWidget::OnRightButtonUp() {
	moving = false;
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