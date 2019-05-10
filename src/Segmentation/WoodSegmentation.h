#ifndef WOODSEGMENTATION_H
#define WOODSEGMENTATION_H

#include <queue>
#include <set>
#include <array>

#include <vtkSmartPointer.h>
#include <vtkImageData.h>
#include <vtkImageMapToColors.h>
#include <vtkColorTransferFunction.h>
#include <vtkExtractVOI.h>
#include <vtkPNGWriter.h>

#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"

#include "Util/Geometry.h"
#include "Util/Measures.h"
#include "Segmentation/SegmentationCommons.h"

/**
 * Check if the first line is longer than the second
 * @param	i	One line
 * @param	j	Another line
 * @return		First line is longer
 */
bool longerLine(const HoughLine &i, const HoughLine &j);

/**
 * Get ordered (first longer) lines found with hough transform in a slice
 * @param	imageData	3D image data
 * @param	colorFun	Mapper scalar to colors
 * @param	slice		Index of the slice
 * @param	bounds		Image bounds
 * @return	Vector with ordered obtained lines
 */
std::vector<Line> getLinesFromImage(const vtkSmartPointer<vtkImageData> &imageData, const vtkSmartPointer<vtkColorTransferFunction> &colorFun, int slice, const Bounds &bounds);

/**
 * Generate a PNG image from a slice and its five longer lines
 * @param	imageData	3D image data
 * @param	colorFun	Mapper scalar to colors
 * @param	slice		Index of the slice
 * @param	bounds		Image bounds
 * @param	lines		Vector with lines
 * @return	Filename of the output PNG image
 */
std::string generateImage(const vtkSmartPointer<vtkImageData> &imageData, const vtkSmartPointer<vtkColorTransferFunction> &colorFun, int slice, const Bounds &bounds, const std::vector<Line> &lines);

/**
 * Check if a point is contained by a line
 * @param	coord		Point coordinates
 * @param	eq		    Line equation
 * @param	epsilon		Tolerance
 * @return	Point is contained by the line or not
 */
bool isInLine(const Coord2D &coord, const LineEq &eq, int epsilon);

/**
 * Check if a voxel is wood
 * @param	imageData	3D image data
 * @param	coord		Voxel
 * @param	min		    Minimum value of wood
 * @param	max		    Maximum value of wood
 * @return	Voxel is wood or not
 */
bool isAdjacent(const vtkSmartPointer<vtkImageData> &imageData, const Coord3D &coord, double min, double max);

/**
 * Search an initial valid voxel from a not valid one using a circular expansion
 * @param	imageData	3D image data
 * @param	ijk		    Initial voxel
 * @param	bounds		Image bounds
 * @param	min		    Minimum value of wood
 * @param	max		    Maximum value of wood
 * @param	eq		    Line equation
 * @return	Initial valid voxel
 */
Coord2D searchInitialVoxel(const vtkSmartPointer<vtkImageData> &imageData, const int ijk[3], const Bounds &bounds, double min, double max, const LineEq &eq);

/**
 * 2D region growing with a line bound
 * @param	inputData	Input 3D image data
 * @param	outputData	Output 3D image data
 * @param	ijk		    Initial voxel
 * @param	bounds		Image bounds
 * @param	eq		    Line equation
 * @return	Midpoint of the region
 */
Coord2D regionGrowingWithLineBoundImage(const vtkSmartPointer<vtkImageData> &inputData, const vtkSmartPointer<vtkImageData> &outputData, const int ijk[3], const Bounds &bounds, const LineEq &eq);

/**
 * Find the line nearest to the goal using angles and distances
 * @param	lines		Vector with lines
 * @param	goal		Goal line
 * @param	originalZ	Z coordinate in goal line
 * @param	z		    Z coordinate in lines
 * @return	Nearest line and its angle with goal
 */
std::pair<Line, double> findNearestLine(const std::vector<Line> &lines, const Line &goal, int originalZ, int z);

/**
 * 3D region growing with a line bound
 * @param	inputData	    Input 3D image data
 * @param	outputData	    Output 3D image data
 * @param	colorFun	    Mapper scalar to colors
 * @param	ijk		        Initial voxel
 * @param	bounds		    Image bounds
 * @param	firstLine	    Initial line
 * @param	lines		    Lines for each slice
 * @param	completeUp	    Force to segment every slice to the top
 * @param	completeDown	Force to segment every slice to the bottom
 */
void regionGrowingWithLineBoundVolume(const vtkSmartPointer<vtkImageData> &inputData, const vtkSmartPointer<vtkImageData> &outputData, const vtkSmartPointer<vtkColorTransferFunction> &colorFun, const int ijk[3], const Bounds &bounds, const Line &firstLine, std::vector<std::vector<Line> > &lines, bool completeUp, bool completeDown);

#endif // WOODSEGMENTATION_H
