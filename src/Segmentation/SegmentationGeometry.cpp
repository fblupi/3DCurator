#include "SegmentationGeometry.h"

SegmentationGeometry::SegmentationGeometry(vtkSmartPointer<vtkImageData> imageData, vtkSmartPointer<vtkColorTransferFunction> colorFun) {
	this->imageData = imageData;
	this->colorFun = colorFun;
	int* dimensions = imageData->GetDimensions();
	bounds.MIN_X = 0;
	bounds.MAX_X = dimensions[0];
	bounds.MIN_Y = 0;
	bounds.MAX_Y = dimensions[1];
	bounds.MIN_Z = 0;
	bounds.MAX_Z = dimensions[2];

	linesAxial.resize(bounds.MAX_Z);
	linesSagital.resize(bounds.MAX_Y);
	linesCoronal.resize(bounds.MAX_X);
}

void SegmentationGeometry::generateLines() {
	generateLinesAxial();
	//generateLinesSagital();
	//generateLinesCoronal();
}

void SegmentationGeometry::generateLinesAxial() {
	for (unsigned int i = 0; i < linesAxial.size(); i++) {
		std::cout << "A: " << i << std::endl;
		linesAxial[i] = getLinesFromImage(AnatomicalPlane::Axial, i);
		std::cout << "\t" << linesAxial[i].size() << std::endl;
	}
}

void SegmentationGeometry::generateLinesSagital() {
	for (unsigned int i = 0; i < linesSagital.size(); i++) {
		std::cout << "S: " << i << std::endl;
		linesSagital[i] = getLinesFromImage(AnatomicalPlane::Sagital, i);
		std::cout << "\t" << linesSagital[i].size() << std::endl;
	}
}

void SegmentationGeometry::generateLinesCoronal() {
	for (unsigned int i = 0; i < linesCoronal.size(); i++) {
		std::cout << "C: " << i << std::endl;
		linesCoronal[i] = getLinesFromImage(AnatomicalPlane::Coronal, i);
		std::cout << "\t" << linesCoronal[i].size() << std::endl;
	}
}

std::vector<Line> SegmentationGeometry::getLinesFromImage(AnatomicalPlane anatomicalPlane, unsigned int slice) {
	vtkSmartPointer<vtkImageMapToColors> map = vtkSmartPointer<vtkImageMapToColors>::New();
	map->SetInputData(imageData);
	map->SetLookupTable(colorFun);

	vtkSmartPointer<vtkExtractVOI> voi = vtkSmartPointer<vtkExtractVOI>::New();
	voi->SetInputConnection(map->GetOutputPort());
	switch (anatomicalPlane) {
	case AnatomicalPlane::Axial:
		voi->SetVOI(bounds.MIN_X, bounds.MAX_X - 1, bounds.MIN_Y, bounds.MAX_Y - 1, slice, slice);
		break;
	case AnatomicalPlane::Sagital:
		voi->SetVOI(bounds.MIN_X, bounds.MAX_X - 1, slice, slice, bounds.MIN_Z, bounds.MAX_Z - 1);
		break;
	case AnatomicalPlane::Coronal:
		voi->SetVOI(slice, slice, bounds.MIN_Y, bounds.MAX_Y - 1, bounds.MIN_Z, bounds.MAX_Z - 1);
		break;
	}
	voi->Update();

	std::string filename = "tmp" + std::to_string(slice) + ".png";

	vtkSmartPointer<vtkPNGWriter> png = vtkSmartPointer<vtkPNGWriter>::New();
	png->SetInputData(voi->GetOutput());
	png->SetFileName(filename.c_str());
	png->Write();

	cv::Mat src, dst, cdst;
	src = cv::imread(filename.c_str(), 0);
	remove(filename.c_str());

	cv::Canny(src, dst, 30, 50, 3);
	cv::cvtColor(dst, cdst, cv::COLOR_GRAY2BGR);

	std::vector<cv::Vec4i> lines;
	cv::HoughLinesP(dst, lines, 1, CV_PI / 180, 50, 50, 10);
	std::vector<HoughLine> foundLines;
	for (int i = 0; i < lines.size(); i++) {
		HoughLine l = std::make_pair(
			std::make_pair(
				cv::Point(lines[i][0], lines[i][1]),
				cv::Point(lines[i][2], lines[i][3])
			),
			cv::norm(cv::Point(lines[i][0], lines[i][1]) - cv::Point(lines[i][2], lines[i][3])));
		foundLines.push_back(l);
	}

	std::vector<Line> result(foundLines.size());

	for (int i = 0; i < foundLines.size(); i++) {
		result[i] = foundLines[i].first;
	}

	return result;
}

void SegmentationGeometry::clear() {
	linesAxial.clear();
	linesSagital.clear();
	linesCoronal.clear();
}

std::vector<std::vector<Line>> SegmentationGeometry::getLinesAxial() const {
	return linesAxial;
}

std::vector<std::vector<Line>> SegmentationGeometry::getLinesSagital() const {
	return linesSagital;
}

std::vector<std::vector<Line>> SegmentationGeometry::getLinesCoronal() const {
	return linesCoronal;
}
