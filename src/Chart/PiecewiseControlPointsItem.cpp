#include "PiecewiseControlPointsItem.h"

vtkStandardNewMacro(PiecewiseControlPointsItem)

bool PiecewiseControlPointsItem::MouseButtonReleaseEvent(const vtkContextMouseEvent &mouse) {
    bool result = vtkPiecewiseControlPointsItem::MouseButtonReleaseEvent(mouse); // forward events
    if (mouse.GetButton() == vtkContextMouseEvent::LEFT_BUTTON			// if point added (left button)
        || mouse.GetButton() == vtkContextMouseEvent::MIDDLE_BUTTON) {	// or deleted (middle button) --> render
        renWin->Render();
    }
    return result;
}

bool PiecewiseControlPointsItem::KeyReleaseEvent(const vtkContextKeyEvent &key) {
    bool result = vtkPiecewiseControlPointsItem::KeyReleaseEvent(key); // forward events
    if (key.GetInteractor()->GetKeySym() == std::string("Delete")			// if point deleted (delete key)
        || key.GetInteractor()->GetKeySym() == std::string("BackSpace")) {	// or (back space key) --> render
        renWin->Render();
    }
    return result;
}

void PiecewiseControlPointsItem::SetRenderWindow(const vtkSmartPointer<vtkRenderWindow> &rw) {
    this->renWin = rw;
}
