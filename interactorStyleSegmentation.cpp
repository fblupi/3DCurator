#include "interactorStyleSegmentation.h"

vtkStandardNewMacro(InteractorStyleSegmentation);

#define MIN_ANGLE 0.5
#define MIN_DISTA 5
#define LINE_TOLERANCE 5
#define MIN_WOOD -750
#define MAX_WOOD -300

bool longerLine(std::pair<std::pair<cv::Point, cv::Point>, double> i, std::pair<std::pair<cv::Point, cv::Point>, double> j) {
	return i.second > j.second;
}

std::vector<std::pair<cv::Point, cv::Point> > getLinesFromImage(Figura *figura, int slice) {
	vtkSmartPointer<vtkImageMapToColors> map = vtkSmartPointer<vtkImageMapToColors>::New();
	map->SetInputData(figura->getImageData());
	map->SetLookupTable(figura->getTransferFunction()->getColorFun());
	
	vtkSmartPointer<vtkExtractVOI> voi = vtkSmartPointer<vtkExtractVOI>::New();
	voi->SetInputConnection(map->GetOutputPort());
	voi->SetVOI(0, figura->getImageData()->GetDimensions()[0] - 1, 0, figura->getImageData()->GetDimensions()[1] - 1, slice, slice);
	voi->Update();

	vtkSmartPointer<vtkPNGWriter> png = vtkSmartPointer<vtkPNGWriter>::New();
	png->SetInputData(voi->GetOutput());
	png->SetFileName(("tmp" + std::to_string(slice) + ".png").c_str());
	png->Write();
	
	cv::Mat src, dst, cdst;
	src = cv::imread(("tmp" + std::to_string(slice) + ".png").c_str(), 0);

	cv::Canny(src, dst, 30, 50, 3);
	cv::cvtColor(dst, cdst, cv::COLOR_GRAY2BGR);
	
	std::vector<cv::Vec4i> lines;
	cv::HoughLinesP(dst, lines, 1, CV_PI / 180, 50, 50, 10);
	std::vector<std::pair<std::pair<cv::Point, cv::Point>, double> > foundLines;
	for (int i = 0; i < lines.size(); i++) {
		std::pair<std::pair<cv::Point, cv::Point>, double> l = std::make_pair(
			std::make_pair(
				cv::Point(lines[i][0], lines[i][1]),
				cv::Point(lines[i][2], lines[i][3])
			),
			cv::norm(cv::Point(lines[i][0], lines[i][1]) - cv::Point(lines[i][2], lines[i][3])));
		foundLines.push_back(l);
	}
	sort(foundLines.begin(), foundLines.end(), longerLine);

	remove(("tmp" + std::to_string(slice) + ".png").c_str());

	std::vector<std::pair<cv::Point, cv::Point> > result(foundLines.size());

	for (int i = 0; i < foundLines.size(); i++) {
		result[i] = foundLines[i].first;
	}

	return result;
}

