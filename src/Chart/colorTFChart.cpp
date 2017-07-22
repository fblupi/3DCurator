#include "ColorTFChart.h"

ColorTFChart::ColorTFChart(vtkSmartPointer<vtkRenderWindow> figureRenWin, vtkSmartPointer<vtkRenderWindow> chartRenWin, 
	vtkSmartPointer<vtkColorTransferFunction> tf, const std::string xLabel, const std::string yLabel, const double minBound, const double maxBound) {
	this->tf = tf;

	chart = vtkSmartPointer<ChartXY>::New();
	
	chart->GetAxis(0)->SetTitle(yLabel);
	chart->GetAxis(1)->SetTitle(xLabel);

	// plots cannot change axis ranges
	chart->GetAxis(0)->SetBehavior(vtkAxis::FIXED);
	chart->GetAxis(1)->SetBehavior(vtkAxis::FIXED);

	function = vtkSmartPointer<vtkColorTransferFunctionItem>::New();
	function->SetColorTransferFunction(tf);
	chart->AddPlot(function);

	controlPoints = vtkSmartPointer<ColorTransferControlPointsItem>::New();
	controlPoints->SetRenderWindow(figureRenWin);
	controlPoints->SetColorTransferFunction(tf);
	controlPoints->SetUserBounds(minBound, maxBound, 0, 1);
	chart->AddPlot(controlPoints);

	context = vtkSmartPointer<vtkContextView>::New();
	context->SetRenderWindow(chartRenWin);
	context->GetScene()->AddItem(chart);

	defaultRange();
}

ColorTFChart::~ColorTFChart() {

}

void ColorTFChart::defaultRange() {
	chart->GetAxis(0)->SetRange(0, 1); // Y axis range
	chart->GetAxis(1)->SetRange(tf->GetRange()[0], tf->GetRange()[1]); // X axis range
	context->Render(); 
}

void ColorTFChart::setRange(const double min, const double max) {
	chart->GetAxis(1)->SetRange(min, max);
	context->Render();
}