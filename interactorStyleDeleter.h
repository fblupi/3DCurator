#ifndef INTERACTORSTYLEDELETER_H
#define INTERACTORSTYLEDELETER_H

#include <QProgressDialog>
#include <QIcon>
#include <QMessageBox>
#include <QAbstractButton>
#include <QPointer>
#include <QProgressBar>
#include <QApplication>

#include <vtkObjectFactory.h>
#include <vtkSmartPointer.h>
#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderWindow.h>
#include <vtkVolumePicker.h>
#include <vtkImageViewer2.h>

#include <stack>
#include "figura.h"
#include "plano.h"
#include "measures.h"

/**
 * @class InteractorStyleDeleter
 * Clase que hereda de la clase vtkInteractorStyleTrackballCamera y que al pulsar sobre un voxel borra todos los que forman
 * parte de esa parte de la figura rodeada de aire. En ocasiones, dependiendo del voxel en el que se pulse, borra la totalidad
 * de la parte que se desea borrar o no y habr�a que hacer varios clicks
 */
class InteractorStyleDeleter : public vtkInteractorStyleTrackballCamera {
public:
	/**
	 * Constructor
	 */
	static InteractorStyleDeleter* New();

	vtkTypeMacro(vtkInteractorStyleTrackballCamera, InteractorStyleDeleter);

	/**
	 * Establece el RenderWindow donde se har� pick
	 * @param	renWin		RenderWindow donde se har� pick
	 */
	void SetDefaultRenderWindow(vtkSmartPointer<vtkRenderWindow> renWin);

	/**
	 * Establece el ImageViewer2 que actualizar� al borrar
	 * @param	viewer		ImageViewer2 que se actualizar� al borrar
	 */
	void SetViewer(vtkSmartPointer<vtkImageViewer2> viewer);

	/**
	 * Establece la figura sobre la que se har� pick para borrar
	 * @param	figura		Figura a la que borrar� partes
	 */
	void SetFigura(Figura* figura);

	/**
	 * Establece el plano al que actualizar� el corte al borrar
	 * @param	plano		Plano al que actualizar� la imagen de corte
	 */
	void SetPlano(Plano* plano);

	/**
	 * Evento al pulsar el bot�n izquierdo del rat�n
	 */
	virtual void OnLeftButtonDown();

private:
	vtkSmartPointer<vtkRenderWindow> renWin; /**< Ventana donde se renderiza la figura */
	vtkSmartPointer<vtkImageViewer2> viewer; /**< ImageViewer2 que se actualizar� cuando se mueva el plano */
	Figura* figura; /**< Figura a la que se le borran partes */
	Plano* plano; /**< Plano con el que se obtienen los cortes */

	/**
	 * Busca un voxel inicial donde empezar a expandirse al borrar una imagen
	 * @param	imageData	Datos del volumen
	 * @param	ijk			Punto inicial
	 * @param	MIN_X		L�mite m�nimo en la coordenada x
	 * @param	MAX_X		L�mite m�ximo en la coordenada x
	 * @param	MIN_Y		L�mite m�nimo en la coordenada y
	 * @param	MAX_Y		L�mite m�ximo en la coordenada y
	 * @return	coordenada x,y donde empezar a borrar la imagen
	 */
	std::pair<int, int> searchInitialVoxel(vtkSmartPointer<vtkImageData> imageData, const int ijk[3], const int MIN_X, const int MAX_X, const int MIN_Y, const int MAX_Y);
	
	/**
	 * Borra la isla donde se encuentra un punto de una imagen
	 * @param	imageData	Datos del volumen
	 * @param	ijk			Punto inicial
	 * @param	MIN_X		L�mite m�nimo en la coordenada x
	 * @param	MAX_X		L�mite m�ximo en la coordenada x
	 * @param	MIN_Y		L�mite m�nimo en la coordenada y
	 * @param	MAX_Y		L�mite m�ximo en la coordenada y
	 */
	void deleteImage(vtkSmartPointer<vtkImageData> imageData, const int ijk[3], const int MIN_X, const int MAX_X, const int MIN_Y, const int MAX_Y);

	/**
	 * Borra la isla donde se encuentra un punto
	 * @param	imageData	Datos del volumen
	 * @param	ijk			Punto inicial
	 * @param	MIN_X		L�mite m�nimo en la coordenada x
	 * @param	MAX_X		L�mite m�ximo en la coordenada x
	 * @param	MIN_Y		L�mite m�nimo en la coordenada y
	 * @param	MAX_Y		L�mite m�ximo en la coordenada y
	 * @param	MIN_Z		L�mite m�nimo en la coordenada z
	 * @param	MAX_Z		L�mite m�ximo en la coordenada z
	 */
	void deleteByImages(vtkSmartPointer<vtkImageData> imageData, const int ijk[3], const int MIN_X, const int MAX_X, const int MIN_Y, const int MAX_Y, const int MIN_Z, const int MAX_Z);
};

#endif // INTERACTORSTYLEDELETER_H