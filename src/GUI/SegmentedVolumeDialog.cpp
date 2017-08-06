#include "SegmentedVolumeDialog.h"
#include "ui_segmentedvolumedialog.h"

SegmentedVolumeDialog::SegmentedVolumeDialog(QWidget *parent) : QDialog(parent), ui(new Ui::SegmentedVolumeDialog) {
	ui->setupUi(this);

	cout << "constructor" << endl;

	// Connect button actions
	QObject::connect(ui->okButton, SIGNAL(clicked()), this, SLOT(accept()));
	QObject::connect(ui->cancelButton, SIGNAL(clicked()), this, SLOT(reject()));
}

SegmentedVolumeDialog::~SegmentedVolumeDialog() {
	delete ui;
}

void SegmentedVolumeDialog::setImageData(vtkSmartPointer<vtkImageData> imageData) {

	cout << "imageData" << endl;
	this->imageData = imageData;
}

void SegmentedVolumeDialog::setTransferFunction(TransferFunction* tf) {

	cout << "tf" << endl;
	this->tf = tf;
}

void SegmentedVolumeDialog::render() {

	cout << "render start" << endl;
	vtkSmartPointer<vtkRenderWindow> renderWindow = ui->viewer->GetRenderWindow();
	vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
	vtkSmartPointer<vtkInteractorStyleTrackballCamera> interactorStyle = vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New(); 
	vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
	vtkSmartPointer<vtkSmartVolumeMapper> volumeMapper = vtkSmartPointer<vtkSmartVolumeMapper>::New();
	vtkSmartPointer<vtkVolumeProperty> volumeProperty = vtkSmartPointer<vtkVolumeProperty>::New();
	vtkSmartPointer<vtkVolume> volume = vtkSmartPointer<vtkVolume>::New();

	renderer->SetBackground(0.1, 0.2, 0.3);
	renderWindow->AddRenderer(renderer);
	renderWindowInteractor->SetInteractorStyle(interactorStyle);
	renderWindowInteractor->SetRenderWindow(renderWindow); 
	
	volumeMapper->SetBlendModeToComposite();
	volumeMapper->SetRequestedRenderModeToGPU();
	volumeMapper->SetInputData(imageData);

	volumeProperty->ShadeOn();
	volumeProperty->SetInterpolationTypeToLinear();

	volumeProperty->SetAmbient(0.1);
	volumeProperty->SetDiffuse(0.9);
	volumeProperty->SetSpecular(0.2);
	volumeProperty->SetSpecularPower(10.0);
	volumeProperty->SetGradientOpacity(tf->getGradientFun());
	volumeProperty->SetScalarOpacity(tf->getScalarFun());
	volumeProperty->SetColor(tf->getColorFun());

	volume->SetMapper(volumeMapper);
	volume->SetProperty(volumeProperty);
	renderer->AddVolume(volume);
	renderer->ResetCamera();

	renderWindow->Render();
	renderWindowInteractor->Start();

	cout << "render end" << endl;
}

void SegmentedVolumeDialog::accept() {
	// TODO
}

void SegmentedVolumeDialog::reject() {
	// TODO
}