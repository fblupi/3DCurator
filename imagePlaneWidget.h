#ifndef IMAGEPLANEWIDGET_H
#define IMAGEPLANEWIDGET_H

#include <vtkObjectFactory.h>
#include <vtkSmartPointer.h>
#include <vtkImagePlaneWidget.h>
#include <vtkImageViewer2.h>

/**
 * @class ImagePlaneWidget
 * Clase que hereda de la clase vtkImagePlaneWidget y redefine los m�todos de eventos producidos por el rat�n para que al moverlo, si previamente
 * se ha pulsado el bot�n derecho se actualice un ImageViewer2. Adem�s, desactiva los eventos producidos al hacer click en el b�t�n izquierdo y central
 */
class ImagePlaneWidget : public vtkImagePlaneWidget {
public:
	/**
	 * Constructor
	 */
	static ImagePlaneWidget* New();

	vtkTypeMacro(vtkImagePlaneWidget, ImagePlaneWidget);

	/**
	 * Establece el ImageViewer2 que actualizar�
	 * @param	viewer	ImageViewer2 que se actualizar�
	 */
	void SetViewer(vtkSmartPointer<vtkImageViewer2> viewer); /**< Establece el ImageViewer2 */

	/**
	 * Evento al mover el rat�n
	 */
	virtual void OnMouseMove();

	/**
	 * Evento al pulsar el bot�n central del rat�n
	 */
	virtual void OnMiddleButtonDown();

	/**
	 * Evento al levantar el bot�n central del rat�n
	 */
	virtual void OnMiddleButtonUp();

	/**
	 * Evento al pulsar el bot�n izquierdo del rat�n
	 */
	virtual void OnLeftButtonDown();

	/**
	 * Evento al levantar el bot�n izquierdo del rat�n
	 */
	virtual void OnLeftButtonUp();

	/**
	 * Evento al pulsar el bot�n derecho del rat�n
	 */
	virtual void OnRightButtonDown();

	/**
	 * Evento al levantar el bot�n izquierdo del rat�n
	 */
	virtual void OnRightButtonUp();

private:
	bool moving = false;  /**< Variable booleana para saber si se est� moviendo o no el plano */
	vtkSmartPointer<vtkImageViewer2> viewer; /**< ImageViewer2 que se actualizar� cuando se mueva el plano */
};

#endif // IMAGEPLANEWIDGET_H