std::string generateImage(Figura *figura, int slice, std::vector<std::pair<cv::Point, cv::Point> > lines) {
	std::string filename = "tmp" + std::to_string(slice) + ".png";

	vtkSmartPointer<vtkImageMapToColors> map = vtkSmartPointer<vtkImageMapToColors>::New();
	map->SetInputData(figura->getImageData());
	map->SetLookupTable(figura->getTransferFunction()->getColorFun());

	vtkSmartPointer<vtkExtractVOI> voi = vtkSmartPointer<vtkExtractVOI>::New();
	voi->SetInputConnection(map->GetOutputPort());
	voi->SetVOI(0, figura->getImageData()->GetDimensions()[0] - 1, 0, figura->getImageData()->GetDimensions()[1] - 1, slice, slice);
	voi->Update();

	vtkSmartPointer<vtkPNGWriter> png = vtkSmartPointer<vtkPNGWriter>::New();
	png->SetInputData(voi->GetOutput());
	png->SetFileName(filename.c_str());
	png->Write();

	cv::Mat src;
	src = cv::imread(filename.c_str(), 1);

	remove(filename.c_str());

	int numLines = lines.size() > 6 ? 6 : lines.size();

	for (int i = 0; i < numLines; i++) {
		cv::Point p0 = lines[i].first, p1 = lines[i].second;
		cv::Scalar color;
		switch (i) {
		case 0:
			color = cv::Scalar(0, 0, 255);
			break;
		case 1:
			color = cv::Scalar(0, 255, 0);
			break;
		case 2:
			color = cv::Scalar(255, 0, 0);
			break;
		case 3:
			color = cv::Scalar(0, 255, 255);
			break;
		case 4:
			color = cv::Scalar(255, 255, 0);
			break;
		case 5:
			color = cv::Scalar(255, 0, 255);
			break;
		case 6:
			color = cv::Scalar(255, 255, 255);
			break;
		default:
			color = cv::Scalar(128, 128, 128);
			break;
		}
		line(src, p0, p1, color, 1, cv::LINE_AA);
	}

	std::vector<int> compression_params;
	compression_params.push_back(CV_IMWRITE_PNG_COMPRESSION);
	compression_params.push_back(9);
	imwrite(filename, src, compression_params);

	return filename;
}

bool isInLine(double x, double y, double a, double b, int max) {
	double result = y - max - (a * x + b);
	if (result >= -LINE_TOLERANCE && result <= LINE_TOLERANCE) {
		return true;
	} else {
		return false;
	}
}

bool isAdjacent(Figura *figura, double x, double y, double z, double MIN, double MAX) {
	double value = figura->getImageData()->GetScalarComponentAsFloat(x, y, z, 0);
	if (value >= MIN && value <= MAX)
		return true;
	else
		return false;
}

std::pair<int, int> searchInitialVoxel(Figura *figura, const int ijk[3], const int MIN_X, const int MAX_X, const int MIN_Y, const int MAX_Y, double MIN, double MAX, std::array<double, 2> eq) {
	std::pair<int, int> ij;
	std::queue<std::pair<int, int> > queue;
	
	ij.first = ijk[0]; ij.second = ijk[1];

	queue.push(ij);
	while (!queue.empty()) {
		ij = queue.front();
		queue.pop();
		if (ij.first < MAX_X && ij.first >= MIN_X && ij.second < MAX_Y && ij.second >= MIN_Y
			&& !isInLine(ij.first, ij.second, -eq[0], -eq[1], MAX_X)) {
			if (isAdjacent(figura, ij.first, ij.second, ijk[2], MIN_WOOD, MAX_WOOD)) {
				return ij;
			} else {
				queue.push(std::make_pair(ij.first - 1, ij.second - 1));
				queue.push(std::make_pair(ij.first - 1, ij.second));
				queue.push(std::make_pair(ij.first - 1, ij.second + 1));
				queue.push(std::make_pair(ij.first, ij.second - 1));
				queue.push(std::make_pair(ij.first, ij.second + 1));
				queue.push(std::make_pair(ij.first + 1, ij.second - 1));
				queue.push(std::make_pair(ij.first + 1, ij.second));
				queue.push(std::make_pair(ij.first + 1, ij.second + 1));
			}
		}
	}
	ij.first = ijk[0]; ij.second = ijk[1];
	return ij;
}

