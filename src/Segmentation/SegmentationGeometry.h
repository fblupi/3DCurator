#ifndef SEGMENTATIONGEOMETRY_H
#define SEGMENTATIONGEOMETRY_H

#include <vector>

#include <vtkSmartPointer.h>
#include <vtkImageData.h>
#include <vtkColorTransferFunction.h>
#include <vtkImageMapToColors.h>
#include <vtkExtractVOI.h>
#include <vtkPNGWriter.h>

#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include "Segmentation/SegmentationCommons.h"

enum AnatomicalPlane {
	Axial,
	Sagital,
	Coronal
};

class SegmentationGeometry {
public:
	SegmentationGeometry(vtkSmartPointer<vtkImageData> imageData, vtkSmartPointer<vtkColorTransferFunction> colorFun);

	void generateLines();
	void generateLinesAxial();
	void generateLinesSagital();
	void generateLinesCoronal();

	std::vector<Line> getLinesFromImage(AnatomicalPlane anatomicalPlane, unsigned int slice);

	void clear();

	std::vector<std::vector<Line> > getLinesAxial() const;
	std::vector<std::vector<Line> > getLinesSagital() const;
	std::vector<std::vector<Line> > getLinesCoronal() const;
private:
	vtkSmartPointer<vtkImageData> imageData;
	vtkSmartPointer<vtkColorTransferFunction> colorFun;
	Bounds bounds;

	std::vector<std::vector<Line> > linesAxial;
	std::vector<std::vector<Line> > linesSagital;
	std::vector<std::vector<Line> > linesCoronal;
};

#endif // SEGMENTATIONGEOMETRY_H