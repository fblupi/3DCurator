#ifndef CHARTXY_H
#define CHARTXY_H

#include <vtkChartXY.h>
#include <vtkObjectFactory.h>
#include <vtkContextMouseEvent.h>

/**
 * @class ChartXY
 * Clase que hereda de la clase vtkChartXY y redefine los métodos de eventos producidos por el ratón para que no hagan nada
 */
class ChartXY : public vtkChartXY {
public:
	/**
	 * Constructor
	 */
	static ChartXY* New();

	vtkTypeMacro(vtkChartXY, ChartXY);

	/**
	 * Evento a la entrada del ratón
	 * @param	mouse	Contexto del ratón
	 */
	virtual bool MouseEnterEvent(const vtkContextMouseEvent &mouse);

	/**
	 * Evento al mover el ratón
	 * @param	mouse	Contexto del ratón
	 */
	virtual bool MouseMoveEvent(const vtkContextMouseEvent &mouse);


	/**
	 * Evento a la salida del ratón
	 * @param	mouse	Contexto del ratón
	 */
	virtual bool MouseLeaveEvent(const vtkContextMouseEvent &mouse);

	/**
	 * Evento al presionar el ratón
	 * @param	mouse	Contexto del ratón
	 */
	virtual bool MouseButtonPressEvent(const vtkContextMouseEvent &mouse);

	/**
	 * Evento al soltar el ratón
	 * @param	mouse	Contexto del ratón
	 */
	virtual bool MouseButtonReleaseEvent(const vtkContextMouseEvent &mouse);

	/**
	 * Evento al usar la rueda del ratón
	 * @param	mouse	Contexto del ratón
	 */
	virtual bool MouseWheelEvent(const vtkContextMouseEvent &mouse, int delta);
};

#endif