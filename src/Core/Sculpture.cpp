#include "Sculpture.h"

Sculpture::Sculpture() :
	isoValue(WOOD_ISOVALUE),
	loaded(false),
	tf(new TransferFunction()),
	volumeProperty(vtkSmartPointer<vtkVolumeProperty>::New()),
	volumeMapper(vtkSmartPointer<vtkSmartVolumeMapper>::New()),
	imageData(vtkSmartPointer<vtkImageData>::New()),
	meshActor(vtkSmartPointer<vtkActor>::New()),
	volume(vtkSmartPointer<vtkVolume>::New()),
	meshMapper(vtkSmartPointer<vtkPolyDataMapper>::New()),
	surface(vtkSmartPointer<vtkMarchingCubes>::New())
{
	setProperties();
	connectComponents();
}

Sculpture::~Sculpture() = default;

void Sculpture::connectComponents() {
	volume->SetMapper(volumeMapper);
	volume->SetProperty(volumeProperty);

	meshMapper->SetInputConnection(surface->GetOutputPort()); 
	meshActor->SetMapper(meshMapper);
}

void Sculpture::setProperties() {
	volumeProperty->SetInterpolationTypeToLinear();
	volumeProperty->SetGradientOpacity(tf->getGradientFun());
	volumeProperty->SetScalarOpacity(tf->getScalarFun());
	volumeProperty->SetColor(tf->getColorFun());
	volumeProperty->ShadeOn();

	surface->ComputeScalarsOn();
	surface->ComputeGradientsOn();
	surface->ComputeNormalsOn();
	meshMapper->ScalarVisibilityOff();
}

void Sculpture::setDICOMFolder(const std::string &s) {
	loaded = false;

	vtkSmartPointer<vtkDICOMImageReader> imageReader = vtkSmartPointer<vtkDICOMImageReader>::New();
	imageReader->SetDirectoryName(s.c_str());
    imageReader->Update();

    imageData->DeepCopy(imageReader->GetOutput());
    loadVolume(imageReader);

	loaded = true;
}

void Sculpture::setVTIFile(const std::string &s) {
	loaded = false;

	vtkSmartPointer<vtkXMLImageDataReader> imageReader = vtkSmartPointer<vtkXMLImageDataReader>::New();
	imageReader->SetFileName(s.c_str());
    imageReader->Update();

    imageData->DeepCopy(imageReader->GetOutput());
    loadVolume(imageReader);

	loaded = true;
}

void Sculpture::loadVolume(const vtkSmartPointer<vtkAlgorithm> &imageReader) {
    volumeMapper->SetInputData(imageData);
    surface->SetInputData(imageData);
    meshMapper->Update();
    surface->SetValue(0, isoValue);
}

void Sculpture::createMesh() {
	surface->SetValue(0, isoValue);
}

void Sculpture::gaussianFilter(unsigned int reps) {
	BinomialBlurFilterType::Pointer binomialBlurFilter = BinomialBlurFilterType::New();
	binomialBlurFilter->SetInput(getITKImage()->GetOutput());
	binomialBlurFilter->SetRepetitions(reps);
	binomialBlurFilter->Update();

	itkToVTK(binomialBlurFilter->GetOutput());
}

void Sculpture::meanFilter(unsigned int radius) {
	MeanImageFilterType::Pointer meanFilter = MeanImageFilterType::New();
	meanFilter->SetInput(getITKImage()->GetOutput());
	meanFilter->SetRadius(radius);
	meanFilter->Update();

	itkToVTK(meanFilter->GetOutput());
}

void Sculpture::medianFilter(unsigned int radius) {
	MedianImageFilterType::Pointer medianFilter = MedianImageFilterType::New();
	medianFilter->SetInput(getITKImage()->GetOutput());
	medianFilter->SetRadius(radius);
	medianFilter->Update();

	itkToVTK(medianFilter->GetOutput());
}

VTKImageToImageType::Pointer Sculpture::getITKImage() {
    VTKImageToImageType::Pointer vtkImageToImage = VTKImageToImageType::New();
    vtkImageToImage->SetInput(imageData);
    vtkImageToImage->Update();

    return vtkImageToImage;
}

void Sculpture::itkToVTK(const ImageType::Pointer &filter) {
    ImageToVTKImageType::Pointer imageToVTKImage = ImageToVTKImageType::New();
    imageToVTKImage->SetInput(filter);
    imageToVTKImage->Update();

    imageData->DeepCopy(imageToVTKImage->GetOutput());
    imageData->Modified();
}

void Sculpture::setMaterial(double ambient, double diffuse, double specular, double power) {
	volumeProperty->SetAmbient(ambient);
	volumeProperty->SetDiffuse(diffuse);
	volumeProperty->SetSpecular(specular); 
	volumeProperty->SetSpecularPower(power);
}

void Sculpture::setIsoValue(double v) {
	this->isoValue = v;
}


TransferFunction * Sculpture::getTransferFunction() const {
	return tf;
}

vtkSmartPointer<vtkVolume> Sculpture::getVolume() const {
	return volume;
}

vtkSmartPointer<vtkImageData> Sculpture::getImageData() const {
	return imageData;
}

vtkSmartPointer<vtkActor> Sculpture::getMesh() const {
	return meshActor;
}

double Sculpture::getIsoValue() const {
	return isoValue;
}

bool Sculpture::getLoaded() const {
	return loaded;
}

double Sculpture::getMinXBound() const {
	return volume->GetMinXBound();
}

double Sculpture::getMinYBound() const {
	return volume->GetMinYBound();
}

double Sculpture::getMinZBound() const {
	return volume->GetMinZBound();
}

double Sculpture::getMaxXBound() const {
	return volume->GetMaxXBound();
}

double Sculpture::getMaxYBound() const {
	return volume->GetMaxYBound();
}

double Sculpture::getMaxZBound() const {
	return volume->GetMaxZBound();
}