std::pair<int, int> regionGrowingWithLineBoundImage(Figura *figura, const int ijk[3], const int MIN_X, const int MAX_X, const int MIN_Y, const int MAX_Y, std::array<double, 2> eq) {
	std::pair<int, int> ij;
	std::pair<int, int> centroid;
	std::pair<int, int> min = std::make_pair(MAX_X, MAX_Y);
	std::pair<int, int> max = std::make_pair(MIN_X, MIN_Y);
	std::stack<std::pair<int, int> > stack;

	ij.first = ijk[0]; ij.second = ijk[1]; // voxel inicial

	stack.push(ij); // añade el primer voxel
	while (!stack.empty()) { // continua hasta vaciar la pila
		ij = stack.top(); // primer elemento de la pila
		stack.pop(); // elimina el primer elemento de la pila
		if (ij.first < MAX_X && ij.first >= MIN_X && ij.second < MAX_Y && ij.second >= MIN_Y) { // se encuentra entre los límites
			if (isAdjacent(figura, ij.first, ij.second, ijk[2], MIN_WOOD, MAX_WOOD)
				&& !isInLine(ij.first, ij.second, -eq[0], -eq[1], MAX_X)) {
				figura->getImageData()->SetScalarComponentFromFloat(ij.first, ij.second, ijk[2], 0, AIR_HU); // actualiza el voxel con el valor del aire
				// añade a la pila los voxeles de alrededor
				stack.push(std::make_pair(ij.first - 1, ij.second - 1));
				stack.push(std::make_pair(ij.first - 1, ij.second));
				stack.push(std::make_pair(ij.first - 1, ij.second + 1));
				stack.push(std::make_pair(ij.first, ij.second - 1));
				stack.push(std::make_pair(ij.first, ij.second + 1));
				stack.push(std::make_pair(ij.first + 1, ij.second - 1));
				stack.push(std::make_pair(ij.first + 1, ij.second));
				stack.push(std::make_pair(ij.first + 1, ij.second + 1));
				// actualiza "centroide"
				if (ij.first < min.first) {
					min.first = ij.first;
				}
				if (ij.second < min.second) {
					min.second = ij.second;
				}
				if (ij.first > max.first) {
					max.first = ij.first;
				}
				if (ij.second > max.second) {
					max.second = ij.second;
				}
			}
		}
	}
	centroid.first = (min.first + max.first) / 2;
	centroid.second = (min.second + max.second) / 2;

	return centroid;
}

std::pair<std::pair<cv::Point, cv::Point>, double> findNearestLine(std::vector<std::pair<cv::Point, cv::Point> > lines, std::pair<cv::Point, cv::Point> goal, const int originalZ, const int z) {
	double minAngle = 90;
	double min = 0;
	int A[3] = { goal.first.x, goal.first.y, originalZ };
	int A_[3] = { goal.second.x, goal.second.y, originalZ };
	for (int i = 0; i < lines.size(); i++) {
		int B[3] = { lines[i].first.x, lines[i].first.y, z };
		int B_[3] = { lines[i].second.x, lines[i].second.y, z };
		double distance = getPointLineDistance(A, A_, B);
		double angle = getAngle(A, A_, B, B_);
		if (angle < minAngle && distance < MIN_DISTA) {
			min = i;
			minAngle = angle;
		}
	}
	return std::make_pair(lines[min], minAngle);
}

