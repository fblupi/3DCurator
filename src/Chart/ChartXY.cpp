#include "ChartXY.h"

vtkStandardNewMacro(ChartXY)

bool ChartXY::MouseEnterEvent(const vtkContextMouseEvent &mouse) {
    return true; // idle
}

bool ChartXY::MouseMoveEvent(const vtkContextMouseEvent &mouse) {
    return true; // idle
}

bool ChartXY::MouseLeaveEvent(const vtkContextMouseEvent &mouse) {
    return true; // idle
}

bool ChartXY::MouseButtonPressEvent(const vtkContextMouseEvent &mouse) {
    return true; // idle
}

bool ChartXY::MouseButtonReleaseEvent(const vtkContextMouseEvent &mouse) {
    return true; // idle
}

bool ChartXY::MouseWheelEvent(const vtkContextMouseEvent &mouse, int delta) {
    return true; // idle
}
