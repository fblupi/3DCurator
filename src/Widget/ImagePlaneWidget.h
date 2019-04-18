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
 * Class that inherits from vtkImagePlaneWIdget and overrides mouse events to update ImageViewer2 when it is moved and previously right button has
 * been clicked. Furthermore, it turns off left and central button events
 */
class ImagePlaneWidget : public vtkImagePlaneWidget {
public:
	/**
	 * Constructor
	 */
	static ImagePlaneWidget* New();

	vtkTypeMacro(vtkImagePlaneWidget, ImagePlaneWidget);

	/**
	 * Set ImageViewer2 that will be updated
	 * @param	viewer	ImageViewer2 that will be updated
	 */
	void SetViewer(vtkSmartPointer<vtkImageViewer2> viewer);

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
	 * Empty list item 
	 * @param	nullROD	Empty list item 
	 */
	void setNullROD(QListWidgetItem* nullROD);

	/**
	 * Mouse move event: Updates viewer if it is moving
	 */
	virtual void OnMouseMove() override;

	/**
	 * Middle button down event: idle
	 */
	virtual void OnMiddleButtonDown() override;

	/**
	 * Middle button up event: idle
	 */
	virtual void OnMiddleButtonUp() override;

	/**
	 * Left button down event: idle
	 */
	virtual void OnLeftButtonDown() override;

	/**
	 * Left button up event: idle
	 */
	virtual void OnLeftButtonUp() override;

	/**
	 * Right button down event: Start moving
	 */
	virtual void OnRightButtonDown() override;

	/**
	 * Right button up event: End moving
	 */
	virtual void OnRightButtonUp() override;

private:
	bool moving = false; /**< Plane is moving */
	vtkSmartPointer<vtkImageViewer2> viewer; /**< ImageViewer2 that will be updated when the plane is moving */
	ROD* activeROD; /**< Active ROD that will be disabled after moving */
	QListWidgetItem* nullROD; /**< Empty list item */
	QListWidget* listROD; /**< List with RODs which active element will be disabled */

	void unsetActiveROD(); /**< Disable active ROD element and hide UI ROD elements in the list */
};

#endif // IMAGEPLANEWIDGET_H