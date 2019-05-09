#ifndef COLORTRANSFERCONTROLPOINTSITEM_H
#define COLORTRANSFERCONTROLPOINTSITEM_H

#include <vtkColorTransferFunction.h>
#include <vtkColorTransferControlPointsItem.h>
#include <vtkSmartPointer.h>
#include <vtkRenderWindow.h>
#include <vtkObjectFactory.h>
#include <vtkContextMouseEvent.h>
#include <vtkContextKeyEvent.h>
#include <vtkRenderWindowInteractor.h>

#include <QColorDialog>
#include <QPointer>

/**
 * @class ColorTransferControlPointsItem
 * Class that inherits from vtkColorTransferControlPointsItem and overrides mouse events to update RenderWindow with each change 
 * made. Furthermore, it will launch a color selector widget to change the color in a point when double click event is triggered
 */
class ColorTransferControlPointsItem : public vtkColorTransferControlPointsItem {
public:
    /**
     * Constructor
     */
    static ColorTransferControlPointsItem* New();

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
     * Mouse double click event: Launches a color selector widget
     * @param	mouse	Mouse context
     */
    bool MouseDoubleClickEvent(const vtkContextMouseEvent &mouse) override;

    /**
     * Key release event: Updates RenderWindow
     * @param	key	Key context
     */
    bool KeyReleaseEvent(const vtkContextKeyEvent &key) override;

private:
    vtkSmartPointer<vtkRenderWindow> renWin; /**< RenderWindow that will be updated when the transfer function is changed */
};

#endif // COLORTRANSFERCONTROLPOINTSITEM_H
