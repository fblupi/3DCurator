#include "colorTFChart.h"

ColorTFChart::ColorTFChart(vtkSmartPointer<vtkRenderWindow> figureRenWin, vtkSmartPointer<vtkRenderWindow> chartRenWin, 
	vtkSmartPointer<vtkColorTransferFunction> tf, const std::string xLabel, const std::string yLabel, const double minBound, const double maxBound) {
	this->tf = tf; // copia la función de transferencia

	chart = vtkSmartPointer<ChartXY>::New();
	// inserta los títulos a los ejes
	chart->GetAxis(0)->SetTitle(yLabel);
	chart->GetAxis(1)->SetTitle(xLabel);
	// no permite que los plot cambien el rango de los ejes
	chart->GetAxis(0)->SetBehavior(vtkAxis::FIXED);
	chart->GetAxis(1)->SetBehavior(vtkAxis::FIXED);

	function = vtkSmartPointer<vtkColorTransferFunctionItem>::New();
	function->SetColorTransferFunction(tf); // asigna la función de transferencia
	chart->AddPlot(function); // añade el plot al chart

	controlPoints = vtkSmartPointer<ColorTransferControlPointsItem>::New();
	controlPoints->SetRenderWindow(figureRenWin); // renderWindow que actualizará al cambiar la función de transferencia
	controlPoints->SetColorTransferFunction(tf); // asigna la función de transferencia
	controlPoints->SetUserBounds(minBound, maxBound, 0, 1); // límite hasta donde se pueden colocar puntos (xmin, xmax, ymin, ymax)
	chart->AddPlot(controlPoints); // añade el plot al chart

	context = vtkSmartPointer<vtkContextView>::New();
	context->SetRenderWindow(chartRenWin); // renderWindow donde se verán los gráficos
	context->GetScene()->AddItem(chart); // añade el chart al renderWindow

	defaultRange(); // actualiza rangos
}

ColorTFChart::~ColorTFChart() {

}

void ColorTFChart::defaultRange() {
	chart->GetAxis(0)->SetRange(0, 1); // rango del eje Y
	chart->GetAxis(1)->SetRange(tf->GetRange()[0], tf->GetRange()[1]); // rango del eje X extraído de la función de transferencia
	context->Render(); // renderiza
}

void ColorTFChart::setRange(const double min, const double max) {
	chart->GetAxis(1)->SetRange(min, max); // actualiza el rango
	context->Render(); // renderiza
}