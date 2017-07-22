#ifndef ROD_H
#define ROD_H

#include <QListWidget>

#include <string>
#include <map>
#include <vector>

#include <vtkSmartPointer.h>
#include <vtkDistanceWidget.h>
#include <vtkAngleWidget.h>

struct PlanePosition {
	double* origin;
	double* point1;
	double* point2;
};

class ROD {
public:
	ROD(std::string name, double* origin, double* point1, double* point2);

	std::string getName() const;
	double* getOrigin() const;
	double* getPoint1() const;
	double* getPoint2() const;
	std::map<QListWidgetItem*, vtkSmartPointer<vtkDistanceWidget> > getRules() const;
	std::map<QListWidgetItem*, vtkSmartPointer<vtkAngleWidget> > getProtractors() const;
	std::map<double*, std::string> getAnnotations() const;

	void setName(const std::string name);
	void setOrigin(const double* origin);
	void setPoint1(const double* point1);
	void setPoint2(const double* point2);

	void clearAllRules();
	void clearAllProtractors();
	void clearAllAnnotations();

private:
	std::string name; /**< ROD name */
	PlanePosition planePosition; /**< Plane position for ROD */
	std::map<QListWidgetItem*, vtkSmartPointer<vtkDistanceWidget> > rules; /**< Rules container */
	std::map<QListWidgetItem*, vtkSmartPointer<vtkAngleWidget> > protractors; /**< Rules container */
	std::map<double*, std::string> annotations; /**< Annotations container */
};

#endif