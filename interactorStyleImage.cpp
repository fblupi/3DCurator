#include "interactorStyleImage.h"

vtkStandardNewMacro(InteractorStyleImage);

void InteractorStyleImage::OnLeftButtonDown() {
	// idle
}

void InteractorStyleImage::OnMouseMove() {
	if (plano != NULL && label != NULL && this->GetDefaultRenderer() != NULL) { // se han establecido los elementos necesarios
		vtkSmartPointer<vtkCellPicker> picker = vtkSmartPointer<vtkCellPicker>::New();
		picker->SetTolerance(0.0005); // ajusta la torlerancia

		int* pos = this->GetInteractor()->GetEventPosition(); // posición del ratón en el render window
		picker->Pick(pos[0], pos[1], pos[2], this->GetDefaultRenderer()); // realiza pick sobre la posición del ratón en el render window

		int* ijk = picker->GetPointIJK(); // voxel seleccionado

		if (picker->GetPointId() != -1) { // se ha seleccionado un voxel
			float value = plano->getPlane()->GetResliceOutput()->GetScalarComponentAsFloat(ijk[0], ijk[1], ijk[2], 0); // valor escalar del voxel
			label->setText(QString::fromStdString("HU: " + std::to_string((int) value))); // actualiza el valor de la etiqueta con el valor del voxel
		} else {
			label->setText(QString::fromStdString("HU: Fuera de rango")); // actualiza el valor de la etiqueta
		}
	}
	vtkInteractorStyleImage::OnMouseMove(); // Forward events
}

void InteractorStyleImage::SetPlano(Plano* plano) {
	this->plano = plano;
}

void InteractorStyleImage::SetLabel(QLabel* label) {
	this->label = label;
}