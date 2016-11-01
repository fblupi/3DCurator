#include "interactorStyleDeleter.h"

vtkStandardNewMacro(InteractorStyleDeleter);

void InteractorStyleDeleter::OnLeftButtonDown() {
	vtkSmartPointer<vtkVolumePicker> picker = vtkSmartPointer<vtkVolumePicker>::New();
	picker->SetUseVolumeGradientOpacity(true); // computa el gradiente al hacer pick
	picker->SetVolumeOpacityIsovalue(0.1); // establece el valor a partir del cuál pickear

	int* pos = this->GetInteractor()->GetEventPosition(); // posición del ratón en el render window
	picker->Pick(pos[0], pos[1], pos[2], this->GetDefaultRenderer()); // realiza pick sobre la posición del ratón en el render window

	int* ijk = picker->GetPointIJK(); // voxel seleccionado

	if (picker->GetPointId() != -1) { // se ha seleccionado un voxel
		double value = figura->getImageData()->GetScalarComponentAsDouble(ijk[0], ijk[1], ijk[2], 0); // valor escalar del voxel
		int * dimensions = figura->getImageData()->GetDimensions(); // dimensión del volumen en x, y, z (para los límites)

		if (value > AIR_HU) { // se ha seleccionado un voxel que no es aire
			// lanza barra de progreso
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

			vtkSmartPointer<vtkImageData> oldData = vtkSmartPointer<vtkImageData>::New();
			oldData->DeepCopy(figura->getImageData()); // guarda los datos por si luego hay que volver al estado original

			deleteByImages(figura->getImageData(), ijk, 0, dimensions[0], 0, dimensions[1], 0, dimensions[2]); // borra
			figura->getImageData()->Modified(); // actualiza tiempo de modificación para que el mapper recalcule los datos del volumen

			plano->getPlane()->UpdatePlacement(); // actualiza el plano para que se actualicen los cambios en el corte
			viewer->Render(); // renderiza el corte

			progressDialog->close(); // cierra barra de progreso

			// crea mensaje de confirmación
			QPointer<QMessageBox> confirmBox = new QMessageBox(0);
			confirmBox->setWindowTitle(QString::fromLatin1("Confirmar"));
			confirmBox->setWindowIcon(QIcon(":/icons/3DCurator.png"));
			confirmBox->setIcon(QMessageBox::Question);
			confirmBox->setText(QString::fromLatin1("¿Actualizar cambios?"));
			confirmBox->setStandardButtons(QMessageBox::Yes | QMessageBox::No);
			confirmBox->button(QMessageBox::Yes)->setText(QString::fromLatin1("Sí"));
			confirmBox->button(QMessageBox::No)->setText(QString::fromLatin1("No"));

			if (confirmBox->exec() == QMessageBox::No) { // comprueba si se tiene que deshacer el cambio
				// lanza barra de progreso
				progressDialog->setWindowTitle(QString("Restaurando..."));
				progressDialog->setLabelText(QString::fromLatin1("Deshaciendo borrado"));
				progressDialog->show();
				QApplication::processEvents();

				figura->getImageData()->DeepCopy(oldData); // vuelve a los datos antes del borrado
				figura->getImageData()->Modified(); // actualiza tiempo de modificación para que el mapper recalcule los datos del volumen

				plano->getPlane()->UpdatePlacement(); // actualiza el plano para que se actualicen los cambios en el corte
				viewer->Render(); // renderiza el corte

				progressDialog->close(); // cierra barra de progreso
			}
		}
	}
}

std::pair<int, int> InteractorStyleDeleter::searchInitialVoxel(vtkSmartPointer<vtkImageData> imageData, const int ijk[3], const int MIN_X, const int MAX_X, const int MIN_Y, const int MAX_Y) {
	if (ijk[0] - 1 >= MIN_X 
		&& imageData->GetScalarComponentAsDouble(ijk[0] - 1, ijk[1], ijk[2], 0) >= MIN_AIR) {
		return std::make_pair(ijk[0] - 1, ijk[1]);	// (x-1, y) es el voxel inicial
	}
	else if (ijk[0] + 1 < MAX_X 
		&& imageData->GetScalarComponentAsDouble(ijk[0] + 1, ijk[1], ijk[2], 0) >= MIN_AIR) {
		return std::make_pair(ijk[0] + 1, ijk[1]);	// (x+1, y) es el voxel inicial
	}
	else if (ijk[1] - 1 >= MIN_Y 
		&& imageData->GetScalarComponentAsDouble(ijk[0], ijk[1] - 1, ijk[2], 0) >= MIN_AIR) {
		return std::make_pair(ijk[0], ijk[1] - 1);	// (x, y-1) es el voxel inicial
	}
	else if (ijk[1] + 1 < MAX_Y 
		&& imageData->GetScalarComponentAsDouble(ijk[0], ijk[1] + 1, ijk[2], 0) >= MIN_AIR) {
		return std::make_pair(ijk[0], ijk[1] + 1);	// (x, y+1) es el voxel inicial
	}
	else if (ijk[0] - 1 >= MIN_X && ijk[1] - 1 >= MIN_Y
		&& imageData->GetScalarComponentAsDouble(ijk[0] - 1, ijk[1] - 1, ijk[2], 0) >= MIN_AIR) {
		return std::make_pair(ijk[0] - 1, ijk[1] - 1);	// (x-1, y-1) es el voxel inicial
	}
	else if (ijk[0] - 1 >= MIN_X && ijk[1] + 1 < MAX_Y
		&& imageData->GetScalarComponentAsDouble(ijk[0] - 1, ijk[1] + 1, ijk[2], 0) >= MIN_AIR) {
		return std::make_pair(ijk[0] - 1, ijk[1] + 1);	// (x-1, y+1) es el voxel inicial
	}
	else if (ijk[0] + 1 < MAX_X && ijk[1] - 1 >= MIN_Y
		&& imageData->GetScalarComponentAsDouble(ijk[0] + 1, ijk[1] - 1, ijk[2], 0) >= MIN_AIR) {
		return std::make_pair(ijk[0] + 1, ijk[1] - 1);	// (x+1, y-1) es el voxel inicial
	}
	else if (ijk[0] + 1 < MAX_X && ijk[1] + 1 < MAX_Y
		&& imageData->GetScalarComponentAsDouble(ijk[0] + 1, ijk[1] + 1, ijk[2], 0) >= MIN_AIR) {
		return std::make_pair(ijk[0] + 1, ijk[1] + 1);	// (x+1, y+1) es el voxel inicial
	}
	else {
		return std::make_pair(ijk[0], ijk[1]);	// (x, y) es el voxel inicial
	}
}

