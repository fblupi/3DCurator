#include "ROD.h"

ROD::ROD(const std::string name, const double* origin, const double* point1, const double* point2, const double slice) {
	this->name = name;
	this->slice = slice;

	this->origin = new double[3];
	this->point1 = new double[3];
	this->point2 = new double[3];

	this->origin[0] = origin[0];
	this->origin[1] = origin[1];
	this->origin[2] = origin[2];
	this->point1[0] = point1[0];
	this->point1[1] = point1[1];
	this->point1[2] = point1[2];
	this->point2[0] = point2[0];
	this->point2[1] = point2[1];
	this->point2[2] = point2[2];
}

std::string ROD::getName() const {
	return std::string();
}

double* ROD::getOrigin() const {
	return origin;
}

double* ROD::getPoint1() const {
	return point1;
}

double* ROD::getPoint2() const {
	return point2;
}

double ROD::getSlicePosition() const {
	return slice;
}
std::map<QListWidgetItem*, vtkSmartPointer<vtkDistanceWidget> > ROD::getRules() const {
	return rules;
}

std::map<QListWidgetItem*, vtkSmartPointer<vtkAngleWidget> > ROD::getProtractors() const {
	return protractors;
}

std::map<double*, std::string> ROD::getAnnotations() const {
	return annotations;
}

void ROD::setName(const std::string name) {
	this->name = name;
}

void ROD::clearAllRules() {
	rules.clear();
}

void ROD::clearAllProtractors() {
	protractors.clear();
}

void ROD::clearAllAnnotations() {
	annotations.clear();
}