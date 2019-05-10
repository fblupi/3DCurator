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

#include "Chart/PiecewiseControlPointsItem.h"
#include "Chart/ChartXY.h"

/**
 * @class OpacityTFChart
 * Class that shows a chart with the control points and the function used by a opacity transfer function
 */
class OpacityTFChart {
public:
    /**
     * Constructor
     * @param	figureRenWin    RenderWindow that will be updated when the opacity function is updated
     * @param	chartRenWin	    RenderWindow where will be placed the chart
     * @param	tf		        Opacity transfer function
     * @param	xLabel		    Axis X label name
     * @param	yLabel		    Axis Y label name
     * @param	minBound	    Min control points bound
     * @param	maxBound	    Max control points bound
     */
    OpacityTFChart(const vtkSmartPointer<vtkRenderWindow> &figureRenWin, const vtkSmartPointer<vtkRenderWindow> &chartRenWin, vtkSmartPointer<vtkPiecewiseFunction> tf, const std::string &xLabel, const std::string &yLabel, double minBound, double maxBound);

    /**
     * Destructor
     */
    ~OpacityTFChart();

    /**
     * Range of Y axes goes from the lowest to the highest transfer function value
     */
    void defaultRange();

    /**
     * Range of Y axes gos from min to max
     * @param	min	Min bound
     * @param	max	Max bound
     */
    void setRange(double min, double max);

private:
    vtkSmartPointer<ChartXY> chart;  /**< Chart where both function and control points plots will be placed */
    vtkSmartPointer<vtkContextView> context; /**< ContextView where the chart content will be rendered */
    vtkSmartPointer<vtkPiecewiseFunctionItem> function; /**< Plot where the opacity function will be shown */
    vtkSmartPointer<PiecewiseControlPointsItem> controlPoints; /**> Plot where the function control points will be shown */
    vtkSmartPointer<vtkPiecewiseFunction> tf; /**< Color transfer function used by both plots */
};

#endif // OPACITYTFCHART_H