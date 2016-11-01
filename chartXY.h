#ifndef CHARTXY_H
#define CHARTXY_H

#include <vtkChartXY.h>
#include <vtkObjectFactory.h>
#include <vtkContextMouseEvent.h>

/**
 * @class ChartXY
 * Clase que hereda de la clase vtkChartXY y redefine los m�todos de eventos producidos por el rat�n para que no hagan nada
 */
class ChartXY : public vtkChartXY {
public:
	/**
	 * Constructor
	 */
	static ChartXY* New();

	vtkTypeMacro(vtkChartXY, ChartXY);

	/**
	 * Evento a la entrada del rat�n
	 * @param	mouse	Contexto del rat�n
	 */
	virtual bool MouseEnterEvent(const vtkContextMouseEvent &mouse);

	/**
	 * Evento al mover el rat�n
	 * @param	mouse	Contexto del rat�n
	 */
	virtual bool MouseMoveEvent(const vtkContextMouseEvent &mouse);


	/**
	 * Evento a la salida del rat�n
	 * @param	mouse	Contexto del rat�n
	 */
	virtual bool MouseLeaveEvent(const vtkContextMouseEvent &mouse);

	/**
	 * Evento al presionar el rat�n
	 * @param	mouse	Contexto del rat�n
	 */
	virtual bool MouseButtonPressEvent(const vtkContextMouseEvent &mouse);

	/**
	 * Evento al soltar el rat�n
	 * @param	mouse	Contexto del rat�n
	 */
	virtual bool MouseButtonReleaseEvent(const vtkContextMouseEvent &mouse);

	/**
	 * Evento al usar la rueda del rat�n
	 * @param	mouse	Contexto del rat�n
	 */
	virtual bool MouseWheelEvent(const vtkContextMouseEvent &mouse, int delta);
};

#endif