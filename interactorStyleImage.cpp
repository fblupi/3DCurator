#include "interactorStyleImage.h"

#include "measures.h"
#include <stack>
#include <vtkVolumePicker.h>
#include <vtkResliceCursorPicker.h>
#include <vtkPointPlacer.h>
#include <vtkRenderer.h>

vtkStandardNewMacro(InteractorStyleImage);

bool isInLine(double a, double b, double m, double n) {
	double result = b - (m * a + n);
	if (result >= -LINE_TOLERANCE && result <= LINE_TOLERANCE) {
		return true;
	} else {
		return false;
	}
}

bool isAdjacent(Figura *figura, double x, double y, double z, double MIN, double MAX) {
	double value = figura->getImageData()->GetScalarComponentAsFloat(x, y, z, 0);
	if (value >= MIN && value <= MAX)
		return true;
	else
		return false;
}

void regionGrowingWithLineBound(Figura *figura, const int ijk[3], const int MIN_X, const int MAX_X, const int MIN_Y, const int MAX_Y) {
	std::pair<int, int> ij;
	std::stack<std::pair<int, int>> stack;

	ij.first = ijk[0]; ij.second = ijk[1]; // voxel inicial

	stack.push(ij); // añade el primer voxel
	while (!stack.empty()) { // continua hasta vaciar la pila
		ij = stack.top(); // primer elemento de la pila
		stack.pop(); // elimina el primer elemento de la pila
		if (ij.first < MAX_X && ij.first >= MIN_X && ij.second < MAX_Y && ij.second >= MIN_Y) { // se encuentra entre los límites
			if (isAdjacent(figura, ij.first, ij.second, ijk[2], -750, -350) 
				&& !isInLine(ij.first, ij.second, 4.4808, -741.7115)) {
				figura->getImageData()->SetScalarComponentFromFloat(ij.first, ij.second, ijk[2], 0, AIR_HU); // actualiza el voxel con el valor del aire
																								 // añade a la pila los voxeles de alrededor
				stack.push(std::make_pair(ij.first - 1, ij.second - 1));
				stack.push(std::make_pair(ij.first - 1, ij.second));
				stack.push(std::make_pair(ij.first - 1, ij.second + 1));
				stack.push(std::make_pair(ij.first, ij.second - 1));
				stack.push(std::make_pair(ij.first, ij.second + 1));
				stack.push(std::make_pair(ij.first + 1, ij.second - 1));
				stack.push(std::make_pair(ij.first + 1, ij.second));
				stack.push(std::make_pair(ij.first + 1, ij.second + 1));
			}
		}
	}
}


void InteractorStyleImage::OnLeftButtonDown() {
	if (plano != NULL && label != NULL && this->GetDefaultRenderer() != NULL) { // se han establecido los elementos necesarios
		vtkSmartPointer<vtkVolumePicker> picker = vtkSmartPointer<vtkVolumePicker>::New();
		int* pos = this->GetInteractor()->GetEventPosition(); // posición del ratón en el render window
		picker->Pick(pos[0], pos[1], pos[2], this->GetDefaultRenderer()); // realiza pick sobre la posición del ratón en el render window

		int* ijk = picker->GetPointIJK();
		ijk[2] = plano->getPlane()->GetCenter()[2] / figura->getImageData()->GetSpacing()[2];

		if (picker->GetPointId() != -1) { // se ha seleccionado un voxel
			label->setText(QString::fromStdString("Borrando")); // actualiza el valor de la etiqueta
			int * dimensions = figura->getImageData()->GetDimensions();
			regionGrowingWithLineBound(figura, ijk, 0, dimensions[0], 0, dimensions[1]); // borra
			figura->getImageData()->Modified(); // actualiza tiempo de modificación para que el mapper recalcule los datos del volumen
		}

	}
}

void InteractorStyleImage::OnMouseMove() {

	vtkInteractorStyleImage::OnMouseMove(); // Forward events
}

void InteractorStyleImage::SetPlano(Plano* plano) {
	this->plano = plano;
}

void InteractorStyleImage::SetLabel(QLabel* label) {
	this->label = label;
}

void InteractorStyleImage::SetFigura(Figura* figura) {
	this->figura = figura;
}