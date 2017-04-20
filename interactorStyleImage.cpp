#include "interactorStyleImage.h"

#include "measures.h"

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

std::vector<std::pair<std::pair<cv::Point, cv::Point>, double> > getLinesFromImage(Figura *figura, int slice) {
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

	int numLines = foundLines.size() > 15 ? 15 : foundLines.size();
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

	return foundLines;
}

bool isInLine(double a, double b, double m, double n) {
	double result = b - (m * a + n);
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

void regionGrowingWithLineBound(Figura *figura, const int ijk[3], const int MIN_X, const int MAX_X, const int MIN_Y, const int MAX_Y, std::array<int, 2> line) {
	std::pair<int, int> ij;
	std::stack<std::pair<int, int>> stack;

	ij.first = ijk[0]; ij.second = ijk[1]; // voxel inicial

	stack.push(ij); // añade el primer voxel
	while (!stack.empty()) { // continua hasta vaciar la pila
		ij = stack.top(); // primer elemento de la pila
		stack.pop(); // elimina el primer elemento de la pila
		if (ij.first < MAX_X && ij.first >= MIN_X && ij.second < MAX_Y && ij.second >= MIN_Y) { // se encuentra entre los límites
			if (isAdjacent(figura, ij.first, ij.second, ijk[2], -750, -350) 
				&& !isInLine(ij.first, ij.second, -line[0], -line[1])) {
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



void InteractorStyleImage::OnLeftButtonDown() {
	if (plano != NULL && label != NULL && this->GetDefaultRenderer() != NULL) { // se han establecido los elementos necesarios
		vtkSmartPointer<vtkVolumePicker> picker = vtkSmartPointer<vtkVolumePicker>::New();
		int* pos = this->GetInteractor()->GetEventPosition(); // posición del ratón en el render window
		picker->Pick(pos[0], pos[1], pos[2], this->GetDefaultRenderer()); // realiza pick sobre la posición del ratón en el render window

		int* ijk = picker->GetPointIJK();
		
		if (picker->GetPointId() != -1) { // se ha seleccionado un voxel
			ijk[2] = plano->getPlane()->GetCenter()[2] / figura->getImageData()->GetSpacing()[2];

			std::vector<std::vector<std::pair<std::pair<cv::Point, cv::Point>, double> > > lines(figura->getImageData()->GetDimensions()[2]);
			lines.at(ijk[2]) = getLinesFromImage(figura, ijk[2]);

			std::pair<cv::Point, cv::Point> selectedLine = lines.at(ijk[2]).at(12).first;
			cv::Point p0 = selectedLine.first, p1 = selectedLine.second;
			cout << "Selected Line: " << p0 << " ;;; " << p1 << " ;;; " << ijk[2] << endl;

			/*
			label->setText(QString::fromStdString("Borrando")); // actualiza el valor de la etiqueta
			int * dimensions = figura->getImageData()->GetDimensions();
			regionGrowingWithLineBound(figura, ijk, 0, dimensions[0], 0, dimensions[1]); // borra
			figura->getImageData()->Modified(); // actualiza tiempo de modificación para que el mapper recalcule los datos del volumen
			*/
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