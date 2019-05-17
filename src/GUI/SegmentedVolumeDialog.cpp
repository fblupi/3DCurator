#include "SegmentedVolumeDialog.h"
#include "ui_segmentedvolumedialog.h"

SegmentedVolumeDialog::SegmentedVolumeDialog(vtkSmartPointer<vtkImageData> imageData, TransferFunction *tf, QColor background, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SegmentedVolumeDialog),
    imageData(std::move(imageData)),
    background(std::move(background)),
    tf(tf)
{
    ui->setupUi(this);

    // Connect button actions
    QObject::connect(ui->okButton, SIGNAL(clicked()), this, SLOT(accept()));
    QObject::connect(ui->cancelButton, SIGNAL(clicked()), this, SLOT(reject()));
}

SegmentedVolumeDialog::~SegmentedVolumeDialog() {
    delete ui;
}

void SegmentedVolumeDialog::render() {
    vtkSmartPointer<vtkSmartVolumeMapper> volumeMapper = vtkSmartPointer<vtkSmartVolumeMapper>::New();
    vtkSmartPointer<vtkVolumeProperty> volumeProperty = vtkSmartPointer<vtkVolumeProperty>::New();
    vtkSmartPointer<vtkVolume> volume = vtkSmartPointer<vtkVolume>::New();
    vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
    vtkSmartPointer<vtkInteractorStyleTrackballCamera> interactorStyle = vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New();

    renderer->SetBackground(background.redF(), background.greenF(), background.blueF());
    ui->viewer->GetRenderWindow()->AddRenderer(renderer);
    ui->viewer->GetRenderWindow()->GetInteractor()->SetInteractorStyle(interactorStyle);

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

    ui->viewer->GetRenderWindow()->Render();
}

void SegmentedVolumeDialog::accept() {
    done(QMessageBox::Yes);
}

void SegmentedVolumeDialog::reject() {
    done(QMessageBox::No);
}
