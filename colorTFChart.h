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
 * Clase que muestra en un gráfico los puntos de control y la paleta de colores utilizada en la función de transferencia
 */
class ColorTFChart {
public:
	/**
	 * Constructor
	 * @param	figureRenWin	RenderWindow que se actualizará al actualizar la función de color
	 * @param	chartRenWin		RenderWindow donde se colocará el gráfico
	 * @param	tf				Función de transferencia de color
	 * @param	xLabel			Nombre para la etiqueta del eje de la X
	 * @param	yLabel			Nombre para la etiqueta del eje de la Y
	 * @param	minBound		Límite inferior que podrán alcanzar los puntos de control
	 * @param	maxBound		Límite superior que podrán alcanzar los puntos de control
	 */
	ColorTFChart(vtkSmartPointer<vtkRenderWindow> figureRenWin, vtkSmartPointer<vtkRenderWindow> chartRenWin, 
		vtkSmartPointer<vtkColorTransferFunction> tf, const std::string xLabel, const std::string yLabel, const double minBound, const double maxBound);
	
	/*
	 * Destructor
	 */
	~ColorTFChart();

	/**
	 * Hace que la gráfica vaya en el eje de la Y desde el valor más pequeño de la función de transferencia al más grande
	 */
	void defaultRange();

	/**
	 * Hace que la gráfica vaya en el eje de la Y desde min hasta max
	 * @param	min				Límite inferior
	 * @param	max				Límite superior
	 */
	void setRange(const double min, const double max);

private:
	vtkSmartPointer<ChartXY> chart; /**> Gráfica donde se dibujarán los dos Plot de la función y los puntos de control */
	vtkSmartPointer<vtkContextView> context; /**> ContextView donde se renderizará el contenido de chart */
	vtkSmartPointer<vtkColorTransferFunctionItem> function; /**> Plot en el que se mostrará la función de color */
	vtkSmartPointer<ColorTransferControlPointsItem> controlPoints; /**> Plot en el que se mostrarán los puntos de control de la función */
	vtkSmartPointer<vtkColorTransferFunction> tf; /**< Función de transferencia de color de donde se obtendrán los dos plot */
};

#endif