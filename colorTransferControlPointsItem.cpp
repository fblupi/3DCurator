#include "colorTransferControlPointsItem.h"

vtkStandardNewMacro(ColorTransferControlPointsItem);

bool ColorTransferControlPointsItem::MouseButtonReleaseEvent(const vtkContextMouseEvent &mouse) {
	bool result = vtkColorTransferControlPointsItem::MouseButtonReleaseEvent(mouse); // forward events
	if (mouse.GetButton() == vtkContextMouseEvent::LEFT_BUTTON			// si se ha soltado el botón izquierdo (añade punto)
		|| mouse.GetButton() == vtkContextMouseEvent::MIDDLE_BUTTON) {	// o el central (borra) --> renderiza
		renWin->Render();
	}
	return result;
}

bool ColorTransferControlPointsItem::KeyReleaseEvent(const vtkContextKeyEvent &key) {
	bool result = vtkColorTransferControlPointsItem::KeyReleaseEvent(key); // forward events
	if (key.GetInteractor()->GetKeySym() == std::string("Delete")			// si se ha pulsado la tecla "Delete"
		|| key.GetInteractor()->GetKeySym() == std::string("BackSpace")) {	// o "BlackSpace" (borra punto) --> renderiza
		renWin->Render();
	}
	return result;
}

bool ColorTransferControlPointsItem::MouseDoubleClickEvent(const vtkContextMouseEvent &mouse) {
	if (mouse.GetButton() == vtkContextMouseEvent::LEFT_BUTTON) { // si se hace doble click sobre el botón izquierdo --> cambia color
		double values[6];
		ColorTransferFunction->GetNodeValue(this->GetCurrentPoint(), values); // obtiene los valores para el punto seleccionado
		QColor color = QColor::fromRgbF( // color por defecto con el color del punto seleccionado
			values[1],	// componente roja del punto seleccionado
			values[2],	// verde
			values[3]	// y azul
			);
		color = QColorDialog::getColor(color); // obtiene el color elegido por el usuario, dando por defecto el que tiene en ese momento
		if (color.isValid()) { // se ha seleccionado un color
			values[1] = color.redF();	// cambia el valor de la componente roja del color
			values[2] = color.greenF();	// el de la componente verde
			values[3] = color.blueF();	// y el de la azul
			ColorTransferFunction->SetNodeValue(this->GetCurrentPoint(), values); // actualiza valores
		}
	}
	return vtkColorTransferControlPointsItem::MouseDoubleClickEvent(mouse); // forward events
}

void ColorTransferControlPointsItem::SetRenderWindow(vtkSmartPointer<vtkRenderWindow> renWin) {
	this->renWin = renWin;
}