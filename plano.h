#ifndef PLANO_H
#define PLANO_H

#include <vtkObjectFactory.h>
#include <vtkSmartPointer.h>
#include <vtkImagePlaneWidget.h>
#include <vtkImageViewer2.h>
#include <vtkImageData.h>

#include "imagePlaneWidget.h"

/** 
 * @class Plano
 * Clase con el plano de corte con la figura
 */
class Plano {
public:
	/**
	 * Constructor
	 */
	Plano();

	/**
	 * Destructor
	 */
	~Plano();

	/**
	 * Obtiene el plano
	 * @return	Puntero a ImagePlaneWidget
	 */
	vtkSmartPointer<ImagePlaneWidget> getPlane() const;

	/**
	 * Establece la conexión con el volumen
	 * @param	imageData	Lector de donde se obtienen los datos del volumen
	 */
	void setInputData(vtkSmartPointer<vtkImageData> imageData);

	/** 
	 * Establece el visor donde se verán los cortes
	 * @param	viewer	Visor
	 */
	void setViewer(vtkSmartPointer<vtkImageViewer2> viewer);

	/**
	 * Hace visible el plano
	 */
	void enable(const bool onOff);

	/**
	 * Hace visible el corte del plano con el volumen
	 */
	void show(const bool onOff);

	/**
	 * Establece el centro del plano en un punto
	 * @param	x	componente x del punto
	 * @param	y	componente y del punto
	 * @param	z	componente z del punto
	 */
	void setOrigin(const double x, const double y, const double z);

	/**
	 * Coloca el plano en el centro del volumen en posición sagital (sobre los ejes YZ)
	 */
	void setSagital();

	/**
	 * Coloca el plano en el centro del volumen en posición coronal (sobre los ejes XZ)
	 */
	void setCoronal();

	/**
	 * Coloca el plano en el centro del volumen en posición axial (sobre los ejes XY)
	 */
	void setAxial();

private:
	vtkSmartPointer<ImagePlaneWidget> plane; /**< Plano de corte con el volumen */
	double centers[3]; /**< Posiciones centrales para los planos sagital, coronal y axial */
};

#endif // PLANO_H