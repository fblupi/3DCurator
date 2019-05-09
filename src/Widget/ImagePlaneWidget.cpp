#include "ImagePlaneWidget.h"

vtkStandardNewMacro(ImagePlaneWidget)

void ImagePlaneWidget::OnMouseMove() {
    if (moving && viewer != nullptr) {
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
    if (activeROD != nullptr && listROD != nullptr) {
        activeROD->hideAll();
        listROD->setCurrentItem(nullptr);
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

void ImagePlaneWidget::SetViewer(const vtkSmartPointer<vtkImageViewer2> &v) {
    this->viewer = v;
}

void ImagePlaneWidget::setActiveROD(ROD* r) {
    this->activeROD = r;
}

void ImagePlaneWidget::setListROD(QListWidget* l) {
    this->listROD = l;
}