void regionGrowingWithLineBoundVolume(Figura *figura, const int ijk[3], const int MIN_X, const int MAX_X, const int MIN_Y, const int MAX_Y, const int MIN_Z, const int MAX_Z, std::pair<cv::Point, cv::Point> firstLine, std::vector<std::vector<std::pair<cv::Point, cv::Point> > > &lines) {
	int xyz[3] = { ijk[0], ijk[1], ijk[2] }; // voxel inicial
	std::pair<cv::Point, cv::Point> lastLine = firstLine;
	int lastZ = ijk[2];
	int U[3] = { lastLine.first.x, lastLine.first.y, lastZ };
	int V[3] = { lastLine.second.x, lastLine.second.y, lastZ };
	std::pair<int, int> lastCentroid = regionGrowingWithLineBoundImage(figura, xyz, MIN_X, MAX_X, MIN_Y, MAX_Y, getLineEquation(U, V));
	std::pair<int, int> lastCentroidAux = lastCentroid;

	int numberOfNoLines = 0;

	// Borrar hacia arriba
	xyz[2] = ijk[2] + 1;
	while (xyz[2] < MAX_Z) {
		lines[xyz[2]] = getLinesFromImage(figura, xyz[2]);
		std::pair<std::pair<cv::Point, cv::Point>, double> nearestLine = findNearestLine(lines[xyz[2]], lastLine, lastZ, xyz[2]);
		if (nearestLine.second < MIN_ANGLE) {
			if (numberOfNoLines != 0) {
				int A[3] = { lastLine.first.x, lastLine.first.y, lastZ };
				int B[3] = { lastLine.second.x, lastLine.second.y, lastZ };
				int C[3] = { nearestLine.first.first.x, nearestLine.first.first.y, xyz[2] };
				std::array<double, 4> P = getPlaneEquation(A, B, C);
				int xyzAux[3] = { xyz[0], xyz[1], xyz[2] - numberOfNoLines };
				for (; xyzAux[2] < xyz[2]; xyzAux[2]++) {
					if (!isAdjacent(figura, xyzAux[0], xyzAux[1], xyzAux[2], MIN_WOOD, MAX_WOOD)) {
						xyzAux[0] = lastCentroid.first;
						xyzAux[1] = lastCentroid.second;
					}
					if (!isAdjacent(figura, xyzAux[0], xyzAux[1], xyzAux[2], MIN_WOOD, MAX_WOOD)) {
						std::pair<int, int> newCentroid = searchInitialVoxel(figura, xyzAux, MIN_X, MAX_X, MIN_Y, MAX_Y, MIN_WOOD, MAX_WOOD, getLineEquationFromPlane(P, xyzAux[2]));
						xyzAux[0] = newCentroid.first;
						xyzAux[1] = newCentroid.second;
					}
					lastCentroid = regionGrowingWithLineBoundImage(figura, xyzAux, MIN_X, MAX_X, MIN_Y, MAX_Y, getLineEquationFromPlane(P, xyzAux[2]));
				} // for
			} // if (numberOfNoLines != 0)
			lastLine = nearestLine.first;
			lastZ = xyz[2];
			int U[3] = { lastLine.first.x, lastLine.first.y, lastZ };
			int V[3] = { lastLine.second.x, lastLine.second.y, lastZ };
			if (!isAdjacent(figura, xyz[0], xyz[1], xyz[2], MIN_WOOD, MAX_WOOD)) {
				xyz[0] = lastCentroid.first;
				xyz[1] = lastCentroid.second;
			}
			if (!isAdjacent(figura, xyz[0], xyz[1], xyz[2], MIN_WOOD, MAX_WOOD)) {
				std::pair<int, int> newCentroid = searchInitialVoxel(figura, xyz, MIN_X, MAX_X, MIN_Y, MAX_Y, MIN_WOOD, MAX_WOOD, getLineEquation(U, V));
				xyz[0] = newCentroid.first;
				xyz[1] = newCentroid.second;
			}
			lastCentroid = regionGrowingWithLineBoundImage(figura, xyz, MIN_X, MAX_X, MIN_Y, MAX_Y, getLineEquation(U, V));
			numberOfNoLines = 0;
		} // if (nearestLine.second < MIN_ANGLE)
		else { 
			numberOfNoLines++;
		}
		xyz[2] = xyz[2] + 1; // pasa a la siguiente
	} // while

	numberOfNoLines = 0;
	lastLine = firstLine;
	lastCentroid = lastCentroidAux;
	lastZ = ijk[2];
	xyz[0] = ijk[0];
	xyz[1] = ijk[1];

	// Borrar hacia abajo
	xyz[2] = ijk[2] - 1; // primera imagen
	while (xyz[2] >= MIN_Z) { // hasta llegar a la última imagen
		lines[xyz[2]] = getLinesFromImage(figura, xyz[2]);
		std::pair<std::pair<cv::Point, cv::Point>, double> nearestLine = findNearestLine(lines[xyz[2]], lastLine, lastZ, xyz[2]);
		if (nearestLine.second < MIN_ANGLE) {
			if (numberOfNoLines != 0) {
				int A[3] = { lastLine.first.x, lastLine.first.y, lastZ };
				int B[3] = { lastLine.second.x, lastLine.second.y, lastZ };
				int C[3] = { nearestLine.first.first.x, nearestLine.first.first.y, xyz[2] };
				std::array<double, 4> P = getPlaneEquation(A, B, C);
				int xyzAux[3] = { xyz[0], xyz[1], xyz[2] + numberOfNoLines };
				for (; xyzAux[2] > xyz[2]; xyzAux[2]--) {
					if (!isAdjacent(figura, xyzAux[0], xyzAux[1], xyzAux[2], MIN_WOOD, MAX_WOOD)) {
						xyzAux[0] = lastCentroid.first;
						xyzAux[1] = lastCentroid.second;
					}
					if (!isAdjacent(figura, xyzAux[0], xyzAux[1], xyzAux[2], MIN_WOOD, MAX_WOOD)) {
						std::pair<int, int> newCentroid = searchInitialVoxel(figura, xyzAux, MIN_X, MAX_X, MIN_Y, MAX_Y, MIN_WOOD, MAX_WOOD, getLineEquationFromPlane(P, xyzAux[2]));
						xyzAux[0] = newCentroid.first;
						xyzAux[1] = newCentroid.second;
					}
					lastCentroid = regionGrowingWithLineBoundImage(figura, xyzAux, MIN_X, MAX_X, MIN_Y, MAX_Y, getLineEquationFromPlane(P, xyzAux[2]));
				} // for
			} // if (numberOfNoLines != 0)
			lastLine = nearestLine.first;
			lastZ = xyz[2];
			int U[3] = { lastLine.first.x, lastLine.first.y, lastZ };
			int V[3] = { lastLine.second.x, lastLine.second.y, lastZ };			
			if (!isAdjacent(figura, xyz[0], xyz[1], xyz[2], MIN_WOOD, MAX_WOOD)) {
				xyz[0] = lastCentroid.first;
				xyz[1] = lastCentroid.second;
			}
			if (!isAdjacent(figura, xyz[0], xyz[1], xyz[2], MIN_WOOD, MAX_WOOD)) {
				std::pair<int, int> newCentroid = searchInitialVoxel(figura, xyz, MIN_X, MAX_X, MIN_Y, MAX_Y, MIN_WOOD, MAX_WOOD, getLineEquation(U, V));
				xyz[0] = newCentroid.first;
				xyz[1] = newCentroid.second;
			}
			lastCentroid = regionGrowingWithLineBoundImage(figura, xyz, MIN_X, MAX_X, MIN_Y, MAX_Y, getLineEquation(U, V));
			numberOfNoLines = 0;
		} // if (nearestLine.second < MIN_ANGLE)
		else {
			numberOfNoLines++;
		}
		xyz[2] = xyz[2] - 1; // pasa a la siguiente
	} // while
}

