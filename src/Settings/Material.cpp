#include "Material.h"

Material::Material(const double &ambient, const double &diffuse, const double &specular, const double &power) :
    ambient(ambient),
    diffuse(diffuse),
    specular(specular),
    power(power),
    sculpture(nullptr),
    volumeRenderWindow(nullptr)
{ }

Material::~Material() = default;

void Material::setSculpture(Sculpture* s) {
    this->sculpture = s;
}

void Material::setVolumeRenderWindow(const vtkSmartPointer<vtkRenderWindow> &rw) {
    this->volumeRenderWindow = rw;
}

void Material::setAmbient(const double &a) {
    this->ambient = a;
    update();
}

void Material::setDiffuse(const double &d) {
    this->diffuse = d;
    update();
}

void Material::setSpecular(const double &s) {
    this->specular = s;
    update();
}

void Material::setPower(const double &p) {
    this->power = p;
    update();
}

double Material::getAmbient() const {
    return ambient;
}

double Material::getDiffuse() const {
    return diffuse;
}

double Material::getSpecular() const {
    return specular;
}

double Material::getPower() const {
    return power;
}

void Material::update() {
    sculpture->setMaterial(ambient, diffuse, specular, power);
    volumeRenderWindow->Render();
}
