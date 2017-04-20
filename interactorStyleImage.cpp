#include "interactorStyleImage.h"

#include "measures.h"
#include "utils.h"

#include <vector>
#include <stack>
#include <array>
#include <stdio.h>

#include <vtkVolumePicker.h>
#include <vtkResliceCursorPicker.h>
#include <vtkPointPlacer.h>
#include <vtkRenderer.h>
#include <vtkExtractVOI.h>
#include <vtkPNGWriter.h>
#include <vtkImageMapToColors.h>

#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"

vtkStandardNewMacro(InteractorStyleImage);

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

	int numLines = foundLines.size() > 50 ? 50 : foundLines.size();
	/*
	for (int i = 0; i < numLines; i++) {
		cv::Point p0 = foundLines[i].first.first, p1 = foundLines[i].first.second;
		//cv::Scalar color = i == 0 ? cv::Scalar(255, 0, 0) : cv::Scalar(0, 0, 255);
		cv::Scalar color;
		switch (i) {
		case 8:
			color = cv::Scalar(0, 0, 255);
			cout << i << " - RED: " << p0 << " ;;; " << p1 << " ;;; " << slice << endl;
			break;
		case 9:
			color = cv::Scalar(0, 255, 0);
			cout << i << " - GREEN: " << p0 << " ;;; " << p1 << " ;;; " << slice << endl;
			break;
		case 10:
			color = cv::Scalar(255, 0, 0);
			cout << i << " - BLUE: " << p0 << " ;;; " << p1 << " ;;; " << slice << endl;
			break;
		case 11:
			color = cv::Scalar(0, 255, 255); 
			cout << i << " - YELLOW: " << p0 << " ;;; " << p1 << " ;;; " << slice << endl;
			break;
		case 12:
			color = cv::Scalar(255, 255, 0);
			cout << i << " - CYAN: " << p0 << " ;;; " << p1 << " ;;; " << slice << endl;
			break;
		case 13:
			color = cv::Scalar(255, 0, 255);
			cout << i << " - MAGENTA: " << p0 << " ;;; " << p1 << " ;;; " << slice << endl;
			break;
		case 14:
			color = cv::Scalar(255, 255, 255);
			cout << i << " - WHITE: " << p0 << " ;;; " << p1 << " ;;; " << slice << endl;
			break;
		default:
			color = cv::Scalar(128, 128, 128);
			cout << i << " - GREY: " << p0 << " ;;; " << p1 << " ;;; " << slice << endl;
			break;
		}
		line(cdst, p0, p1, color, 1, cv::LINE_AA);
	}
	imshow("detected lines", cdst);
	*/
	remove(("tmp" + std::to_string(slice) + ".png").c_str());

	std::vector<std::pair<cv::Point, cv::Point> > result(foundLines.size());

	for (int i = 0; i < foundLines.size(); i++) {
		result[i] = foundLines[i].first;
	}

	return result;
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

void regionGrowingWithLineBoundImage(Figura *figura, const int ijk[3], const int MIN_X, const int MAX_X, const int MIN_Y, const int MAX_Y, std::pair<cv::Point, cv::Point> line) {
	std::pair<int, int> ij;
	std::stack<std::pair<int, int> > stack;

	int A[3] = { line.first.x, line.first.y, ijk[2] };
	int B[3] = { line.second.x, line.second.y, ijk[2] };
	std::array<double, 2> eq = getEquation(A, B);

	ij.first = ijk[0]; ij.second = ijk[1]; // voxel inicial

	stack.push(ij); // añade el primer voxel
	while (!stack.empty()) { // continua hasta vaciar la pila
		ij = stack.top(); // primer elemento de la pila
		stack.pop(); // elimina el primer elemento de la pila
		if (ij.first < MAX_X && ij.first >= MIN_X && ij.second < MAX_Y && ij.second >= MIN_Y) { // se encuentra entre los límites
			if (isAdjacent(figura, ij.first, ij.second, ijk[2], -750, -350) 
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
			}
		}
	}
}

std::pair<std::pair<cv::Point, cv::Point>, double> findNearestLine(std::vector<std::pair<cv::Point, cv::Point> > lines, std::pair<cv::Point, cv::Point> goal, const int originalZ, const int z) {
	double minDistance = VTK_DOUBLE_MAX;
	double min = 0;
	int A[3] = { goal.first.x, goal.first.y, originalZ };
	int A_[3] = { goal.second.x, goal.second.y, originalZ };
	for (int i = 0; i < lines.size(); i++) {
		int B[3] = { lines[i].first.x, lines[i].first.y, z };
		int B_[3] = { lines[i].second.x, lines[i].second.y, z };
		if (z > 237) {
			std::cout << "A=(" << A[0] << "," << A[1] << "," << A[2] << std::endl;
			std::cout << "A'=(" << A_[0] << "," << A_[1] << "," << A_[2] << std::endl;
			std::cout << "B=(" << B[0] << "," << B[1] << "," << B[2] << std::endl;
			std::cout << "B'=(" << B_[0] << "," << B_[1] << "," << B_[2] << std::endl;
			int a;
			std::cin >> a;
		}
		double distance = getDistance(A, A_, B, B_);
		if (distance < minDistance) {
			min = i;
			minDistance = distance;
		}
	}
	return std::make_pair(lines[min], minDistance);
}

