#include "ROD.h"

ROD::ROD(std::string name, double* origin, double* point1, double* point2, double slice, const QFont &enabled, const QFont &disabled, vtkSmartPointer<vtkRenderWindowInteractor> interactor) :
    name(std::move(name)),
    origin(origin),
    point1(point1),
    point2(point2),
    slice(slice),
    enabled(enabled),
    disabled(disabled),
    interactor(std::move(interactor))
{}

ROD::ROD(const std::string &filename, const QFont &enabled, const QFont &disabled, vtkSmartPointer<vtkRenderWindowInteractor> interactor, QListWidget* ruleList, QListWidget* protractorList, QListWidget *annotationList) :
    enabled(enabled),
    disabled(disabled),
    interactor(std::move(interactor)),
    slice(0),
    origin(new double[3]),
    point1(new double[3]),
    point2(new double[3])
{
    read(filename, ruleList, protractorList, annotationList);
}

ROD::~ROD() {
    delete[] origin;
    delete[] point1;
    delete[] point2;
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

void ROD::addRule(QListWidgetItem* item) {
    rules[item] = vtkSmartPointer<vtkDistanceWidget>::New();
    rules[item]->SetInteractor(interactor);
    rules[item]->CreateDefaultRepresentation();
    rules[item]->GetDistanceRepresentation()->SetLabelFormat(DISTANCE_FORMAT.c_str());
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
    protractors[item]->GetAngleRepresentation()->SetLabelFormat(ANGLE_FORMAT.c_str());
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

void ROD::addAnnotation(QListWidgetItem* item, const std::string &text) {
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

bool ROD::samePlane(const double* o, const double* p1, const double* p2, double s) {
    return (
        this->origin[0] == o[0] &&
        this->origin[1] == o[1] &&
        this->origin[2] == o[2] &&
        this->point1[0] == p1[0] &&
        this->point1[1] == p1[1] &&
        this->point1[2] == p1[2] &&
        this->point2[0] == p2[0] &&
        this->point2[1] == p2[1] &&
        this->point2[2] == p2[2] &&
        this->slice == s
    );
}

void ROD::write(const std::string &filename) {
    ptree pt;

    pt.put("rod.<xmlattr>.name", this->name);

    ptree &ptPos = pt.add("rod.pos", "");
    ptree &ptOrigin = ptPos.add("o", "");
    ptOrigin.put("x", this->origin[0]);
    ptOrigin.put("y", this->origin[1]);
    ptOrigin.put("z", this->origin[2]);
    ptree &ptPoint1 = ptPos.add("p1", "");
    ptPoint1.put("x", this->point1[0]);
    ptPoint1.put("y", this->point1[1]);
    ptPoint1.put("z", this->point1[2]);
    ptree &ptPoint2 = ptPos.add("p2", "");
    ptPoint2.put("x", this->point2[0]);
    ptPoint2.put("y", this->point2[1]);
    ptPoint2.put("z", this->point2[2]);
    ptPos.put("slice", this->slice);

    ptree &ptRules = pt.add("rod.rules", "");
    std::map<QListWidgetItem*, vtkSmartPointer<vtkDistanceWidget> >::iterator itr;
    for (itr = this->rules.begin(); itr != this->rules.end(); ++itr) {
        ptree &ptRule = ptRules.add("rule", "");
        ptree &ptName = ptRule.add("name", itr->first->text().toUtf8().constData());
        ptree &ptP1 = ptRule.add("p1", "");
        ptP1.put("x", itr->second->GetDistanceRepresentation()->GetPoint1WorldPosition()[0]);
        ptP1.put("y", itr->second->GetDistanceRepresentation()->GetPoint1WorldPosition()[1]);
        ptP1.put("z", itr->second->GetDistanceRepresentation()->GetPoint1WorldPosition()[2]);
        ptree &ptP2 = ptRule.add("p2", "");
        ptP2.put("x", itr->second->GetDistanceRepresentation()->GetPoint2WorldPosition()[0]);
        ptP2.put("y", itr->second->GetDistanceRepresentation()->GetPoint2WorldPosition()[1]);
        ptP2.put("z", itr->second->GetDistanceRepresentation()->GetPoint2WorldPosition()[2]);
    }

    ptree &ptProtractors = pt.add("rod.protractors", "");
    std::map<QListWidgetItem*, vtkSmartPointer<vtkAngleWidget> >::iterator itp;
    for (itp = this->protractors.begin(); itp != this->protractors.end(); ++itp) {
        auto *p1 = new double[3], *p2 = new double[3], *c = new double[3];
        itp->second->GetAngleRepresentation()->GetPoint1WorldPosition(p1);
        itp->second->GetAngleRepresentation()->GetPoint2WorldPosition(p2);
        itp->second->GetAngleRepresentation()->GetCenterWorldPosition(c);

        ptree &ptProtractor = ptProtractors.add("protractor", "");
        ptree &ptName = ptProtractor.add("name", itp->first->text().toUtf8().constData());
        ptree &ptP1 = ptProtractor.add("p1", "");
        ptP1.put("x", p1[0]);
        ptP1.put("y", p1[1]);
        ptP1.put("z", p1[2]);
        ptree &ptP2 = ptProtractor.add("p2", "");
        ptP2.put("x", p2[0]);
        ptP2.put("y", p2[1]);
        ptP2.put("z", p2[2]);
        ptree &ptC = ptProtractor.add("c", "");
        ptC.put("x", c[0]);
        ptC.put("y", c[1]);
        ptC.put("z", c[2]);
    }

    ptree &ptAnnotations = pt.add("rod.annotations", "");
    std::map<QListWidgetItem*, vtkSmartPointer<vtkCaptionWidget> >::iterator ita;
    for (ita = this->annotations.begin(); ita != this->annotations.end(); ++ita) {
        double *p = ita->second->GetCaptionActor2D()->GetAttachmentPoint();
        ptree &ptAnnotation = ptAnnotations.add("annotation", "");
        ptree &ptName = ptAnnotation.add("name", ita->first->text().toUtf8().constData());
        ptree &ptText = ptAnnotation.add("text", ita->second->GetCaptionActor2D()->GetCaption());
        ptree &ptP = ptAnnotation.add("p", "");
        ptP.put("x", p[0]);
        ptP.put("y", p[1]);
        ptP.put("z", p[2]);
    }

    write_xml(filename, pt);
}

void ROD::read(const std::string &filename, QListWidget* ruleList, QListWidget* protractorList, QListWidget *annotationList) {
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
            auto *item = new QListWidgetItem();
            item->setText(QString::fromStdString(v.second.get<std::string>("name")));
            ruleList->addItem(item);

            auto *p1 = new double[3], *p2 = new double[3];
            p1[0] = v.second.get<double>("p1.x");
            p1[1] = v.second.get<double>("p1.y");
            p1[2] = v.second.get<double>("p1.z");
            p2[0] = v.second.get<double>("p2.x");
            p2[1] = v.second.get<double>("p2.y");
            p2[2] = v.second.get<double>("p2.z");

            rules[item] = vtkSmartPointer<vtkDistanceWidget>::New();
            rules[item]->SetInteractor(interactor);
            rules[item]->CreateDefaultRepresentation();
            rules[item]->GetDistanceRepresentation()->SetLabelFormat(DISTANCE_FORMAT.c_str());
            rules[item]->GetDistanceRepresentation()->SetPoint1WorldPosition(p1);
            rules[item]->GetDistanceRepresentation()->SetPoint2WorldPosition(p2);
            rules[item]->SetWidgetStateToManipulate();
        }
    }

    BOOST_FOREACH(ptree::value_type const &v, pt.get_child("rod.protractors")) {
        if (v.first == "protractor") {
            auto *item = new QListWidgetItem();
            item->setText(QString::fromStdString(v.second.get<std::string>("name")));
            protractorList->addItem(item);

            auto *p1 = new double[3], *p2 = new double[3], *c = new double[3];
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
            protractors[item]->GetAngleRepresentation()->SetLabelFormat(ANGLE_FORMAT.c_str());
            protractors[item]->SetWidgetStateToManipulate();
        }
    }

    BOOST_FOREACH(ptree::value_type const &v, pt.get_child("rod.annotations")) {
        if (v.first == "annotation") {
            auto *item = new QListWidgetItem();
            item->setText(QString::fromStdString(v.second.get<std::string>("name")));
            annotationList->addItem(item);

            auto *pos = new double[3];
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
