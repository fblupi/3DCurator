#include "InteractorStyleDeleter.h"

vtkStandardNewMacro(InteractorStyleDeleter);

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
			// -- launch progress bar
			QPointer<QProgressBar> bar = new QProgressBar(0);
			QPointer<QProgressDialog> progressDialog = new QProgressDialog(0);
			progressDialog->setWindowTitle(QString("Borrando..."));
			progressDialog->setLabelText(QString::fromLatin1("Extrayendo la malla del objeto"));
			progressDialog->setWindowIcon(QIcon(":/icons/3DCurator.png"));
			progressDialog->setWindowFlags(progressDialog->windowFlags() & ~Qt::WindowCloseButtonHint);
			progressDialog->setCancelButton(0);
			progressDialog->setBar(bar);
			progressDialog->show();
			bar->close();
			QApplication::processEvents();
			// -- END launch progress bar

			vtkSmartPointer<vtkImageData> oldData = vtkSmartPointer<vtkImageData>::New();
			oldData->DeepCopy(sculpture->getImageData());

			int* dimensions = sculpture->getImageData()->GetDimensions();
			Bounds bounds;
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

			// -- close progress bar
			progressDialog->close(); 
			// -- END close progress bar

			// -- launch confirm box
			QPointer<QMessageBox> confirmBox = new QMessageBox(0);
			confirmBox->setWindowTitle(QString::fromLatin1("Confirmar"));
			confirmBox->setWindowIcon(QIcon(":/icons/3DCurator.png"));
			confirmBox->setIcon(QMessageBox::Question);
			confirmBox->setText(QString::fromLatin1("¿Actualizar cambios?"));
			confirmBox->setStandardButtons(QMessageBox::Yes | QMessageBox::No);
			confirmBox->button(QMessageBox::Yes)->setText(QString::fromLatin1("Sí"));
			confirmBox->button(QMessageBox::No)->setText(QString::fromLatin1("No"));

			if (confirmBox->exec() == QMessageBox::No) {
				// -- launch progress bar
				progressDialog->setWindowTitle(QString("Restaurando..."));
				progressDialog->setLabelText(QString::fromLatin1("Deshaciendo borrado"));
				progressDialog->show();
				QApplication::processEvents();
				// -- END launch progress bar

				sculpture->getImageData()->DeepCopy(oldData); 

				sculpture->getImageData()->Modified(); 
				slicePlane->getPlane()->UpdatePlacement(); 
				viewer->Render(); 

				// -- close progress bar
				progressDialog->close();
				// -- END close progress bar
			}
			// -- END launch confirm box
		}
	}
}

void InteractorStyleDeleter::SetViewer(vtkSmartPointer<vtkImageViewer2> viewer) {
	this->viewer = viewer;
}

void InteractorStyleDeleter::SetDefaultRenderWindow(vtkSmartPointer<vtkRenderWindow> renWin) {
	this->renWin = renWin;
}

void InteractorStyleDeleter::SetSculpture(Sculpture* sculpture) {
	this->sculpture = sculpture;
}

void InteractorStyleDeleter::SetSlicePlane(SlicePlane* slicePlane) {
	this->slicePlane = slicePlane;
}