void regionGrowingWithLineBoundVolume(Figura *figura, const int ijk[3], const int MIN_X, const int MAX_X, const int MIN_Y, const int MAX_Y, const int MIN_Z, const int MAX_Z, std::pair<cv::Point, cv::Point> firstLine, std::vector<std::vector<std::pair<cv::Point, cv::Point> > > &lines) {
	int xyz[3] = { ijk[0], ijk[1], ijk[2] }; // voxel inicial
	std::pair<cv::Point, cv::Point> lastLine = firstLine;
	int lastZ = ijk[2];
	regionGrowingWithLineBoundImage(figura, xyz, MIN_X, MAX_X, MIN_Y, MAX_Y, lastLine);

	int numberOfNoLines = 0;
	// borrar hacia arriba
	xyz[2] = ijk[2] + 1; // primera imagen
	while (xyz[2] < MAX_Z) { // hasta llegar a la última imagen
		std::cout << "Slice: " << xyz[2] << std::endl;
		lines[xyz[2]] = getLinesFromImage(figura, xyz[2]);
		std::pair<std::pair<cv::Point, cv::Point>, double> nearestLine = findNearestLine(lines[xyz[2]], lastLine, lastZ, xyz[2]);
		if (nearestLine.second < 0.5) {
			std::cout << "Deleting" << std::endl;
			//if (numberOfNoLines != 0)
			lastLine = nearestLine.first;
			lastZ = ijk[2];
			regionGrowingWithLineBoundImage(figura, xyz, MIN_X, MAX_X, MIN_Y, MAX_Y, lastLine);
			numberOfNoLines = 0;
		} else {
			std::cout << "I can't delete cause distance is " << nearestLine.second << std::endl;
			numberOfNoLines++;
		}
		xyz[2] = xyz[2] + 1; // pasa a la siguiente
	}

	numberOfNoLines = 0;
	lastLine = firstLine;
	lastZ = ijk[2];

	// Borrar hacia abajo
	xyz[2] = ijk[2] - 1; // primera imagen
	while (xyz[2] >= MIN_Z) { // hasta llegar a la última imagen
		lines[xyz[2]] = getLinesFromImage(figura, xyz[2]);
		std::pair<std::pair<cv::Point, cv::Point>, double> nearestLine = findNearestLine(lines[xyz[2]], lastLine, lastZ, xyz[2]);
		if (nearestLine.second < 0.5) {
			std::cout << "Deleting " << xyz[2] << std::endl;
			//if (numberOfNoLines != 0)
			lastLine = nearestLine.first;
			lastZ = ijk[2];
			regionGrowingWithLineBoundImage(figura, xyz, MIN_X, MAX_X, MIN_Y, MAX_Y, lastLine);
			numberOfNoLines = 0;
		} else {
			std::cout << "I can't delete " << xyz[2] << " cause distance is " << nearestLine.second << std::endl;
			numberOfNoLines++;
		}
		xyz[2] = xyz[2] - 1; // pasa a la siguiente
	}

}

void InteractorStyleImage::OnLeftButtonDown() {
	if (plano != NULL && label != NULL && this->GetDefaultRenderer() != NULL) { // se han establecido los elementos necesarios
		vtkSmartPointer<vtkVolumePicker> picker = vtkSmartPointer<vtkVolumePicker>::New();
		int* pos = this->GetInteractor()->GetEventPosition(); // posición del ratón en el render window
		picker->Pick(pos[0], pos[1], pos[2], this->GetDefaultRenderer()); // realiza pick sobre la posición del ratón en el render window

		int* ijk = picker->GetPointIJK();
		
		if (picker->GetPointId() != -1) { // se ha seleccionado un voxel
			ijk[2] = plano->getPlane()->GetCenter()[2] / figura->getImageData()->GetSpacing()[2];

			std::vector<std::vector<std::pair<cv::Point, cv::Point> > > lines(figura->getImageData()->GetDimensions()[2]);
			lines[ijk[2]] = getLinesFromImage(figura, ijk[2]);

			std::pair<cv::Point, cv::Point> selectedLine = lines[ijk[2]][12];
			//cv::Point p0 = selectedLine.first, p1 = selectedLine.second;
			//cout << "Selected Line: " << p0 << " ;;; " << p1 << " ;;; " << ijk[2] << endl;

			label->setText(QString::fromStdString("Borrando")); // actualiza el valor de la etiqueta

			int * dimensions = figura->getImageData()->GetDimensions();
			regionGrowingWithLineBoundVolume(figura, ijk, 0, dimensions[0], 0, dimensions[1], 0, dimensions[2], selectedLine, lines); // borra
			figura->getImageData()->Modified(); // actualiza tiempo de modificación para que el mapper recalcule los datos del volumen
		}
	}
}

void InteractorStyleImage::OnMouseMove() {

	vtkInteractorStyleImage::OnMouseMove(); // Forward events
}

void InteractorStyleImage::SetPlano(Plano* plano) {
	this->plano = plano;
}

void InteractorStyleImage::SetLabel(QLabel* label) {
	this->label = label;
}

void InteractorStyleImage::SetFigura(Figura* figura) {
	this->figura = figura;
}