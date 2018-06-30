#include "InteractorStyleImage.h"

vtkStandardNewMacro(InteractorStyleImage);

void InteractorStyleImage::OnMouseMove() {
	if (slicePlane != NULL && label != NULL && this->GetDefaultRenderer() != NULL) {
		vtkSmartPointer<vtkCellPicker> picker = vtkSmartPointer<vtkCellPicker>::New();
		picker->SetTolerance(0.0005);

		int* pos = this->GetInteractor()->GetEventPosition();
		picker->Pick(pos[0], pos[1], pos[2], this->GetDefaultRenderer());

		int* ijk = picker->GetPointIJK();

		if (picker->GetPointId() != -1) { // a voxel has been selected
			float value = slicePlane->getPlane()->GetResliceOutput()->GetScalarComponentAsFloat(ijk[0], ijk[1], ijk[2], 0);
			label->setText(QString::fromStdString("HU: " + std::to_string((int)value)));
		} else {
			label->setText(QCoreApplication::translate("MainWindow", "HU_OUT_OF_RANGE"));
		}
	}
	vtkInteractorStyleImage::OnMouseMove(); // Forward events
}

void InteractorStyleImage::OnLeftButtonDown() {
	// idle
}

void InteractorStyleImage::SetSlicePlane(SlicePlane* plane) {
	this->slicePlane = plane;
}

void InteractorStyleImage::SetLabel(QLabel* label) {
	this->label = label;
}