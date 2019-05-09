#include "TransferFunction.h"

TransferFunction::TransferFunction() :
    colorFun(vtkSmartPointer<vtkColorTransferFunction>::New()),
    scalarFun(vtkSmartPointer<vtkPiecewiseFunction>::New()),
    gradientFun(vtkSmartPointer<vtkPiecewiseFunction>::New()),
    name("tf"),
    description("")
{}

TransferFunction::~TransferFunction() = default;

void TransferFunction::readData(ptree pt) {
    name = pt.get<std::string>("tf.<xmlattr>.name");
    description = pt.get<std::string>("tf.<xmlattr>.description");

    BOOST_FOREACH(ptree::value_type const &v, pt.get_child("tf.color")) {
        if (v.first == "point") {
            colorFun->AddRGBPoint(v.second.get<double>("x"), v.second.get<double>("r"), v.second.get<double>("g"), v.second.get<double>("b"));
        }
    }

    BOOST_FOREACH(ptree::value_type const &v, pt.get_child("tf.scalar")) {
        if (v.first == "point") {
            scalarFun->AddPoint(v.second.get<double>("x"), v.second.get<double>("y"));
        }
    }

    BOOST_FOREACH(ptree::value_type const &v, pt.get_child("tf.gradient")) {
        if (v.first == "point") {
            gradientFun->AddPoint(v.second.get<double>("x"), v.second.get<double>("y"));
        }
    }
}

void TransferFunction::read(std::string &filename) {
    clear();

    ptree pt;
    read_xml(filename, pt);

    readData(pt);
}


void TransferFunction::read(std::istream &file) {
    clear();

    ptree pt;
    read_xml(file, pt);

    readData(pt);
}

void TransferFunction::write(std::string &filename) {
    ptree pt;

    double *colorFunData = colorFun->GetDataPointer();
    double *scalarFunData = scalarFun->GetDataPointer();
    double *gradientFunData = gradientFun->GetDataPointer();

    pt.put("tf.<xmlattr>.name", name);
    pt.put("tf.<xmlattr>.description", description);

    ptree &color = pt.add("tf.color", "");
    for (int i = 0; i < colorFun->GetSize(); i++) {
        ptree &node = color.add("point", "");
        node.put("x", colorFunData[i * 4]);
        node.put("r", colorFunData[i * 4 + 1]);
        node.put("g", colorFunData[i * 4 + 2]);
        node.put("b", colorFunData[i * 4 + 3]);
    }

    ptree &scalar = pt.add("tf.scalar", "");
    for (int i = 0; i < scalarFun->GetSize(); i++) {
        ptree &node = scalar.add("point", "");
        node.put("x", scalarFunData[i * 2]);
        node.put("y", scalarFunData[i * 2 + 1]);
    }

    ptree &gradient = pt.add("tf.gradient", "");
    for (int i = 0; i < gradientFun->GetSize(); i++) {
        ptree &node = scalar.add("point", "");
        node.put("x", gradientFunData[i * 2]);
        node.put("y", gradientFunData[i * 2 + 1]);
    }

    write_xml(filename, pt);
}
void TransferFunction::clear() {
    colorFun->RemoveAllPoints();
    scalarFun->RemoveAllPoints();
    gradientFun->RemoveAllPoints();
}

void TransferFunction::setName(const std::string &n) {
    this->name = n;
}

void TransferFunction::setDescription(const std::string &d) {
    this->description = d;
}

std::string TransferFunction::getName() const {
    return name;
}

std::string TransferFunction::getDescription() const {
    return description;
}

vtkSmartPointer<vtkColorTransferFunction> TransferFunction::getColorFun() const {
    return colorFun;
}

vtkSmartPointer<vtkPiecewiseFunction> TransferFunction::getScalarFun() const {
    return scalarFun;
}

vtkSmartPointer<vtkPiecewiseFunction> TransferFunction::getGradientFun() const {
    return gradientFun;
}
