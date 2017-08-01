#include "Sculpture.h"

Sculpture::Sculpture() {
	isoValue = WOOD_ISOVALUE; // default isovalue
	loaded = false; // no volume loaded

	tf = new TransferFunction();
	volumeProperty = vtkSmartPointer<vtkVolumeProperty>::New();
	volumeMapper = vtkSmartPointer<vtkSmartVolumeMapper>::New();
	imageData = vtkSmartPointer<vtkImageData>::New();
	meshActor = vtkSmartPointer<vtkActor>::New();
	volume = vtkSmartPointer<vtkVolume>::New();
	meshMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
	surface = vtkSmartPointer<vtkMarchingCubes>::New();

	setProperties();
	connectComponents();
}

Sculpture::~Sculpture() {

}

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

void Sculpture::setDICOMFolder(const std::string s) {
	loaded = false;

	vtkSmartPointer<vtkDICOMImageReader> imageReader = vtkSmartPointer<vtkDICOMImageReader>::New();
	imageReader->SetDirectoryName(s.c_str());
	imageReader->Update();

	imageData->DeepCopy(imageReader->GetOutput());

	volumeMapper->SetInputData(imageData);

	surface->SetInputData(imageData);
	meshMapper->Update();
	surface->SetValue(0, isoValue);

	loaded = true;
}

void Sculpture::createMesh() {
	surface->SetValue(0, isoValue);
}

void Sculpture::gaussianFilter(const unsigned int reps) {
	typedef signed short PixelType;
	const unsigned int Dimension = 3;

	typedef itk::Image<PixelType, Dimension> ImageType;

	typedef itk::VTKImageToImageFilter<ImageType> VTKImageToImageType;
	VTKImageToImageType::Pointer vtkImageToImage = VTKImageToImageType::New();
	vtkImageToImage->SetInput(imageData);
	vtkImageToImage->Update();

	typedef itk::BinomialBlurImageFilter<ImageType, ImageType> BinomialBlurFilterType;
	BinomialBlurFilterType::Pointer binomialBlurFilter = BinomialBlurFilterType::New();
	binomialBlurFilter->SetInput(vtkImageToImage->GetOutput());
	binomialBlurFilter->SetRepetitions(reps);
	binomialBlurFilter->Update();

	typedef itk::ImageToVTKImageFilter<ImageType> ImageToVTKImageType;
	ImageToVTKImageType::Pointer imageToVTKImage = ImageToVTKImageType::New();
	imageToVTKImage->SetInput(binomialBlurFilter->GetOutput());
	imageToVTKImage->Update();

	imageData->DeepCopy(imageToVTKImage->GetOutput());
	imageData->Modified();
}

void Sculpture::meanFilter(const unsigned int radius) {
	typedef signed short PixelType;
	const unsigned int Dimension = 3;

	typedef itk::Image<PixelType, Dimension> ImageType;

	typedef itk::VTKImageToImageFilter<ImageType> VTKImageToImageType;
	VTKImageToImageType::Pointer vtkImageToImage = VTKImageToImageType::New();
	vtkImageToImage->SetInput(imageData);
	vtkImageToImage->Update();

	typedef itk::MeanImageFilter<ImageType, ImageType> MeanImageFilterType;
	MeanImageFilterType::Pointer meanFilter = MeanImageFilterType::New();
	meanFilter->SetInput(vtkImageToImage->GetOutput());
	meanFilter->SetRadius(radius);
	meanFilter->Update();

	typedef itk::ImageToVTKImageFilter<ImageType> ImageToVTKImageType;
	ImageToVTKImageType::Pointer imageToVTKImage = ImageToVTKImageType::New();
	imageToVTKImage->SetInput(meanFilter->GetOutput());
	imageToVTKImage->Update();

	imageData->DeepCopy(imageToVTKImage->GetOutput());
	imageData->Modified();
}

void Sculpture::medianFilter(const unsigned int radius) {
	typedef signed short PixelType;
	const unsigned int Dimension = 3;

	typedef itk::Image<PixelType, Dimension> ImageType;

	typedef itk::VTKImageToImageFilter<ImageType> VTKImageToImageType;
	VTKImageToImageType::Pointer vtkImageToImage = VTKImageToImageType::New();
	vtkImageToImage->SetInput(imageData);
	vtkImageToImage->Update();

	typedef itk::MedianImageFilter<ImageType, ImageType> MedianImageFilterType;
	MedianImageFilterType::Pointer medianFilter = MedianImageFilterType::New();
	medianFilter->SetInput(vtkImageToImage->GetOutput());
	medianFilter->SetRadius(radius);
	medianFilter->Update();

	typedef itk::ImageToVTKImageFilter<ImageType> ImageToVTKImageType;
	ImageToVTKImageType::Pointer imageToVTKImage = ImageToVTKImageType::New();
	imageToVTKImage->SetInput(medianFilter->GetOutput());
	imageToVTKImage->Update();

	imageData->DeepCopy(imageToVTKImage->GetOutput());
	imageData->Modified();
}

void Sculpture::setMaterial(const double ambient, const double diffuse, const double specular, const double power) {
	volumeProperty->SetAmbient(ambient);
	volumeProperty->SetDiffuse(diffuse);
	volumeProperty->SetSpecular(specular); 
	volumeProperty->SetSpecularPower(power);
}

void Sculpture::setIsoValue(const double isoValue) {
	this->isoValue = isoValue;
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