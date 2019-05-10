#include "ColorTransferControlPointsItem.h"

vtkStandardNewMacro(ColorTransferControlPointsItem)

bool ColorTransferControlPointsItem::MouseButtonReleaseEvent(const vtkContextMouseEvent &mouse) {
    bool result = vtkColorTransferControlPointsItem::MouseButtonReleaseEvent(mouse); // forward events
    if (mouse.GetButton() == vtkContextMouseEvent::LEFT_BUTTON			// if point added (left button)
        || mouse.GetButton() == vtkContextMouseEvent::MIDDLE_BUTTON) {	// or deleted (middle button) --> render
        renWin->Render();
    }
    return result;
}

bool ColorTransferControlPointsItem::KeyReleaseEvent(const vtkContextKeyEvent &key) {
    bool result = vtkColorTransferControlPointsItem::KeyReleaseEvent(key); // forward events
    if (key.GetInteractor()->GetKeySym() == std::string("Delete")			// if point deleted (delete key)
        || key.GetInteractor()->GetKeySym() == std::string("BackSpace")) {	// or (back space key) --> render
        renWin->Render();
    }
    return result;
}

bool ColorTransferControlPointsItem::MouseDoubleClickEvent(const vtkContextMouseEvent &mouse) {
    if (mouse.GetButton() == vtkContextMouseEvent::LEFT_BUTTON) { // double left button click --> color change
        double values[6];
        ColorTransferFunction->GetNodeValue(this->GetCurrentPoint(), values); // previous color
        QColor color = QColor::fromRgbF(values[1], values[2], values[3]);
        color = QColorDialog::getColor(color); // new color
        if (color.isValid()) {
            values[1] = color.redF();
            values[2] = color.greenF();
            values[3] = color.blueF();
            ColorTransferFunction->SetNodeValue(this->GetCurrentPoint(), values);
        }
    }
    return vtkColorTransferControlPointsItem::MouseDoubleClickEvent(mouse); // forward events
}

void ColorTransferControlPointsItem::SetRenderWindow(const vtkSmartPointer<vtkRenderWindow> &rw) {
    this->renWin = rw;
}
