#ifndef CHARTXY_H
#define CHARTXY_H

#include <vtkChartXY.h>
#include <vtkObjectFactory.h>
#include <vtkContextMouseEvent.h>

/**
 * @class ChartXY
 * Class that inherits from vtkChartXY class and overrides some mouse events
 */
class ChartXY : public vtkChartXY {
public:
	/**
	 * Constructor
	 */
	static ChartXY* New();

	vtkTypeMacro(vtkChartXY, ChartXY);

	/**
	 * Mouse enter event: Idle
	 * @param	mouse	Mouse context
	 */
	virtual bool MouseEnterEvent(const vtkContextMouseEvent &mouse);

	/**
	 * Mouse move event: Idle
	 * @param	mouse	Mouse context
	 */
	virtual bool MouseMoveEvent(const vtkContextMouseEvent &mouse);


	/**
	 * Mouse leave event: Idle
	 * @param	mouse	Mouse context
	 */
	virtual bool MouseLeaveEvent(const vtkContextMouseEvent &mouse);

	/**
	 * Mouse button press event: Idle
	 * @param	mouse	Mouse context
	 */
	virtual bool MouseButtonPressEvent(const vtkContextMouseEvent &mouse);

	/**
	 * Mouse button release event: Idle
	 * @param	mouse	Mouse context
	 */
	virtual bool MouseButtonReleaseEvent(const vtkContextMouseEvent &mouse);

	/**
	 * Mouse wheel event: Idle
	 * @param	mouse	Mouse context
	 */
	virtual bool MouseWheelEvent(const vtkContextMouseEvent &mouse, int delta);
};

#endif