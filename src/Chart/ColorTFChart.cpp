#include "ColorTFChart.h"

ColorTFChart::ColorTFChart(const vtkSmartPointer<vtkRenderWindow> &figureRenWin, const vtkSmartPointer<vtkRenderWindow> &chartRenWin, vtkSmartPointer<vtkColorTransferFunction> tf, const std::string &xLabel, const std::string &yLabel, double minBound, double maxBound) :
    tf(std::move(tf)),
    chart(vtkSmartPointer<ChartXY>::New()),
    function(vtkSmartPointer<vtkColorTransferFunctionItem>::New()),
    controlPoints(vtkSmartPointer<ColorTransferControlPointsItem>::New()),
    context(vtkSmartPointer<vtkContextView>::New())
{
    chart->GetAxis(0)->SetTitle(yLabel);
    chart->GetAxis(1)->SetTitle(xLabel);

    // plots cannot change axis ranges
    chart->GetAxis(0)->SetBehavior(vtkAxis::FIXED);
    chart->GetAxis(1)->SetBehavior(vtkAxis::FIXED);

    function->SetColorTransferFunction(tf);
    chart->AddPlot(function);

    controlPoints->SetRenderWindow(figureRenWin);
    controlPoints->SetColorTransferFunction(tf);
    controlPoints->SetUserBounds(minBound, maxBound, 0, 1);
    chart->AddPlot(controlPoints);

    context->SetRenderWindow(chartRenWin);
    context->GetScene()->AddItem(chart);

    defaultRange();
}

ColorTFChart::~ColorTFChart() = default;

void ColorTFChart::defaultRange() {
    chart->GetAxis(0)->SetRange(0, 1); // Y axis range
    chart->GetAxis(1)->SetRange(tf->GetRange()[0], tf->GetRange()[1]); // X axis range
    context->Render();
}

void ColorTFChart::setRange(double min, double max) {
    chart->GetAxis(1)->SetRange(min, max);
    context->Render();
}
