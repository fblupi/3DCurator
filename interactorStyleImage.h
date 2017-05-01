#ifndef INTERACTORSTYLEIMAGE_H
#define INTERACTORSTYLEIMAGE_H

#include <QLabel>
#include <QPixmap>
#include <QBitmap>

#include <vtkObjectFactory.h>
#include <vtkSmartPointer.h>
#include <vtkInteractorStyleImage.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkCellPicker.h>

#include "plano.h"
#include "figura.h"

/**
 * @class InteractorStyleImage
 * Clase que hereda de la clase vtkInteractorStyleImage y redefine el evento de pulsar el botón izquierdo del ratón para que no cambie el 
 * nivel de color y ventana del ImageViewer2 y se pueda ver el valor de densidad de cada voxel
 */
class InteractorStyleImage : public vtkInteractorStyleImage {
public:
	/**
	 * Constructor
	 */
	static InteractorStyleImage* New();

	vtkTypeMacro(vtkInteractorStyleImage, InteractorStyleImage);
	
	/**
	 * Establece el plano en el que buscará el valor del voxel seleccionado
	 * @param	plano	Plano en el que buscará el valor del voxel seleccionado
	 */
	void SetPlano(Plano* plano);

	/**
	 * Establece la etiqueta donde se escribirá el valor escalar del voxel seleccionado
	 * @param	label	QLabel donde se escribirá el valor escalar del voxel seleccionado
	 */
	void SetLabel(QLabel* label);

	void SetFigura(Figura* figura);

	/**
	 * Evento al pulsar el botón izquierdo del ratón
	 */
	virtual void OnLeftButtonDown();
	
	/**
	 * Evento al mover el ratón
	 */
	virtual void OnMouseMove();

private:
	Plano* plano; /**< Figura a la que se le borran partes */
	QLabel* label; /**< Etiqueta donde se actualizan los valores */
	Figura* figura;
};

#endif // INTERACTORSTYLEIMAGE_H