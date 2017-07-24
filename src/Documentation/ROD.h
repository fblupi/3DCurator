#ifndef ROD_H
#define ROD_H

#include <QListWidget>
#include <QFont>

#include <string>
#include <map>
#include <vector>

#include <vtkSmartPointer.h>
#include <vtkDistanceWidget.h>
#include <vtkDistanceRepresentation.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkAngleWidget.h>

class ROD {
public:
	/**
	 * Constructor
	 * @param	name		ROD name
	 * @param	origin		Origin of the plane
	 * @param	point1		Position of the point defining the first axis of the plane
	 * @param	point2		Position of the point defining the second axis of the plane
	 * @param	slice		Slice position in terms of data extent
	 * @param	enabled		Font for enabled list elements
	 * @param	disabled	Font for disabled list elements
	 */
	ROD(const std::string name, const double* origin, const double* point1, const double* point2, const double slice, const QFont enabled, const QFont disabled);

	/**
	 * Get ROD name
	 * @return	ROD name
	 */
	std::string getName() const;

	/**
	 * Get origin of the plane
	 * @return	Origin of the plane
	 */
	double* getOrigin() const;

	/**
	 * Get position of the point defining the first axis of the plane
	 * @return	Position of the point defining the first axis of the plane
	 */
	double* getPoint1() const;

	/**
	 * Get position of the point defining the second axis of the plane
	 * @return	Position of the point defining the second axis of the plane
	 */
	double* getPoint2() const;

	/**
	 * Get slice position in terms of data extent
	 * @return	Slice position in terms of data extent
	 */
	double getSlicePosition() const;

	/**
	 * Get ROD rules
	 * @return	ROD rules
	 */
	std::map<QListWidgetItem*, vtkSmartPointer<vtkDistanceWidget> > getRules() const;

	/**
	 * Get ROD protractors
	 * @return	ROD protractors
	 */
	std::map<QListWidgetItem*, vtkSmartPointer<vtkAngleWidget> > getProtractors() const;

	/**
	 * Get ROD annotations
	 * @return	ROD annotations
	 */
	std::map<double*, std::string> getAnnotations() const;

	/**
	 * Set ROD name
	 * @param	name	ROD name
	 */
	void setName(const std::string name);

	/**
	 * Add new rule to measure
	 * @param	item	Rule item in UI
	 */
	void addRule(QListWidgetItem* item, vtkSmartPointer<vtkRenderWindowInteractor> interactor);

	/**
	 * Delete selected rule
	 * @param	item	Rule item in UI
	 */
	void deleteRule(QListWidgetItem* item);

	/**
	 * Enable or disable selected rule
	 * @param	item	Rule item in UI
	 */
	void enableDisableRule(QListWidgetItem* item);

	/**
	 * Enable selected rule
	 * @param	item	Rule item in UI
	 */
	void enableRule(QListWidgetItem* item);

	/**
	 * Disable selected rule
	 * @param	item	Rule item in UI
	 */
	void disableRule(QListWidgetItem* item);

	/**
	 * Hide all rules
	 */
	void hideAllRules();

	/**
	 * Show all rules
	 */
	void showAllRules();

	/**
	 * Delete all rules
	 */
	void clearAllRules();

	/**
	 * Delete all protractors
	 */
	void clearAllProtractors();

	/**
	 * Delete all annotations
	 */
	void clearAllAnnotations();

private:
	std::string name; /**< ROD name */
	double* origin; /**< Origin of the plane */
	double* point1; /**< Position of the point defining the first axis of the plane */
	double* point2; /**< Position of the point defining the second axis of the plane */
	double slice; /**< Slice position in terms of data extent */
	std::map<QListWidgetItem*, vtkSmartPointer<vtkDistanceWidget> > rules; /**< Rules container */
	std::map<QListWidgetItem*, vtkSmartPointer<vtkAngleWidget> > protractors; /**< Rules container */
	std::map<double*, std::string> annotations; /**< Annotations container */

	QFont enabled; /**< Font for list enabled elements */
	QFont disabled; /**< Font for list disabled elements */
};

#endif