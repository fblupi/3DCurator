#ifndef OPACITYTFCHART_H
#define OPACITYTFCHART_H

#include <vtkContextView.h>
#include <vtkTable.h>
#include <vtkPlot.h>
#include <vtkAxis.h>
#include <vtkFloatArray.h>
#include <vtkContextView.h>
#include <vtkContextScene.h>
#include <vtkPiecewiseFunction.h>
#include <vtkPiecewiseFunctionItem.h>
#include <vtkSmartPointer.h>
#include <vtkRenderWindow.h>

#include "piecewiseControlPointsItem.h"
#include "chartXY.h"

/**
 * @class OpacityTFChart
 * Clase que muestra en un gráfico los puntos de control y la paleta de colores utilizada en una función de transferencia de opacidad
 */
class OpacityTFChart {
public:
	/**
	 * Constructor
	 * @param	figureRenWin	RenderWindow que se actualizará al actualizar la función de opacidad
	 * @param	chartRenWin		RenderWindow donde se colocará el gráfico
	 * @param	tf				Función de transferencia de opacidad
	 * @param	xLabel			Nombre para la etiqueta del eje de la X
	 * @param	yLabel			Nombre para la etiqueta del eje de la Y
	 * @param	minBound		Límite inferior que podrán alcanzar los puntos de control
	 * @param	maxBound		Límite superior que podrán alcanzar los puntos de control
	 */
	OpacityTFChart(vtkSmartPointer<vtkRenderWindow> figureRenWin, vtkSmartPointer<vtkRenderWindow> chartRenWin, 
		vtkSmartPointer<vtkPiecewiseFunction> tf, const std::string xLabel, const std::string yLabel, const double minBound, const double maxBound);
	
	/*
	 * Destructor
	 */
	~OpacityTFChart();

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
	vtkSmartPointer<ChartXY> chart;  /**< Gráfica donde se dibujarán los dos Plot de la función y los puntos de control */
	vtkSmartPointer<vtkContextView> context; /**< ContextView donde se renderizará el contenido de chart */
	vtkSmartPointer<vtkPiecewiseFunctionItem> function; /**< Plot en el que se mostrará la función de color */
	vtkSmartPointer<PiecewiseControlPointsItem> controlPoints; /**< Plot en el que se mostrarán los puntos de control de la función */
	vtkSmartPointer<vtkPiecewiseFunction> tf; /**< Función de transferencia de opacidad de donde se obtendrán los dos plot */
};

#endif