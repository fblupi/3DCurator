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
 * Clase que hereda de la clase vtkColorTransferControlPointsItem y redefine los métodos de eventos producidos por el ratón
 * para que al realizar cualquier cambio sobre la función de transferencia se actualice un RenderWindow. Además se añade una 
 * funcionalidad al doble click para que aparezca un selector de color para cambiar el color de ese punto
 */
class ColorTransferControlPointsItem : public vtkColorTransferControlPointsItem {
public:
	/**
	 * Constructor
	 */
	static ColorTransferControlPointsItem* New();

	vtkTypeMacro(vtkColorTransferControlPointsItem, ColorTransferControlPointsItem);

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
	 * Evento al hacer doble click con el ratón
	 * @param	mouse	Contexto del ratón
	 */
	virtual bool MouseDoubleClickEvent(const vtkContextMouseEvent &mouse);

	/**
	 * Evento al soltar una tecla
	 * @param	key		Contexto de la tecla
	 */
	virtual bool KeyReleaseEvent(const vtkContextKeyEvent &key);

private:
	vtkSmartPointer<vtkRenderWindow> renWin; /**< RenderWindow que se actualizará cuando se produzca un cambio en la función de transferencia */
};

#endif