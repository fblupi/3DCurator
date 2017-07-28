#include "ROD.h"

ROD::ROD(const std::string name, const double* origin, const double* point1, const double* point2, const double slice, const QFont enabled, const QFont disabled) {
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

	this->enabled = enabled;
	this->disabled = disabled;
}

ROD::~ROD() {
	delete origin;
	delete point1;
	delete point2;
	clearAllRules();
	clearAllProtractors();
	clearAllAnnotations();
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

void ROD::addRule(QListWidgetItem* item, vtkSmartPointer<vtkRenderWindowInteractor> interactor) {
	rules[item] = vtkSmartPointer<vtkDistanceWidget>::New();
	rules[item]->SetInteractor(interactor);
	rules[item]->CreateDefaultRepresentation();
	static_cast<vtkDistanceRepresentation *>(rules[item]->GetRepresentation())->SetLabelFormat("%-#6.3g mm");
	rules[item]->On();
}

void ROD::deleteRule(QListWidgetItem* item) {
	rules.erase(item);
}

void ROD::enableRule(QListWidgetItem* item) {
	item->setFont(enabled);
	rules[item]->On();
}

void ROD::disableRule(QListWidgetItem* item) {
	item->setFont(disabled);
	rules[item]->Off();
}

void ROD::enableDisableRule(QListWidgetItem* item) {
	if (item->font() == disabled) {
		enableRule(item);
		item->setFont(enabled);
	} else {
		disableRule(item);
		item->setFont(disabled);
	}
}

void ROD::hideAllRules() {
	std::map<QListWidgetItem*, vtkSmartPointer<vtkDistanceWidget> >::iterator it;
	for (it = rules.begin(); it != rules.end(); ++it) {
		it->first->setHidden(true);
		it->second->Off();
	}
}

void ROD::showAllRules() {
	std::map<QListWidgetItem*, vtkSmartPointer<vtkDistanceWidget> >::iterator it;
	for (it = rules.begin(); it != rules.end(); ++it) {
		it->first->setHidden(false);
		if (it->first->font() == enabled) {
			it->second->On();
		}
	}
}

void ROD::clearAllRules() {
	rules.clear();
}

void ROD::addProtractor(QListWidgetItem* item, vtkSmartPointer<vtkRenderWindowInteractor> interactor) {
	protractors[item] = vtkSmartPointer<vtkAngleWidget>::New();
	protractors[item]->SetInteractor(interactor);
	protractors[item]->CreateDefaultRepresentation();
	protractors[item]->On();
}

void ROD::deleteProtractor(QListWidgetItem* item) {
	protractors.erase(item);
}

void ROD::enableProtractor(QListWidgetItem* item) {
	item->setFont(enabled);
	protractors[item]->On();
}

void ROD::disableProtractor(QListWidgetItem* item) {
	item->setFont(disabled);
	protractors[item]->Off();
}

void ROD::enableDisableProtractor(QListWidgetItem* item) {
	if (item->font() == disabled) {
		enableProtractor(item);
		item->setFont(enabled);
	}
	else {
		disableProtractor(item);
		item->setFont(disabled);
	}
}

void ROD::hideAllProtractors() {
	std::map<QListWidgetItem*, vtkSmartPointer<vtkAngleWidget> >::iterator it;
	for (it = protractors.begin(); it != protractors.end(); ++it) {
		it->first->setHidden(true);
		it->second->Off();
	}
}

void ROD::showAllProtractors() {
	std::map<QListWidgetItem*, vtkSmartPointer<vtkAngleWidget> >::iterator it;
	for (it = protractors.begin(); it != protractors.end(); ++it) {
		it->first->setHidden(false);
		if (it->first->font() == enabled) {
			it->second->On();
		}
	}
}

void ROD::clearAllProtractors() {
	protractors.clear();
}

void ROD::addAnnotation(QListWidgetItem* item, std::string text, vtkSmartPointer<vtkRenderWindowInteractor> interactor) {
	vtkSmartPointer<vtkCaptionRepresentation> captionRepresentation = vtkSmartPointer<vtkCaptionRepresentation>::New();
	captionRepresentation->GetCaptionActor2D()->SetCaption(text.c_str());
	captionRepresentation->GetCaptionActor2D()->BorderOff();
	captionRepresentation->GetCaptionActor2D()->GetTextActor()->SetMinimumSize(300, 300);
	annotations[item] = vtkSmartPointer<vtkCaptionWidget>::New();
	annotations[item]->SetInteractor(interactor);
	annotations[item]->CreateDefaultRepresentation();
	annotations[item]->SetRepresentation(captionRepresentation);
	annotations[item]->On();
}

void ROD::deleteAnnotation(QListWidgetItem* item) {
	annotations.erase(item);
}

void ROD::enableAnnotation(QListWidgetItem* item) {
	item->setFont(enabled);
	annotations[item]->On();
}

void ROD::disableAnnotation(QListWidgetItem* item) {
	item->setFont(disabled);
	annotations[item]->Off();
}

void ROD::enableDisableAnnotation(QListWidgetItem* item) {
	if (item->font() == disabled) {
		enableAnnotation(item);
		item->setFont(enabled);
	} else {
		disableAnnotation(item);
		item->setFont(disabled);
	}
}

void ROD::hideAllAnnotations() {
	std::map<QListWidgetItem*, vtkSmartPointer<vtkCaptionWidget> >::iterator it;
	for (it = annotations.begin(); it != annotations.end(); ++it) {
		it->first->setHidden(true);
		it->second->Off();
	}
}

void ROD::showAllAnnotations() {
	std::map<QListWidgetItem*, vtkSmartPointer<vtkCaptionWidget> >::iterator it;
	for (it = annotations.begin(); it != annotations.end(); ++it) {
		it->first->setHidden(false);
		if (it->first->font() == enabled) {
			it->second->On();
		}
	}
}

void ROD::clearAllAnnotations() {
	annotations.clear();
}

void ROD::hideAll() {
	hideAllRules();
	hideAllProtractors();
	hideAllAnnotations();
}

void ROD::showAll() {
	showAllRules();
	showAllProtractors();
	showAllAnnotations();
}

bool ROD::samePlane(const double* origin, const double* point1, const double* point2, const double slice) {
	return (
		this->origin[0] == origin[0] &&
		this->origin[1] == origin[1] &&
		this->origin[2] == origin[2] &&
		this->point1[0] == point1[0] &&
		this->point1[1] == point1[1] &&
		this->point1[2] == point1[2] &&
		this->point2[0] == point2[0] &&
		this->point2[1] == point2[1] &&
		this->point2[2] == point2[2] &&
		this->slice == slice
	);
}
