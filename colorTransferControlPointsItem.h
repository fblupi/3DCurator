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
 * Clase que hereda de la clase vtkColorTransferControlPointsItem y redefine los m�todos de eventos producidos por el rat�n
 * para que al realizar cualquier cambio sobre la funci�n de transferencia se actualice un RenderWindow. Adem�s se a�ade una 
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
	 * Establece el RenderWindow que actualizar�
	 * @param	renWin	RenderWindow que actualizar�
	 */
	void SetRenderWindow(vtkSmartPointer<vtkRenderWindow> renWin);

	/**
	 * Evento al soltar el rat�n
	 * @param	mouse	Contexto del rat�n
	 */
	virtual bool MouseButtonReleaseEvent(const vtkContextMouseEvent &mouse);

	/**
	 * Evento al hacer doble click con el rat�n
	 * @param	mouse	Contexto del rat�n
	 */
	virtual bool MouseDoubleClickEvent(const vtkContextMouseEvent &mouse);

	/**
	 * Evento al soltar una tecla
	 * @param	key		Contexto de la tecla
	 */
	virtual bool KeyReleaseEvent(const vtkContextKeyEvent &key);

private:
	vtkSmartPointer<vtkRenderWindow> renWin; /**< RenderWindow que se actualizar� cuando se produzca un cambio en la funci�n de transferencia */
};

#endif