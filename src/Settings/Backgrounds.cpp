#include "Backgrounds.h"

Backgrounds::Backgrounds(QColor meshBackground, QColor volumeBackground, QColor volumeDeletingBackground, QColor volumeSegmentingBackground) :
    meshBackground(std::move(meshBackground)),
    volumeBackground(std::move(volumeBackground)),
    volumeDeletingBackground(std::move(volumeDeletingBackground)),
    volumeSegmentingBackground(std::move(volumeSegmentingBackground)),
    deleting(nullptr),
    meshRenderer(nullptr),
    volumeRenderer(nullptr),
    meshRenderWindow(nullptr),
    volumeRenderWindow(nullptr)
{ }

Backgrounds::~Backgrounds() = default;

void Backgrounds::setDeleting(bool *d) {
    this->deleting = d;
}

void Backgrounds::setMeshRenderer(const vtkSmartPointer<vtkRenderer> &r) {
    this->meshRenderer = r;
}

void Backgrounds::setVolumeRenderer(const vtkSmartPointer<vtkRenderer> &r) {
    this->volumeRenderer = r;
}

void Backgrounds::setMeshRenderWindow(const vtkSmartPointer<vtkRenderWindow> &rw) {
    this->meshRenderWindow = rw;
}

void Backgrounds::setVolumeRenderWindow(const vtkSmartPointer<vtkRenderWindow> &rw) {
    this->volumeRenderWindow = rw;
}

void Backgrounds::setVolumeBackground(const QColor &b) {
    this->volumeBackground = b;
    if (!*deleting) {
        volumeRenderer->SetBackground(b.redF(), b.greenF(), b.blueF());
        volumeRenderWindow->Render();
    }
}

void Backgrounds::setVolumeDeletingBackground(const QColor &b) {
    this->volumeDeletingBackground = b;
    if (*deleting) {
        volumeRenderer->SetBackground(b.redF(), b.greenF(), b.blueF());
        volumeRenderWindow->Render();
    }
}

void Backgrounds::setVolumeSegmentingBackground(const QColor &b) {
    this->volumeSegmentingBackground = b;
}

void Backgrounds::setMeshBackground(const QColor &b) {
    this->meshBackground = b;
    meshRenderer->SetBackground(b.redF(), b.greenF(), b.blueF());
    meshRenderWindow->Render();
}

QColor Backgrounds::getVolumeBackground() const {
    return volumeBackground;
}

QColor Backgrounds::getVolumeDeletingBackground() const {
    return volumeDeletingBackground;
}

QColor Backgrounds::getVolumeSegmentingBackground() const {
    return volumeSegmentingBackground;
}

QColor Backgrounds::getMeshBackground() const {
    return meshBackground;
}
