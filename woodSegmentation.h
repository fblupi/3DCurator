#include <queue>
#include <array>
#include <stack>

#include <vtkSmartPointer.h>
#include <vtkImageMapToColors.h>
#include <vtkExtractVOI.h>
#include <vtkPNGWriter.h>

#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"

#include "figura.h"
#include "utils.h"

#define MIN_ANGLE 0.5
#define MIN_DISTA 5
#define LINE_TOLERANCE 5
#define MIN_WOOD -750
#define MAX_WOOD -300

typedef std::pair<cv::Point, cv::Point> Line;
typedef std::pair<Line, double> HoughLine;
typedef std::array<int, 2> Coord2D;
typedef std::array<int, 3> Coord3D;
typedef std::array<double, 2> LineEq;
typedef std::array<double, 4> PlaneEq;

struct Bounds {
	int MIN_X;
	int MAX_X;
	int MIN_Y;
	int MAX_Y;
	int MIN_Z;
	int MAX_Z;
};

/**
 * Check if the first line is longer than the second
 * @param i	one line
 * @param j another line
 * @return	first line is longer
 */
bool longerLine(HoughLine i, HoughLine j);

/**
 * Get ordered (first longer) lines found with hough transform in a slice
 * @param sculpture	3D image data
 * @param slice		index of the slice
 * @return			vector with ordered obtained lines
 */
std::vector<Line> getLinesFromImage(Figura *sculpture, int slice);

/**
 * Generate a PNG image from a slice and its five longer lines
 * @param sculpture	3D image data
 * @param slice		index of the slice
 * @param lines		vector with lines
 * @return			filename of the output PNG image
 */
std::string generateImage(Figura *sculpture, int slice, std::vector<Line> lines);

/**
 * Check if a point is contained by a line
 * @param coord		point coordinates
 * @param eq		line equation
 * @param epsilon	tolerance
 * @return			point is contained by the line or not
 */
bool isInLine(Coord2D coord, LineEq eq, int epsilon);

/**
 * Check if a voxel is wood
 * @param sculpture	3D image data
 * @param coord		voxel
 * @param MIN		minimum value of wood
 * @param MAX		maximum value of wood
 * @return			voxel is wood or not
 */
bool isAdjacent(Figura *sculpture, Coord3D coord, double MIN, double MAX);

/**
 * Search an initial valid voxel from a not valid one using a circular expansion
 * @param sculpture	3D image data
 * @param ijk		initial voxel
 * @param bounds	image bounds
 * @param MIN		minimum value of wood
 * @param MAX		maximum value of wood
 * @param eq		line equation
 * @return			initial valid voxel
 */
Coord2D searchInitialVoxel(Figura *sculpture, const int ijk[3], Bounds bounds, double MIN, double MAX, LineEq eq);

/**
 * 2D region growing with a line bound
 * @param sculpture	3D image data
 * @param ijk		initial voxel
 * @param bounds	image bounds
 * @param eq		line equation
 * @return			midpoint of the region
 */
Coord2D regionGrowingWithLineBoundImage(Figura *sculpture, const int ijk[3], Bounds bounds, LineEq eq);

/**
 * Find the line nearest to the goal using angles and distances
 * @param lines		vector with lines
 * @param goal		goal line
 * @param originalZ	z coordinate in goal line
 * @param z			z coordinate in lines
 * @return			nearest line and its angle with goal
 */
std::pair<Line, double> findNearestLine(std::vector<Line> lines, Line goal, const int originalZ, const int z);

/**
 * 3D region growing with a line bound
 * @param sculpture	3D image data
 * @param ijk		initial voxel
 * @param bounds	image bounds
 * @param firstLine	initial line
 * @param lines		lines for each slice
 */
void regionGrowingWithLineBoundVolume(Figura *sculpture, const int ijk[3], Bounds bounds, Line firstLine, std::vector<std::vector<Line> > &lines);