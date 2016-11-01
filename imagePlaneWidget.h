#ifndef IMAGEPLANEWIDGET_H
#define IMAGEPLANEWIDGET_H

#include <vtkObjectFactory.h>
#include <vtkSmartPointer.h>
#include <vtkImagePlaneWidget.h>
#include <vtkImageViewer2.h>

/**
 * @class ImagePlaneWidget
 * Clase que hereda de la clase vtkImagePlaneWidget y redefine los métodos de eventos producidos por el ratón para que al moverlo, si previamente
 * se ha pulsado el botón derecho se actualice un ImageViewer2. Además, desactiva los eventos producidos al hacer click en el bótón izquierdo y central
 */
class ImagePlaneWidget : public vtkImagePlaneWidget {
public:
	/**
	 * Constructor
	 */
	static ImagePlaneWidget* New();

	vtkTypeMacro(vtkImagePlaneWidget, ImagePlaneWidget);

	/**
	 * Establece el ImageViewer2 que actualizará
	 * @param	viewer	ImageViewer2 que se actualizará
	 */
	void SetViewer(vtkSmartPointer<vtkImageViewer2> viewer); /**< Establece el ImageViewer2 */

	/**
	 * Evento al mover el ratón
	 */
	virtual void OnMouseMove();

	/**
	 * Evento al pulsar el botón central del ratón
	 */
	virtual void OnMiddleButtonDown();

	/**
	 * Evento al levantar el botón central del ratón
	 */
	virtual void OnMiddleButtonUp();

	/**
	 * Evento al pulsar el botón izquierdo del ratón
	 */
	virtual void OnLeftButtonDown();

	/**
	 * Evento al levantar el botón izquierdo del ratón
	 */
	virtual void OnLeftButtonUp();

	/**
	 * Evento al pulsar el botón derecho del ratón
	 */
	virtual void OnRightButtonDown();

	/**
	 * Evento al levantar el botón izquierdo del ratón
	 */
	virtual void OnRightButtonUp();

private:
	bool moving = false;  /**< Variable booleana para saber si se está moviendo o no el plano */
	vtkSmartPointer<vtkImageViewer2> viewer; /**< ImageViewer2 que se actualizará cuando se mueva el plano */
};

#endif // IMAGEPLANEWIDGET_H