#ifndef INTERACTORSTYLESEGMENTATION_H
#define INTERACTORSTYLESEGMENTATION_H

#include <vector>
#include <stack>
#include <queue>
#include <array>
#include <stdio.h>

#include <QPixmap>
#include <QBitmap>
#include <QMessageBox>
#include <QProgressDialog>
#include <QProgressBar>
#include <QPointer>
#include <QIcon>
#include <QApplication>

#include <vtkObjectFactory.h>
#include <vtkSmartPointer.h>
#include <vtkInteractorStyleImage.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkCellPicker.h>
#include <vtkVolumePicker.h>
#include <vtkResliceCursorPicker.h>
#include <vtkPointPlacer.h>
#include <vtkRenderer.h>
#include <vtkExtractVOI.h>
#include <vtkPNGWriter.h>
#include <vtkImageMapToColors.h>

#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"

#include "plano.h"
#include "figura.h"
#include "measures.h"
#include "utils.h"
#include "lineSelectionDialog.h"


/**
 * @class InteractorStyleSegmentation
 * Clase que hereda de la clase vtkInteractorStyleSegmentation y redefine el evento de pulsar el bot�n izquierdo del rat�n para que no cambie el 
 * nivel de color y ventana del ImageViewer2 y se pueda ver el valor de densidad de cada voxel
 */
class InteractorStyleSegmentation : public vtkInteractorStyleImage {
public:
	/**
	 * Constructor
	 */
	static InteractorStyleSegmentation* New();

	vtkTypeMacro(vtkInteractorStyleImage, InteractorStyleSegmentation);

	/**
	 * Establece el plano en el que buscar� el valor del voxel seleccionado
	 * @param	plano	Plano en el que buscar� el valor del voxel seleccionado
	 */
	void SetPlano(Plano* plano);

	/**
	 * Establece la figura sobre la que se har� pick para segmentar
	 * @param	figura	Figura a la que se segmentar� partes
	 */
	void SetFigura(Figura* figura);

	/**
	 * Evento al pulsar el bot�n izquierdo del rat�n
	 */
	virtual void OnLeftButtonDown();

private:
	Plano* plano; /**< Plano de la figura a la que se le borran partes */
	Figura* figura; /**< Figura a la que se le borran partes */
};

#endif // INTERACTORSTYLESEGMENTATION_H