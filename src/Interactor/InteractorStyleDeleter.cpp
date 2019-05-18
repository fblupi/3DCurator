#include "InteractorStyleDeleter.h"

vtkStandardNewMacro(InteractorStyleDeleter)

void InteractorStyleDeleter::OnLeftButtonDown() {
    vtkSmartPointer<vtkVolumePicker> picker = vtkSmartPointer<vtkVolumePicker>::New();
    picker->SetUseVolumeGradientOpacity(true);
    picker->SetVolumeOpacityIsovalue(0.1);

    int* pos = this->GetInteractor()->GetEventPosition();
    picker->Pick(pos[0], pos[1], pos[2], this->GetDefaultRenderer());

    int* ijk = picker->GetPointIJK();

    if (picker->GetPointId() != -1) {
        double value = sculpture->getImageData()->GetScalarComponentAsDouble(ijk[0], ijk[1], ijk[2], 0);
        if (value > AIR_HU) {
            auto *progressDialog = new ProgressDialog(QCoreApplication::translate("InteractorStyleDeleter", "DELETING"), QCoreApplication::translate("InteractorStyleDeleter", "DELETING_SELECTED_PART_OF_THE_VOLUME"));
            progressDialog->show();

            vtkSmartPointer<vtkImageData> oldData = vtkSmartPointer<vtkImageData>::New();
            oldData->DeepCopy(sculpture->getImageData());

            int* dimensions = sculpture->getImageData()->GetDimensions();
            Bounds bounds = {};
            bounds.MIN_X = 0;
            bounds.MAX_X = dimensions[0];
            bounds.MIN_Y = 0;
            bounds.MAX_Y = dimensions[1];
            bounds.MIN_Z = 0;
            bounds.MAX_Z = dimensions[2];
            deleteByImages(sculpture->getImageData(), ijk, bounds);

            sculpture->getImageData()->Modified();
            slicePlane->getPlane()->UpdatePlacement();
            viewer->Render();

            progressDialog->close();

            // -- launch confirm box
            QPointer<QMessageBox> confirmBox = new QMessageBox();
            confirmBox->setWindowTitle(QCoreApplication::translate("InteractorStyleDeleter", "CONFIRM_DELETION"));
            confirmBox->setWindowIcon(QIcon(":/icons/3DCurator.png"));
            confirmBox->setIcon(QMessageBox::Question);
            confirmBox->setText(QCoreApplication::translate("InteractorStyleDeleter", "UPDATE_DELETION_CHANGES?"));
            confirmBox->setStandardButtons(QMessageBox::Yes | QMessageBox::No);
            confirmBox->button(QMessageBox::Yes)->setText(QCoreApplication::translate("InteractorStyleDeleter", "CONFIRM_DELETION_YES"));
            confirmBox->button(QMessageBox::No)->setText(QCoreApplication::translate("InteractorStyleDeleter", "CONFIRM_DELETION_NO"));

            if (confirmBox->exec() == QMessageBox::No) {
                progressDialog = new ProgressDialog(QCoreApplication::translate("InteractorStyleDeleter", "DELETION_RESTORING"), QCoreApplication::translate("InteractorStyleDeleter", "UNDOING_DELETION"));
                progressDialog->show();

                sculpture->getImageData()->DeepCopy(oldData);

                sculpture->getImageData()->Modified();
                slicePlane->getPlane()->UpdatePlacement();
                viewer->Render();

                progressDialog->close();
            }
            // -- END launch confirm box
        }
    }
}

void InteractorStyleDeleter::SetViewer(const vtkSmartPointer<vtkImageViewer2> &v) {
    this->viewer = v;
}

void InteractorStyleDeleter::SetSculpture(Sculpture* s) {
    this->sculpture = s;
}

void InteractorStyleDeleter::SetSlicePlane(SlicePlane* p) {
    this->slicePlane = p;
}
