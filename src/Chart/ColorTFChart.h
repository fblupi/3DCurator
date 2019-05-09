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

#include "Chart/ColorTransferControlPointsItem.h"
#include "Chart/ChartXY.h"

/**
 * @class ColorTFChart
 * Class that shows a chart with the control points and the color palette used by the transfer function
 */
class ColorTFChart {
public:
    /**
     * Constructor
     * @param	figureRenWin    RenderWindow that will be updated when the color function is updated
     * @param	chartRenWin	    RenderWindow where will be placed the chart
     * @param	tf		        Color transfer function
     * @param	xLabel		    Axis X label name
     * @param	yLabel		    Axis Y label name
     * @param	minBound	    Min control points bound
     * @param	maxBound	    Max control points bound
     */
    ColorTFChart(const vtkSmartPointer<vtkRenderWindow> &figureRenWin, const vtkSmartPointer<vtkRenderWindow> &chartRenWin, vtkSmartPointer<vtkColorTransferFunction> tf, const std::string &xLabel, const std::string &yLabel, double minBound, double maxBound);

    /**
     * Destructor
     */
    ~ColorTFChart();

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
    vtkSmartPointer<ChartXY> chart; /**> Chart where both function and control points plots will be placed */
    vtkSmartPointer<vtkContextView> context; /**> ContextView where the chart content will be rendered */
    vtkSmartPointer<vtkColorTransferFunctionItem> function; /**> Plot where the color function will be shown */
    vtkSmartPointer<ColorTransferControlPointsItem> controlPoints; /**> Plot where the function control points will be shown */
    vtkSmartPointer<vtkColorTransferFunction> tf; /**< Color transfer function used by both plots */
};

#endif // COLORTFCHART_H
