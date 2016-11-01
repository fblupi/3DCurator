#include "piecewiseControlPointsItem.h"

vtkStandardNewMacro(PiecewiseControlPointsItem);

bool PiecewiseControlPointsItem::MouseButtonReleaseEvent(const vtkContextMouseEvent &mouse) {
	bool result = vtkPiecewiseControlPointsItem::MouseButtonReleaseEvent(mouse); // forward events
	if (mouse.GetButton() == vtkContextMouseEvent::LEFT_BUTTON			// si se ha soltado el botón izquierdo (añade punto)
		|| mouse.GetButton() == vtkContextMouseEvent::MIDDLE_BUTTON) {	// o el central (borra) --> renderiza
		renWin->Render();
	}
	return result;
}

bool PiecewiseControlPointsItem::KeyReleaseEvent(const vtkContextKeyEvent &key) {
	bool result = vtkPiecewiseControlPointsItem::KeyReleaseEvent(key); // forward events
	if (key.GetInteractor()->GetKeySym() == std::string("Delete")			// si se ha pulsado la tecla "Delete"
		|| key.GetInteractor()->GetKeySym() == std::string("BackSpace")) {	// o "BlackSpace" (borra punto) --> renderiza
		renWin->Render();
	}
	return result;
}

void PiecewiseControlPointsItem::SetRenderWindow(vtkSmartPointer<vtkRenderWindow> renWin) {
	this->renWin = renWin;
}