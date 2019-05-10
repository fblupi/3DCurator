#ifndef IMAGEPLANEWIDGET_H
#define IMAGEPLANEWIDGET_H

#include <QListWidget>
#include <QListWidgetItem>

#include <vtkObjectFactory.h>
#include <vtkSmartPointer.h>
#include <vtkImagePlaneWidget.h>
#include <vtkImageViewer2.h>

#include "Documentation/ROD.h"

/**
 * @class ImagePlaneWidget
 * Class that inherits from vtkImagePlaneWidget and overrides mouse events to update ImageViewer2 when it is moved and previously right button has
 * been clicked. Furthermore, it turns off left and central button events
 */
class ImagePlaneWidget : public vtkImagePlaneWidget {
public:
    /**
     * Constructor
     */
    static ImagePlaneWidget* New();

    /**
     * Set ImageViewer2 that will be updated
     * @param	viewer	ImageViewer2 that will be updated
     */
    void SetViewer(const vtkSmartPointer<vtkImageViewer2> &viewer);

    /**
     * Set ROD that will be disabled after moving
     * @param	activeROD	ROD that will be disabled after moving
     */
    void setActiveROD(ROD* activeROD);

    /**
     * Set list with RODs which active element will be disabled
     * @param	activeROD	List with RODs which active element will be disabled
     */
    void setListROD(QListWidget* listROD);

    /**
     * Mouse move event: Updates viewer if it is moving
     */
    void OnMouseMove() override;

    /**
     * Middle button down event: idle
     */
    void OnMiddleButtonDown() override;

    /**
     * Middle button up event: idle
     */
    void OnMiddleButtonUp() override;

    /**
     * Left button down event: idle
     */
    void OnLeftButtonDown() override;

    /**
     * Left button up event: idle
     */
    void OnLeftButtonUp() override;

    /**
     * Right button down event: Start moving
     */
    void OnRightButtonDown() override;

    /**
     * Right button up event: End moving
     */
    void OnRightButtonUp() override;

private:
    bool moving = false; /**< Plane is moving */
    vtkSmartPointer<vtkImageViewer2> viewer; /**< ImageViewer2 that will be updated when the plane is moving */
    ROD* activeROD; /**< Active ROD that will be disabled after moving */
    QListWidget* listROD; /**< List with RODs which active element will be disabled */

    void unsetActiveROD(); /**< Disable active ROD element and hide UI ROD elements in the list */
};

#endif // IMAGEPLANEWIDGET_H
