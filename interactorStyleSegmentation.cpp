#include "interactorStyleSegmentation.h"

vtkStandardNewMacro(InteractorStyleSegmentation);

void InteractorStyleSegmentation::OnLeftButtonDown() {
	if (plano != NULL && this->GetDefaultRenderer() != NULL) { // se han establecido los elementos necesarios
		vtkSmartPointer<vtkVolumePicker> picker = vtkSmartPointer<vtkVolumePicker>::New();
		int* pos = this->GetInteractor()->GetEventPosition(); // posición del ratón en el render window
		picker->Pick(pos[0], pos[1], pos[2], this->GetDefaultRenderer()); // realiza pick sobre la posición del ratón en el render window

		int* ijk = picker->GetPointIJK();
		
		if (picker->GetPointId() != -1) { // se ha seleccionado un voxel
			ijk[2] = plano->getPlane()->GetCenter()[2] / figura->getImageData()->GetSpacing()[2];

			std::vector<std::vector<Line> > lines(figura->getImageData()->GetDimensions()[2]);
			lines[ijk[2]] = getLinesFromImage(figura, ijk[2]);

			std::string img = generateImage(figura, ijk[2], lines[ijk[2]]);

			LineSelectionDialog *diag = new LineSelectionDialog();
			diag->setImage(img);
			remove(img.c_str());

			int response = diag->exec();
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

				// lanza barra de progreso
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

				int * dimensions = figura->getImageData()->GetDimensions();
				Bounds bounds;
				bounds.MIN_X = 0;
				bounds.MAX_X = dimensions[0];
				bounds.MIN_Y = 0;
				bounds.MAX_Y = dimensions[1];
				bounds.MIN_Z = 0;
				bounds.MAX_Z = dimensions[2];
				regionGrowingWithLineBoundVolume(figura, ijk, bounds, selectedLine, lines); // borra
				figura->getImageData()->Modified(); // actualiza tiempo de modificación para que el mapper recalcule los datos del volumen

				progressDialog->close(); // cierra barra de progreso
			}
		}
	}
}

void InteractorStyleSegmentation::SetPlano(Plano* plano) {
	this->plano = plano;
}

void InteractorStyleSegmentation::SetFigura(Figura* figura) {
	this->figura = figura;
}