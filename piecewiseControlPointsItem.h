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
 * Clase que hereda de la clase vtkPiecewiseControlPointsItem y redefine los métodos de eventos producidos por el ratón
 * para que al realizar cualquier cambio sobre la función de transferencia se actualice un RenderWindow.
 */
class PiecewiseControlPointsItem : public vtkPiecewiseControlPointsItem {
public:
	/**
	 * Constructor
	 */
	static PiecewiseControlPointsItem* New();

	vtkTypeMacro(vtkPiecewiseControlPointsItem, PiecewiseControlPointsItem);

	/**
	 * Establece el RenderWindow que actualizará
	 * @param	renWin	RenderWindow que actualizará
	 */
	void SetRenderWindow(vtkSmartPointer<vtkRenderWindow> renWin);
	
	/**
	 * Evento al soltar el ratón
	 * @param	mouse	Contexto del ratón
	 */
	virtual bool MouseButtonReleaseEvent(const vtkContextMouseEvent &mouse);

	/**
	 * Evento al soltar una tecla
	 * @param	key		Contexto de la tecla
	 */
	virtual bool KeyReleaseEvent(const vtkContextKeyEvent &key);

private:
	vtkSmartPointer<vtkRenderWindow> renWin; /**< RenderWindow que se actualizará cuando se produzca un cambio en la función de transferencia */
};

#endif