void InteractorStyleSegmentation::OnLeftButtonDown() {
	if (plano != NULL && this->GetDefaultRenderer() != NULL) { // se han establecido los elementos necesarios
		vtkSmartPointer<vtkVolumePicker> picker = vtkSmartPointer<vtkVolumePicker>::New();
		int* pos = this->GetInteractor()->GetEventPosition(); // posición del ratón en el render window
		picker->Pick(pos[0], pos[1], pos[2], this->GetDefaultRenderer()); // realiza pick sobre la posición del ratón en el render window

		int* ijk = picker->GetPointIJK();
		
		if (picker->GetPointId() != -1) { // se ha seleccionado un voxel
			ijk[2] = plano->getPlane()->GetCenter()[2] / figura->getImageData()->GetSpacing()[2];

			std::vector<std::vector<std::pair<cv::Point, cv::Point> > > lines(figura->getImageData()->GetDimensions()[2]);
			lines[ijk[2]] = getLinesFromImage(figura, ijk[2]);

			std::string img = generateImage(figura, ijk[2], lines[ijk[2]]);

			LineSelectionDialog *diag = new LineSelectionDialog();
			diag->setImage(img);

			int response = diag->exec();
			if (response != LINE_CANCEL) { // comprueba si se tiene que deshacer el cambio
				std::pair<cv::Point, cv::Point> selectedLine;
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
				regionGrowingWithLineBoundVolume(figura, ijk, 0, dimensions[0], 0, dimensions[1], 0, dimensions[2], selectedLine, lines); // borra
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