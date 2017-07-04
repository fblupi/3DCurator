#ifndef WOODSEGMENTATION_H
#define WOODSEGMENTATION_H

#include <queue>
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

#include "Utils/geometry.h"
#include "Segmentation/segmentationCommons.h"

#define MIN_ANGLE	0.5	/**< Min angle for nearest line */
#define MIN_DISTA	5	/**< Min for nearest line */
#define LINE_TOLERANCE	5	/**< Line tolerance to check if a point is contained by a line */
#define MIN_WOOD	-750	/**< Min wood value */
#define MAX_WOOD	-300	/**< Max wood value */
#define AIR_HU		-1000	/**< Air value */

/**
 * Check if the first line is longer than the second
 * @param	i	One line
 * @param	j	Another line
 * @return		First line is longer
 */
bool longerLine(const HoughLine i, const HoughLine j);

/**
 * Get ordered (first longer) lines found with hough transform in a slice
 * @param	imageData	3D image data
 * @param	colorFun	Mapper scalar to colors
 * @param	slice		Index of the slice
 * @param	bounds		Image bounds
 * @return	Vector with ordered obtained lines
 */
std::vector<Line> getLinesFromImage(vtkSmartPointer<vtkImageData> imageData, vtkSmartPointer<vtkColorTransferFunction> colorFun, const int slice, const Bounds bounds);

/**
 * Generate a PNG image from a slice and its five longer lines
 * @param	imageData	3D image data
 * @param	colorFun	Mapper scalar to colors
 * @param	slice		Index of the slice
 * @param	bounds		Image bounds
 * @param	lines		Vector with lines
 * @return	Filename of the output PNG image
 */
std::string generateImage(vtkSmartPointer<vtkImageData> imageData, vtkSmartPointer<vtkColorTransferFunction> colorFun, const int slice, const Bounds bounds, std::vector<Line> lines);

/**
 * Check if a point is contained by a line
 * @param	coord		Point coordinates
 * @param	eq		Line equation
 * @param	epsilon		Tolerance
 * @return	Point is contained by the line or not
 */
bool isInLine(const Coord2D coord, const LineEq eq, const int epsilon);

/**
 * Check if a voxel is wood
 * @param	imageData	3D image data
 * @param	coord		Voxel
 * @param	MIN		Minimum value of wood
 * @param	MAX		Maximum value of wood
 * @return	Voxel is wood or not
 */
bool isAdjacent(vtkSmartPointer<vtkImageData> imageData, const Coord3D coord, const double MIN, const double MAX);

/**
 * Search an initial valid voxel from a not valid one using a circular expansion
 * @param	imageData	3D image data
 * @param	ijk		Initial voxel
 * @param	bounds		Image bounds
 * @param	MIN		Minimum value of wood
 * @param	MAX		Maximum value of wood
 * @param	eq		Line equation
 * @return	Initial valid voxel
 */
Coord2D searchInitialVoxel(vtkSmartPointer<vtkImageData> imageData, const int ijk[3], const Bounds bounds, const double MIN, const double MAX, const LineEq eq);

/**
 * 2D region growing with a line bound
 * @param	imageData	3D image data
 * @param	ijk		Initial voxel
 * @param	bounds		Image bounds
 * @param	eq		Line equation
 * @return	Midpoint of the region
 */
Coord2D regionGrowingWithLineBoundImage(vtkSmartPointer<vtkImageData> imageData, const int ijk[3], const Bounds bounds, const LineEq eq);

/**
 * Find the line nearest to the goal using angles and distances
 * @param	lines		Vector with lines
 * @param	goal		Goal line
 * @param	originalZ	Z coordinate in goal line
 * @param	z		Z coordinate in lines
 * @return	Nearest line and its angle with goal
 */
std::pair<Line, double> findNearestLine(std::vector<Line> lines, const Line goal, const int originalZ, const int z);

/**
 * 3D region growing with a line bound
 * @param	imageData	3D image data
 * @param	colorFun	Mapper scalar to colors
 * @param	ijk		Initial voxel
 * @param	bounds		Image bounds
 * @param	firstLine	Initial line
 * @param	lines		Lines for each slice
 */
void regionGrowingWithLineBoundVolume(vtkSmartPointer<vtkImageData> imageData, vtkSmartPointer<vtkColorTransferFunction> colorFun, const int ijk[3], const Bounds bounds, const Line firstLine, std::vector<std::vector<Line> > &lines);

#endif // WOODSEGMENTATION_H