#ifndef COLORTFCHART_H
#define COLORTFCHART_H

#include <vtkContextView.h>
#include <vtkTable.h>
#include <vtkPlot.h>
#include <vtkAxis.h>
#include <vtkFloatArray.h>
#include <vtkContextView.h>
#include <vtkContextScene.h>
#include <vtkColorTransferFunction.h>
#include <vtkColorTransferFunctionItem.h>
#include <vtkSmartPointer.h>
#include <vtkRenderWindow.h>

#include "colorTransferControlPointsItem.h"
#include "chartXY.h"

/**
 * @class ColorTFChart
 * Clase que muestra en un gr�fico los puntos de control y la paleta de colores utilizada en la funci�n de transferencia
 */
class ColorTFChart {
public:
	/**
	 * Constructor
	 * @param	figureRenWin	RenderWindow que se actualizar� al actualizar la funci�n de color
	 * @param	chartRenWin		RenderWindow donde se colocar� el gr�fico
	 * @param	tf				Funci�n de transferencia de color
	 * @param	xLabel			Nombre para la etiqueta del eje de la X
	 * @param	yLabel			Nombre para la etiqueta del eje de la Y
	 * @param	minBound		L�mite inferior que podr�n alcanzar los puntos de control
	 * @param	maxBound		L�mite superior que podr�n alcanzar los puntos de control
	 */
	ColorTFChart(vtkSmartPointer<vtkRenderWindow> figureRenWin, vtkSmartPointer<vtkRenderWindow> chartRenWin, 
		vtkSmartPointer<vtkColorTransferFunction> tf, const std::string xLabel, const std::string yLabel, const double minBound, const double maxBound);
	
	/*
	 * Destructor
	 */
	~ColorTFChart();

	/**
	 * Hace que la gr�fica vaya en el eje de la Y desde el valor m�s peque�o de la funci�n de transferencia al m�s grande
	 */
	void defaultRange();

	/**
	 * Hace que la gr�fica vaya en el eje de la Y desde min hasta max
	 * @param	min				L�mite inferior
	 * @param	max				L�mite superior
	 */
	void setRange(const double min, const double max);

private:
	vtkSmartPointer<ChartXY> chart; /**> Gr�fica donde se dibujar�n los dos Plot de la funci�n y los puntos de control */
	vtkSmartPointer<vtkContextView> context; /**> ContextView donde se renderizar� el contenido de chart */
	vtkSmartPointer<vtkColorTransferFunctionItem> function; /**> Plot en el que se mostrar� la funci�n de color */
	vtkSmartPointer<ColorTransferControlPointsItem> controlPoints; /**> Plot en el que se mostrar�n los puntos de control de la funci�n */
	vtkSmartPointer<vtkColorTransferFunction> tf; /**< Funci�n de transferencia de color de donde se obtendr�n los dos plot */
};

#endif