void InteractorStyleDeleter::deleteImage(vtkSmartPointer<vtkImageData> imageData, const int ijk[3], const int MIN_X, const int MAX_X, const int MIN_Y, const int MAX_Y) {
	std::pair<int, int> ij;
	std::stack<std::pair<int, int>> stack;

	ij.first = ijk[0]; ij.second = ijk[1]; // voxel inicial

	if (imageData->GetScalarComponentAsDouble(ijk[0], ijk[1], ijk[2], 0) < MIN_AIR) { // el voxel inicial es aire
		ij = searchInitialVoxel(imageData, ijk, MIN_X, MAX_X, MIN_Y, MAX_Y); // --> actualiza el voxel inicial
	}

	stack.push(ij); // añade el primer voxel
	while (!stack.empty()) { // continua hasta vaciar la pila
		ij = stack.top(); // primer elemento de la pila
		stack.pop(); // elimina el primer elemento de la pila
		if (ij.first < MAX_X && ij.first >= MIN_X && ij.second < MAX_Y && ij.second >= MIN_Y) { // se encuentra entre los límites
			if (imageData->GetScalarComponentAsDouble(ij.first, ij.second, ijk[2], 0) >= MIN_AIR) { // el voxel está en la isla
				imageData->SetScalarComponentFromDouble(ij.first, ij.second, ijk[2], 0, AIR_HU); // actualiza el voxel con el valor del aire
				// añade a la pila los voxeles de alrededor
				stack.push(std::make_pair(ij.first - 1, ij.second - 1));
				stack.push(std::make_pair(ij.first - 1, ij.second));
				stack.push(std::make_pair(ij.first - 1, ij.second + 1));
				stack.push(std::make_pair(ij.first, ij.second - 1));
				stack.push(std::make_pair(ij.first, ij.second + 1));
				stack.push(std::make_pair(ij.first + 1, ij.second - 1));
				stack.push(std::make_pair(ij.first + 1, ij.second));
				stack.push(std::make_pair(ij.first + 1, ij.second + 1));
			}
		}
	}
}

void InteractorStyleDeleter::deleteByImages(vtkSmartPointer<vtkImageData> imageData, const int ijk[3], const int MIN_X, const int MAX_X, const int MIN_Y, const int MAX_Y, const int MIN_Z, const int MAX_Z) {
	int xyz[3] = { ijk[0], ijk[1], ijk[2] }; // voxel inicial

	// borrar imagen actual
	deleteImage(imageData, xyz, MIN_X, MAX_X, MIN_Y, MAX_Y);

	// borrar hacia arriba
	xyz[2] = ijk[2] + 1; // primera imagen
	while (xyz[2] < MAX_Z) { // hasta llegar a la última imagen
		deleteImage(imageData, xyz, MIN_X, MAX_X, MIN_Y, MAX_Y); // elimina imagen
		xyz[2] = xyz[2] + 1; // pasa a la siguiente
	}

	// Borrar hacia abajo
	xyz[2] = ijk[2] - 1; // primera imagen
	while (xyz[2] >= MIN_Z) { // hasta llegar a la última imagen
		deleteImage(imageData, xyz, MIN_X, MAX_X, MIN_Y, MAX_Y); // elimina imagen
		xyz[2] = xyz[2] - 1; // pasa a la siguiente
	}
}

void InteractorStyleDeleter::SetViewer(vtkSmartPointer<vtkImageViewer2> viewer) {
	this->viewer = viewer;
}

void InteractorStyleDeleter::SetDefaultRenderWindow(vtkSmartPointer<vtkRenderWindow> renWin) {
	this->renWin = renWin;
}

void InteractorStyleDeleter::SetFigura(Figura* figura) {
	this->figura = figura;
}

void InteractorStyleDeleter::SetPlano(Plano* plano) {
	this->plano = plano;
}