#include "InteractorStyleSegmentation.h"

vtkStandardNewMacro(InteractorStyleSegmentation);

void InteractorStyleSegmentation::OnLeftButtonDown() {
	if (slicePlane != NULL && this->GetDefaultRenderer() != NULL) {
		vtkSmartPointer<vtkVolumePicker> picker = vtkSmartPointer<vtkVolumePicker>::New();
		int* pos = this->GetInteractor()->GetEventPosition();
		picker->Pick(pos[0], pos[1], pos[2], this->GetDefaultRenderer());

		int* ijk = picker->GetPointIJK();
		
		if (picker->GetPointId() != -1) {
			ijk[2] = slicePlane->getPlane()->GetCenter()[2] / sculpture->getImageData()->GetSpacing()[2];
			int * dimensions = sculpture->getImageData()->GetDimensions();
			Bounds bounds;
			bounds.MIN_X = 0;
			bounds.MAX_X = dimensions[0];
			bounds.MIN_Y = 0;
			bounds.MAX_Y = dimensions[1];
			bounds.MIN_Z = 0;
			bounds.MAX_Z = dimensions[2];

			std::vector<std::vector<Line> > lines(bounds.MAX_Z);

			lines[ijk[2]] = getLinesFromImage(sculpture->getImageData(), sculpture->getTransferFunction()->getColorFun(), ijk[2], bounds);

			std::string img = generateImage(sculpture->getImageData(), sculpture->getTransferFunction()->getColorFun(), ijk[2], bounds, lines[ijk[2]]);

			// -- launch line selection
			LineSelectionDialog *diag = new LineSelectionDialog();
			diag->setImage(img);
			// -- END launch line selection

			remove(img.c_str());

			// -- exec line selection
			int response = diag->exec();
			// -- END exec line selection

			if (response != LINE_CANCEL) {
				Line selectedLine;
				switch (response) {
					case LINE_RED:
						selectedLine = lines[ijk[2]][0];
						break;
					case LINE_GREEN:
						selectedLine = lines[ijk[2]][1];
						break;
					case LINE_BLUE:
						selectedLine = lines[ijk[2]][2];
						break;
					case LINE_CYAN:
						selectedLine = lines[ijk[2]][3];
						break;
					case LINE_MAGENTA:
						selectedLine = lines[ijk[2]][4];
						break;
					case LINE_YELLOW:
						selectedLine = lines[ijk[2]][5];
						break;
				}

				// -- launch progress bar
				QPointer<QProgressBar> bar = new QProgressBar(0);
				QPointer<QProgressDialog> progressDialog = new QProgressDialog(0);
				progressDialog->setWindowTitle(QString("Segmentando..."));
				progressDialog->setLabelText(QString::fromLatin1("Segmentando la pieza de madera seleccionada"));
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

				vtkSmartPointer<vtkImageData> segmentedData = vtkSmartPointer<vtkImageData>::New();
				segmentedData->DeepCopy(sculpture->getImageData());

				for (int i = 0; i < dimensions[0]; i++) {
					for (int j = 0; j < dimensions[1]; j++) {
						for (int k = 0; k < dimensions[2]; k++) {
							segmentedData->SetScalarComponentFromFloat(i, j, k, 0, AIR_HU);
						}
					}
				}

				regionGrowingWithLineBoundVolume(sculpture->getImageData(), segmentedData, sculpture->getTransferFunction()->getColorFun(), ijk, bounds, selectedLine, lines, diag->getCompleteUp(), diag->getCompleteDown());

				sculpture->getImageData()->DeepCopy(oldData);

				// -- close progress bar
				progressDialog->close();
				// -- END close progress bar

				SegmentedVolumeDialog *segmentedVolumeDialog = new SegmentedVolumeDialog();
				segmentedVolumeDialog->setImageData(segmentedData);
				segmentedVolumeDialog->setTransferFunction(sculpture->getTransferFunction());
				segmentedVolumeDialog->render();

				int exportSegmentedVolume = segmentedVolumeDialog->exec();

				if (exportSegmentedVolume == QMessageBox::Yes) {
					QString vtiFile = NULL;
					vtiFile = QFileDialog::getSaveFileName(NULL, QObject::tr("Exportar volumen"), QDir(QDir::homePath()).filePath("Sub-volume"), "VTI (*.vti) ;; XML (*.xml)");
					if (vtiFile != NULL) {
						// -- launch progress bar
						QPointer<QProgressBar> bar = new QProgressBar(0);
						QPointer<QProgressDialog> progressDialog = new QProgressDialog(0);
						progressDialog->setWindowTitle(QString("Extrayendo..."));
						progressDialog->setLabelText(QString::fromLatin1("Extrayendo el modelo"));
						progressDialog->setWindowIcon(QIcon(":/icons/3DCurator.png"));
						progressDialog->setWindowFlags(progressDialog->windowFlags() & ~Qt::WindowCloseButtonHint);
						progressDialog->setCancelButton(0);
						progressDialog->setBar(bar);
						progressDialog->show();
						bar->close();
						QApplication::processEvents();
						// -- END launch progress bar

						vtkSmartPointer<vtkXMLImageDataWriter> writer = vtkSmartPointer<vtkXMLImageDataWriter>::New();
						writer->SetFileName(vtiFile.toUtf8().constData());
						writer->SetInputData(segmentedData);
						writer->Write();

						// -- close progress bar
						progressDialog->close();
						// -- END close progress bar
					}
				}
			}
		}
	}
}

void InteractorStyleSegmentation::SetSlicePlane(SlicePlane* slicePlane) {
	this->slicePlane = slicePlane;
}

void InteractorStyleSegmentation::SetSculpture(Sculpture* sculpture) {
	this->sculpture = sculpture;
}