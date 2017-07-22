#include "ROD.h"

ROD::ROD(std::string name, double* origin, double* point1, double* point2) {
	this->name = name;
	planePosition.origin = origin;
	planePosition.point1 = point1;
	planePosition.point2 = point2;
}

std::string ROD::getName() const {
	return std::string();
}

double* ROD::getOrigin() const {
	return planePosition.origin;
}

double* ROD::getPoint1() const {
	return planePosition.point1;
}

double* ROD::getPoint2() const {
	return planePosition.point2;
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

void ROD::setOrigin(const double* origin) {
	planePosition.origin[0] = origin[0];
	planePosition.origin[1] = origin[1];
	planePosition.origin[2] = origin[2];
}

void ROD::setPoint1(const double* point1) {
	planePosition.point1[0] = point1[0];
	planePosition.point1[1] = point1[1];
	planePosition.point1[2] = point1[2];
}

void ROD::setPoint2(const double* point2) {
	planePosition.point2[0] = point2[0];
	planePosition.point2[1] = point2[1];
	planePosition.point2[2] = point2[2];
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