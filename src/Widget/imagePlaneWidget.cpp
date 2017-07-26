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
	unsetActiveROD();
	vtkImagePlaneWidget::OnMiddleButtonDown(); // forward events
}

void ImagePlaneWidget::OnRightButtonUp() {
	moving = false;
	vtkImagePlaneWidget::OnMiddleButtonUp(); // forward events
}

void ImagePlaneWidget::unsetActiveROD() {
	if (activeROD != NULL && listROD != NULL) {
		activeROD->hideAll();
		listROD->setCurrentItem(nullROD);
		activeROD = NULL;
		nullROD->setSelected(true);
	}
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

void ImagePlaneWidget::setActiveROD(ROD* activeROD) {
	this->activeROD = activeROD;
}

void ImagePlaneWidget::setListROD(QListWidget* listROD) {
	this->listROD = listROD;
}

void ImagePlaneWidget::setNullROD(QListWidgetItem* nullROD) {
	this->nullROD = nullROD;
}
