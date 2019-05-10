#ifndef PIECEWISECONTROLPOINTSITEM_H
#define PIECEWISECONTROLPOINTSITEM_H

#include <vtkPiecewiseControlPointsItem.h>
#include <vtkSmartPointer.h>
#include <vtkRenderWindow.h>
#include <vtkObjectFactory.h>
#include <vtkContextMouseEvent.h>
#include <vtkContextKeyEvent.h>
#include <vtkRenderWindowInteractor.h>

/**
 * @class PiecewiseControlPointsItem
 * Class that inherits from vtkPiecewiseControlPointsItem and overrides mouse events to update RenderWindow with each change made
 */
class PiecewiseControlPointsItem : public vtkPiecewiseControlPointsItem {
public:
    /**
     * Constructor
     */
    static PiecewiseControlPointsItem* New();

    /**
     * Set the RenderWindow that will be updated
     * @param	renWin	RenderWindow that will be updated
     */
    void SetRenderWindow(const vtkSmartPointer<vtkRenderWindow> &renWin);

    /**
     * Mouse button release event: Updates RenderWindow
     * @param	mouse	Mouse context
     */
    bool MouseButtonReleaseEvent(const vtkContextMouseEvent &mouse) override;

    /**
     * Key release event: Updates RenderWindow
     * @param	key	Key context
     */
    bool KeyReleaseEvent(const vtkContextKeyEvent &key) override;

private:
    vtkSmartPointer<vtkRenderWindow> renWin; /**< RenderWindow that will be updated when the transfer function is changed */
};

#endif // PIECEWISECONTROLPOINTSITEM_H
