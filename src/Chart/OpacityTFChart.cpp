#include "OpacityTFChart.h"

OpacityTFChart::OpacityTFChart(const vtkSmartPointer<vtkRenderWindow> &figureRenWin, vtkSmartPointer<vtkPiecewiseFunction> tf, const std::string &xLabel, const std::string &yLabel, double minBound, double maxBound) :
    tf(std::move(tf)),
    chart(vtkSmartPointer<ChartXY>::New()),
    function(vtkSmartPointer<vtkPiecewiseFunctionItem>::New()),
    controlPoints(vtkSmartPointer<PiecewiseControlPointsItem>::New()),
    context(vtkSmartPointer<vtkContextView>::New())
{
    chart->GetAxis(0)->SetTitle(yLabel);
    chart->GetAxis(1)->SetTitle(xLabel);

    // plots cannot change axis ranges
    chart->GetAxis(0)->SetBehavior(vtkAxis::FIXED);
    chart->GetAxis(1)->SetBehavior(vtkAxis::FIXED);

    function->SetPiecewiseFunction(this->tf);
    chart->AddPlot(function);

    controlPoints->SetRenderWindow(figureRenWin);
    controlPoints->SetPiecewiseFunction(this->tf);
    controlPoints->SetUserBounds(minBound, maxBound, 0, 1);
    chart->AddPlot(controlPoints);

    // Axis ranges set here; rendering deferred until setRenderWindow
    chart->GetAxis(0)->SetRange(0, 1);
    chart->GetAxis(1)->SetRange(this->tf->GetRange()[0], this->tf->GetRange()[1]);
}

void OpacityTFChart::setRenderWindow(vtkRenderWindow* renWin) {
    context->SetRenderWindow(renWin);
    context->GetScene()->AddItem(chart);
    context->Render();
}

OpacityTFChart::~OpacityTFChart() = default;

void OpacityTFChart::defaultRange() {
    chart->GetAxis(0)->SetRange(0, 1); // Y axis range
    chart->GetAxis(1)->SetRange(tf->GetRange()[0], tf->GetRange()[1]); // X axis range
    context->Render();
}

void OpacityTFChart::setRange(double min, double max) {
    chart->GetAxis(1)->SetRange(min, max);
    context->Render();
}
