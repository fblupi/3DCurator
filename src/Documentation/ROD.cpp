#include "ROD.h"

ROD::ROD(const std::string name, const double* origin, const double* point1, const double* point2, const double slice, const QFont enabled, const QFont disabled, vtkSmartPointer<vtkRenderWindowInteractor> interactor) {
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

	this->name = name;
	this->slice = slice;

	this->enabled = enabled;
	this->disabled = disabled;

	this->interactor = interactor;
}

ROD::ROD(std::string &filename, const QFont enabled, const QFont disabled, vtkSmartPointer<vtkRenderWindowInteractor> interactor, QListWidget* ruleList, QListWidget* protractorList, QListWidget *annotationList) {
	this->origin = new double[3];
	this->point1 = new double[3];
	this->point2 = new double[3];

	this->enabled = enabled;
	this->disabled = disabled;

	this->interactor = interactor;

	read(filename, ruleList, protractorList, annotationList);
}

ROD::~ROD() {
	delete origin;
	delete point1;
	delete point2;
	clearAllRules();
	clearAllProtractors();
	clearAllAnnotations();
}

std::string ROD::getName() const {
	return name;
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

std::map<QListWidgetItem*, vtkSmartPointer<vtkDistanceWidget>> ROD::getRules() const {
	return rules;
}

std::map<QListWidgetItem*, vtkSmartPointer<vtkAngleWidget>> ROD::getProtractors() const {
	return protractors;
}

std::map<QListWidgetItem*, vtkSmartPointer<vtkCaptionWidget>> ROD::getAnnotations() const {
	return annotations;
}

void ROD::addRule(QListWidgetItem* item) {
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

void ROD::addProtractor(QListWidgetItem* item) {
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

void ROD::addAnnotation(QListWidgetItem* item, std::string text) {
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

void ROD::write(std::string &filename) {
	ptree pt;

	pt.put("rod.<xmlattr>.name", this->name);

	ptree &pos = pt.add("rod.pos", "");
	ptree &origin = pos.add("o", "");
	origin.put("x", this->origin[0]);
	origin.put("y", this->origin[1]);
	origin.put("z", this->origin[2]);
	ptree &point1 = pos.add("p1", "");
	point1.put("x", this->point1[0]);
	point1.put("y", this->point1[1]);
	point1.put("z", this->point1[2]);
	ptree &point2 = pos.add("p2", "");
	point2.put("x", this->point2[0]);
	point2.put("y", this->point2[1]);
	point2.put("z", this->point2[2]);
	pos.put("slice", this->slice);

	ptree &rules = pt.add("rod.rules", "");
	std::map<QListWidgetItem*, vtkSmartPointer<vtkDistanceWidget> >::iterator itr;
	for (itr = this->rules.begin(); itr != this->rules.end(); ++itr) {
		ptree &rule = rules.add("rule", "");
		ptree &name = rule.add("name", itr->first->text().toUtf8().constData());
		ptree &p1 = rule.add("p1", "");
		p1.put("x", itr->second->GetDistanceRepresentation()->GetPoint1WorldPosition()[0]);
		p1.put("y", itr->second->GetDistanceRepresentation()->GetPoint1WorldPosition()[1]);
		p1.put("z", itr->second->GetDistanceRepresentation()->GetPoint1WorldPosition()[2]);
		ptree &p2 = rule.add("p2", "");
		p2.put("x", itr->second->GetDistanceRepresentation()->GetPoint2WorldPosition()[0]);
		p2.put("y", itr->second->GetDistanceRepresentation()->GetPoint2WorldPosition()[1]);
		p2.put("z", itr->second->GetDistanceRepresentation()->GetPoint2WorldPosition()[2]);
	}

	ptree &protractors = pt.add("rod.protractors", "");
	std::map<QListWidgetItem*, vtkSmartPointer<vtkAngleWidget> >::iterator itp;
	for (itp = this->protractors.begin(); itp != this->protractors.end(); ++itp) {
		double *point1 = new double[3], *point2 = new double[3], *center = new double[3];
		itp->second->GetAngleRepresentation()->GetPoint1WorldPosition(point1);
		itp->second->GetAngleRepresentation()->GetPoint2WorldPosition(point2);
		itp->second->GetAngleRepresentation()->GetCenterWorldPosition(center);

		ptree &protractor = protractors.add("protractor", "");
		ptree &name = protractor.add("name", itp->first->text().toUtf8().constData());
		ptree &p1 = protractor.add("p1", "");
		p1.put("x", point1[0]);
		p1.put("y", point1[1]);
		p1.put("z", point1[2]);
		ptree &p2 = protractor.add("p2", "");
		p2.put("x", point2[0]);
		p2.put("y", point2[1]);
		p2.put("z", point2[2]);
		ptree &c = protractor.add("c", "");
		c.put("x", center[0]);
		c.put("y", center[1]);
		c.put("z", center[2]);
	}

	ptree &annotations = pt.add("rod.annotations", "");
	std::map<QListWidgetItem*, vtkSmartPointer<vtkCaptionWidget> >::iterator ita;
	for (ita = this->annotations.begin(); ita != this->annotations.end(); ++ita) {
		double *point = ita->second->GetCaptionActor2D()->GetAttachmentPoint();
		ptree &annotation = annotations.add("annotation", "");
		ptree &name = annotation.add("name", ita->first->text().toUtf8().constData());
		ptree &text = annotation.add("text", ita->second->GetCaptionActor2D()->GetCaption());
		ptree &p = annotation.add("p", "");
		p.put("x", point[0]);
		p.put("y", point[1]);
		p.put("z", point[2]);
	}

	write_xml(filename, pt);
}

void ROD::read(std::string &filename, QListWidget* ruleList, QListWidget* protractorList, QListWidget *annotationList) {
	ptree pt;
	read_xml(filename, pt);

	this->name = pt.get<std::string>("rod.<xmlattr>.name");

	this->origin[0] = pt.get<double>("rod.pos.o.x");
	this->origin[1] = pt.get<double>("rod.pos.o.y");
	this->origin[2] = pt.get<double>("rod.pos.o.z");
	this->point1[0] = pt.get<double>("rod.pos.p1.x");
	this->point1[1] = pt.get<double>("rod.pos.p1.y");
	this->point1[2] = pt.get<double>("rod.pos.p1.z");
	this->point2[0] = pt.get<double>("rod.pos.p2.x");
	this->point2[1] = pt.get<double>("rod.pos.p2.y");
	this->point2[2] = pt.get<double>("rod.pos.p2.z");
	this->slice = pt.get<double>("rod.pos.slice");

	BOOST_FOREACH(ptree::value_type const &v, pt.get_child("rod.rules")) {
		if (v.first == "rule") {
			QListWidgetItem *item = new QListWidgetItem(0);
			item->setText(QString::fromStdString(v.second.get<std::string>("name")));
			ruleList->addItem(item);

			double *p1 = new double[3], *p2 = new double[3];
			p1[0] = v.second.get<double>("p1.x");
			p1[1] = v.second.get<double>("p1.y");
			p1[2] = v.second.get<double>("p1.z");
			p2[0] = v.second.get<double>("p2.x");
			p2[1] = v.second.get<double>("p2.y");
			p2[2] = v.second.get<double>("p2.z");

			rules[item] = vtkSmartPointer<vtkDistanceWidget>::New();
			rules[item]->SetInteractor(interactor);
			rules[item]->CreateDefaultRepresentation();
			rules[item]->GetDistanceRepresentation()->SetLabelFormat("%-#6.3g mm");
			rules[item]->GetDistanceRepresentation()->SetPoint1WorldPosition(p1);
			rules[item]->GetDistanceRepresentation()->SetPoint2WorldPosition(p2);
			rules[item]->SetWidgetStateToManipulate();
		}
	}

	BOOST_FOREACH(ptree::value_type const &v, pt.get_child("rod.protractors")) {
		if (v.first == "protractor") {
			QListWidgetItem *item = new QListWidgetItem(0);
			item->setText(QString::fromStdString(v.second.get<std::string>("name")));
			protractorList->addItem(item);

			double *p1 = new double[3], *p2 = new double[3], *c = new double[3];
			p1[0] = v.second.get<double>("p1.x");
			p1[1] = v.second.get<double>("p1.y");
			p1[2] = v.second.get<double>("p1.z");
			p2[0] = v.second.get<double>("p2.x");
			p2[1] = v.second.get<double>("p2.y");
			p2[2] = v.second.get<double>("p2.z");
			c[0] = v.second.get<double>("c.x");
			c[1] = v.second.get<double>("c.y");
			c[2] = v.second.get<double>("c.z");

			protractors[item] = vtkSmartPointer<vtkAngleWidget>::New();
			protractors[item]->SetInteractor(interactor);
			protractors[item]->CreateDefaultRepresentation();
			protractors[item]->GetAngleRepresentation()->GetPoint1Representation()->SetWorldPosition(p1);
			protractors[item]->GetAngleRepresentation()->GetPoint2Representation()->SetWorldPosition(p2);
			protractors[item]->GetAngleRepresentation()->GetCenterRepresentation()->SetWorldPosition(c);
			protractors[item]->SetWidgetStateToManipulate();
		}
	}

	BOOST_FOREACH(ptree::value_type const &v, pt.get_child("rod.annotations")) {
		if (v.first == "annotation") {
			QListWidgetItem *item = new QListWidgetItem(0);
			item->setText(QString::fromStdString(v.second.get<std::string>("name")));
			annotationList->addItem(item);

			double *pos = new double[3];
			pos[0] = v.second.get<double>("p.x");
			pos[1] = v.second.get<double>("p.y");
			pos[2] = v.second.get<double>("p.z");

			vtkSmartPointer<vtkCaptionRepresentation> captionRepresentation = vtkSmartPointer<vtkCaptionRepresentation>::New();
			captionRepresentation->GetCaptionActor2D()->SetCaption(v.second.get<std::string>("text").c_str());
			captionRepresentation->GetCaptionActor2D()->BorderOff();
			captionRepresentation->GetCaptionActor2D()->GetTextActor()->SetMinimumSize(300, 300);
			captionRepresentation->GetCaptionActor2D()->SetAttachmentPoint(pos);
			annotations[item] = vtkSmartPointer<vtkCaptionWidget>::New();
			annotations[item]->SetInteractor(interactor);
			annotations[item]->CreateDefaultRepresentation();
			annotations[item]->SetRepresentation(captionRepresentation);
		}
	}
}