#ifndef SEGMENTATIONCOMMONS_H
#define SEGMENTATIONCOMMONS_H

#include <array>
#include "opencv2/core/types.hpp"

struct Bounds {
	int MIN_X;
	int MAX_X;
	int MIN_Y;
	int MAX_Y;
	int MIN_Z;
	int MAX_Z;
};

typedef std::pair<cv::Point, cv::Point> Line;
typedef std::pair<Line, double> HoughLine;
typedef std::array<int, 2> Coord2D;
typedef std::array<int, 3> Coord3D;
typedef std::array<double, 2> LineEq;
typedef std::array<double, 4> PlaneEq;

#endif // SEGMENTATIONCOMMONS_H