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
 * Class that inherites from vtkPiecewiseControlPointsItem and overrides mouse events to update RenderWindow with each change made
 */
class PiecewiseControlPointsItem : public vtkPiecewiseControlPointsItem {
public:
	/**
	 * Constructor
	 */
	static PiecewiseControlPointsItem* New();

	vtkTypeMacro(vtkPiecewiseControlPointsItem, PiecewiseControlPointsItem);

	/**
	 * Set the RenderWindow that will be updated
	 * @param	renWin	RenderWindow that will be updated
	 */
	void SetRenderWindow(vtkSmartPointer<vtkRenderWindow> renWin);
	
	/**
	 * Mouse button release event: Updates RenderWindow
	 * @param	mouse	Mouse context
	 */
	virtual bool MouseButtonReleaseEvent(const vtkContextMouseEvent &mouse);

	/**
	 * Key release event: Updates RenderWindow
	 * @param	key	Key context
	 */
	virtual bool KeyReleaseEvent(const vtkContextKeyEvent &key);

private:
	vtkSmartPointer<vtkRenderWindow> renWin; /**< RenderWindow that will be updated when the transfer function is changed */
};

#endif