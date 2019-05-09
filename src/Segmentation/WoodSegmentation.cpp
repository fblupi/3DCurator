#include "WoodSegmentation.h"

bool longerLine(const HoughLine &i, const HoughLine &j) {
    return i.second > j.second;
}

std::vector<Line> getLinesFromImage(const vtkSmartPointer<vtkImageData> &imageData, const vtkSmartPointer<vtkColorTransferFunction> &colorFun, const int slice, const Bounds &bounds) {
    vtkSmartPointer<vtkImageMapToColors> map = vtkSmartPointer<vtkImageMapToColors>::New();
    map->SetInputData(imageData);
    map->SetLookupTable(colorFun);

    vtkSmartPointer<vtkExtractVOI> voi = vtkSmartPointer<vtkExtractVOI>::New();
    voi->SetInputConnection(map->GetOutputPort());
    voi->SetVOI(bounds.MIN_X, bounds.MAX_X - 1, bounds.MIN_Y, bounds.MAX_Y - 1, slice, slice);
    voi->Update();

    std::string filename = "tmp" + std::to_string(slice) + ".png";

    vtkSmartPointer<vtkPNGWriter> png = vtkSmartPointer<vtkPNGWriter>::New();
    png->SetInputData(voi->GetOutput());
    png->SetFileName(filename.c_str());
    png->Write();

    cv::Mat src, dst;
    src = cv::imread(filename, 0);
    remove(filename.c_str());

    cv::Canny(src, dst, 30, 50, 3);

    std::vector<cv::Vec4i> lines;
    cv::HoughLinesP(dst, lines, 1, CV_PI / 180, 50, 50, 10);
    std::vector<HoughLine> foundLines;
    for (auto line : lines) {
        HoughLine l = std::make_pair(
            std::make_pair(
                cv::Point(line[0], line[1]),
                cv::Point(line[2], line[3])
            ),
            cv::norm(cv::Point(line[0], line[1]) - cv::Point(line[2], line[3])));
        foundLines.push_back(l);
    }
    sort(foundLines.begin(), foundLines.end(), longerLine);

    std::vector<Line> result(foundLines.size());

    for (int i = 0; i < foundLines.size(); i++) {
        result[i] = foundLines[i].first;
    }

    return result;
}

std::string generateImage(const vtkSmartPointer<vtkImageData> &imageData, const vtkSmartPointer<vtkColorTransferFunction> &colorFun, int slice, const Bounds &bounds, const std::vector<Line> &lines) {
    std::string filename = "tmp" + std::to_string(slice) + ".png";

    vtkSmartPointer<vtkImageMapToColors> map = vtkSmartPointer<vtkImageMapToColors>::New();
    map->SetInputData(imageData);
    map->SetLookupTable(colorFun);

    vtkSmartPointer<vtkExtractVOI> voi = vtkSmartPointer<vtkExtractVOI>::New();
    voi->SetInputConnection(map->GetOutputPort());
    voi->SetVOI(bounds.MIN_X, bounds.MAX_X - 1, bounds.MIN_Y, bounds.MAX_Y - 1, slice, slice);
    voi->Update();

    vtkSmartPointer<vtkPNGWriter> png = vtkSmartPointer<vtkPNGWriter>::New();
    png->SetInputData(voi->GetOutput());
    png->SetFileName(filename.c_str());
    png->Write();

    cv::Mat src;
    src = cv::imread(filename, 1);

    remove(filename.c_str());

    size_t numLines = lines.size() > 6 ? 6 : lines.size();

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
            color = cv::Scalar(255, 255, 0);
            break;
        case 4:
            color = cv::Scalar(255, 0, 255);
            break;
        case 5:
            color = cv::Scalar(0, 255, 255);
            break;
        default:
            color = cv::Scalar(128, 128, 128);
            break;
        }
        line(src, p0, p1, color, 1, cv::LINE_AA);
    }

    std::vector<int> compression_params;
    compression_params.push_back(cv::IMWRITE_PNG_COMPRESSION);
    compression_params.push_back(9);
    imwrite(filename, src, compression_params);

    return filename;
}

bool isInLine(const Coord2D &coord, const LineEq &eq, int epsilon) {
    double result = coord[1] - epsilon + (eq[0] * coord[0] + eq[1]);

    return result >= -LINE_TOLERANCE && result <= LINE_TOLERANCE;
}

bool isAdjacent(const vtkSmartPointer<vtkImageData> &imageData, const Coord3D &coord, double min, double max) {
    double value = imageData->GetScalarComponentAsFloat(coord[0], coord[1], coord[2], 0);

    return value >= min && value <= max;
}

Coord2D searchInitialVoxel(const vtkSmartPointer<vtkImageData> &imageData, const int ijk[3], const Bounds &bounds, double min, double max, const LineEq &eq) {
    Coord2D ij;
    std::queue<Coord2D> queue;
    std::set<Coord2D> set;

    ij[0] = ijk[0]; ij[1] = ijk[1];

    queue.push(ij);
    set.insert(ij);
    while (!queue.empty()) {
        ij = queue.front();
        queue.pop();
        if (ij[0] < bounds.MAX_X && ij[0] >= bounds.MIN_X && ij[1] < bounds.MAX_Y && ij[1] >= bounds.MIN_Y
            && !isInLine(ij, eq, bounds.MAX_X)) {
            if (isAdjacent(imageData, { ij[0], ij[1], ijk[2] }, min, max)) {
                return ij;
            } else {
                if (set.find({ ij[0] - 1, ij[1] - 1 }) == set.end()) {
                    queue.push({ ij[0] - 1, ij[1] - 1 });
                    set.insert({ ij[0] - 1, ij[1] - 1 });
                }
                if (set.find({ ij[0] - 1, ij[1] }) == set.end()) {
                    queue.push({ ij[0] - 1, ij[1] });
                    set.insert({ ij[0] - 1, ij[1] });
                }
                if (set.find({ ij[0] - 1, ij[1] + 1 }) == set.end()) {
                    queue.push({ ij[0] - 1, ij[1] + 1 });
                    set.insert({ ij[0] - 1, ij[1] + 1 });
                }
                if (set.find({ ij[0], ij[1] - 1 }) == set.end()) {
                    queue.push({ ij[0], ij[1] - 1 });
                    set.insert({ ij[0], ij[1] - 1 });
                }
                if (set.find({ ij[0], ij[1] + 1 }) == set.end()) {
                    queue.push({ ij[0], ij[1] + 1 });
                    set.insert({ ij[0], ij[1] + 1 });
                }
                if (set.find({ ij[0] + 1, ij[1] - 1 }) == set.end()) {
                    queue.push({ ij[0] + 1, ij[1] - 1 });
                    set.insert({ ij[0] + 1, ij[1] - 1 });
                }
                if (set.find({ ij[0] + 1, ij[1] }) == set.end()) {
                    queue.push({ ij[0] + 1, ij[1] });
                    set.insert({ ij[0] + 1, ij[1] });
                }
                if (set.find({ ij[0] + 1, ij[1] + 1 }) == set.end()) {
                    queue.push({ ij[0] + 1, ij[1] + 1 });
                    set.insert({ ij[0] + 1, ij[1] + 1 });
                }
            }
        }
    }

    return{ ijk[0], ijk[1] };
}
Coord2D regionGrowingWithLineBoundImage(const vtkSmartPointer<vtkImageData> &inputData, const vtkSmartPointer<vtkImageData> &outputData, const int ijk[3], const Bounds &bounds, const LineEq &eq) {
    Coord2D ij;
    Coord2D min = { bounds.MAX_X, bounds.MAX_Y };
    Coord2D max = { bounds.MIN_X, bounds.MIN_Y };
    std::queue<Coord2D> queue;

    ij[0] = ijk[0]; ij[1] = ijk[1];

    queue.push(ij);
    while (!queue.empty()) {
        ij = queue.front();
        queue.pop();
        if (ij[0] < bounds.MAX_X && ij[0] >= bounds.MIN_X && ij[1] < bounds.MAX_Y && ij[1] >= bounds.MIN_Y) {
            if (isAdjacent(inputData, { ij[0], ij[1], ijk[2] }, MIN_WOOD, MAX_WOOD)
                && !isInLine(ij, eq, bounds.MAX_X)) {
                outputData->SetScalarComponentFromFloat(ij[0], ij[1], ijk[2], 0, inputData->GetScalarComponentAsFloat(ij[0], ij[1], ijk[2], 0));
                inputData->SetScalarComponentFromFloat(ij[0], ij[1], ijk[2], 0, AIR_HU);

                queue.push({ ij[0] - 1, ij[1] - 1 });
                queue.push({ ij[0] - 1, ij[1] });
                queue.push({ ij[0] - 1, ij[1] + 1 });
                queue.push({ ij[0], ij[1] - 1 });
                queue.push({ ij[0], ij[1] + 1 });
                queue.push({ ij[0] + 1, ij[1] - 1 });
                queue.push({ ij[0] + 1, ij[1] });
                queue.push({ ij[0] + 1, ij[1] + 1 });

                if (ij[0] < min[0]) {
                    min[0] = ij[0];
                }
                if (ij[1] < min[1]) {
                    min[1] = ij[1];
                }
                if (ij[0] > max[0]) {
                    max[0] = ij[0];
                }
                if (ij[1] > max[1]) {
                    max[1] = ij[1];
                }
            }
        }
    }

    return{ (min[0] + max[0]) / 2 , (min[1] + max[1]) / 2 };
}

std::pair<Line, double> findNearestLine(const std::vector<Line> &lines, const Line &goal, int originalZ, int z) {
    double minAngle = 90;
    unsigned long min = 0;
    int A[3] = { goal.first.x, goal.first.y, originalZ };
    int A_[3] = { goal.second.x, goal.second.y, originalZ };
    for (int i = 0; i < lines.size(); i++) {
        int B[3] = { lines[i].first.x, lines[i].first.y, z };
        int B_[3] = { lines[i].second.x, lines[i].second.y, z };
        double distance = getPointLineDistance(A, A_, B);
        double angle = getAngle(A, A_, B, B_);
        if (angle < minAngle && distance < MIN_DISTANCE) {
            min = i;
            minAngle = angle;
        }
    }
    return std::make_pair(lines[min], minAngle);
}

void regionGrowingWithLineBoundVolume(const vtkSmartPointer<vtkImageData> &inputData, const vtkSmartPointer<vtkImageData> &outputData, const vtkSmartPointer<vtkColorTransferFunction> &colorFun, const int ijk[3], const Bounds &bounds, const Line &firstLine, std::vector<std::vector<Line> > &lines, bool completeUp, bool completeDown) {
    int xyz[3] = { ijk[0], ijk[1], ijk[2] };
    Line lastLine = firstLine;
    int lastZ = ijk[2];
    int U[3] = { lastLine.first.x, lastLine.first.y, lastZ };
    int V[3] = { lastLine.second.x, lastLine.second.y, lastZ };
    Coord2D lastCentroid = regionGrowingWithLineBoundImage(inputData, outputData, xyz, bounds, getLineEquation(U, V));
    Coord2D lastCentroidAux = lastCentroid;
    PlaneEq P;
    bool lastPlane = false;

    int numberOfNoLines = 0;

    xyz[2] = ijk[2] + 1;
    while (xyz[2] < bounds.MAX_Z) {
        lines[xyz[2]] = getLinesFromImage(inputData, colorFun, xyz[2], bounds);
        std::pair<Line, double> nearestLine = findNearestLine(lines[xyz[2]], lastLine, lastZ, xyz[2]);
        if (nearestLine.second < MIN_ANGLE) {
            if (numberOfNoLines != 0) {
                int A[3] = { lastLine.first.x, lastLine.first.y, lastZ };
                int B[3] = { lastLine.second.x, lastLine.second.y, lastZ };
                int C[3] = { nearestLine.first.first.x, nearestLine.first.first.y, xyz[2] };
                P = getPlaneEquation(A, B, C);
                lastPlane = true;
                int xyzAux[3] = { xyz[0], xyz[1], xyz[2] - numberOfNoLines };
                for (; xyzAux[2] < xyz[2]; xyzAux[2]++) {
                    if (!isAdjacent(inputData, { xyzAux[0], xyzAux[1], xyzAux[2] }, MIN_WOOD, MAX_WOOD)) {
                        xyzAux[0] = lastCentroid[0];
                        xyzAux[1] = lastCentroid[1];
                    }
                    if (!isAdjacent(inputData, { xyzAux[0], xyzAux[1], xyzAux[2] }, MIN_WOOD, MAX_WOOD)) {
                        Coord2D newCentroid = searchInitialVoxel(inputData, xyzAux, bounds, MIN_WOOD, MAX_WOOD, getLineEquationFromPlane(P, xyzAux[2]));
                        xyzAux[0] = newCentroid[0];
                        xyzAux[1] = newCentroid[1];
                    }
                    lastCentroid = regionGrowingWithLineBoundImage(inputData, outputData, xyzAux, bounds, getLineEquationFromPlane(P, xyzAux[2]));
                } // for
            } // if (numberOfNoLines != 0)
            lastLine = nearestLine.first;
            lastZ = xyz[2];
            U[0] = lastLine.first.x; U[1] = lastLine.first.y; U[2] = lastZ;
            V[0] = lastLine.second.x; V[1] = lastLine.second.y; V[2] = lastZ;
            if (!isAdjacent(inputData, { xyz[0], xyz[1], xyz[2] }, MIN_WOOD, MAX_WOOD)) {
                xyz[0] = lastCentroid[0];
                xyz[1] = lastCentroid[1];
            }
            if (!isAdjacent(inputData, { xyz[0], xyz[1], xyz[2] }, MIN_WOOD, MAX_WOOD)) {
                Coord2D newCentroid = searchInitialVoxel(inputData, xyz, bounds, MIN_WOOD, MAX_WOOD, getLineEquation(U, V));
                xyz[0] = newCentroid[0];
                xyz[1] = newCentroid[1];
            }
            lastCentroid = regionGrowingWithLineBoundImage(inputData, outputData, xyz, bounds, getLineEquation(U, V));
            numberOfNoLines = 0;
        } // if (nearestLine.second < MIN_ANGLE)
        else {
            numberOfNoLines++;
        }
        if (completeDown && xyz[2] + 1 == bounds.MAX_Z && numberOfNoLines > 0) {
            if (!lastPlane) {
                int A[3] = { lastLine.first.x, lastLine.first.y, lastZ };
                int B[3] = { lastLine.second.x, lastLine.second.y, lastZ };
                int C[3] = { firstLine.first.x, firstLine.first.y, xyz[2] };
                P = getPlaneEquation(A, B, C);
            }
            int xyzAux[3] = { xyz[0], xyz[1], xyz[2] - numberOfNoLines + 1 };
            for (; xyzAux[2] <= xyz[2]; xyzAux[2]++) {
                if (!isAdjacent(inputData, { xyzAux[0], xyzAux[1], xyzAux[2] }, MIN_WOOD, MAX_WOOD)) {
                    xyzAux[0] = lastCentroid[0];
                    xyzAux[1] = lastCentroid[1];
                }
                if (!isAdjacent(inputData, { xyzAux[0], xyzAux[1], xyzAux[2] }, MIN_WOOD, MAX_WOOD)) {
                    Coord2D newCentroid = searchInitialVoxel(inputData, xyzAux, bounds, MIN_WOOD, MAX_WOOD, getLineEquationFromPlane(P, xyzAux[2]));
                    xyzAux[0] = newCentroid[0];
                    xyzAux[1] = newCentroid[1];
                }
                lastCentroid = regionGrowingWithLineBoundImage(inputData, outputData, xyzAux, bounds, getLineEquationFromPlane(P, xyzAux[2]));
            } // for
        } // if (completeUp && xyz[2] + 1 == bounds.MAX_Z && numberOfNoLines > 0)
        xyz[2] = xyz[2] + 1;
    } // while

    numberOfNoLines = 0;
    lastLine = firstLine;
    lastPlane = false;
    lastCentroid = lastCentroidAux;
    lastZ = ijk[2];
    xyz[0] = ijk[0];
    xyz[1] = ijk[1];

    xyz[2] = ijk[2] - 1;
    while (xyz[2] >= bounds.MIN_Z) {
        lines[xyz[2]] = getLinesFromImage(inputData, colorFun, xyz[2], bounds);
        std::pair<Line, double> nearestLine = findNearestLine(lines[xyz[2]], lastLine, lastZ, xyz[2]);
        if (nearestLine.second < MIN_ANGLE) {
            if (numberOfNoLines != 0) {
                int A[3] = { lastLine.first.x, lastLine.first.y, lastZ };
                int B[3] = { lastLine.second.x, lastLine.second.y, lastZ };
                int C[3] = { nearestLine.first.first.x, nearestLine.first.first.y, xyz[2] };
                P = getPlaneEquation(A, B, C);
                lastPlane = true;
                int xyzAux[3] = { xyz[0], xyz[1], xyz[2] + numberOfNoLines };
                for (; xyzAux[2] > xyz[2]; xyzAux[2]--) {
                    if (!isAdjacent(inputData, { xyzAux[0], xyzAux[1], xyzAux[2] }, MIN_WOOD, MAX_WOOD)) {
                        xyzAux[0] = lastCentroid[0];
                        xyzAux[1] = lastCentroid[1];
                    }
                    if (!isAdjacent(inputData, { xyzAux[0], xyzAux[1], xyzAux[2] }, MIN_WOOD, MAX_WOOD)) {
                        Coord2D newCentroid = searchInitialVoxel(inputData, xyzAux, bounds, MIN_WOOD, MAX_WOOD, getLineEquationFromPlane(P, xyzAux[2]));
                        xyzAux[0] = newCentroid[0];
                        xyzAux[1] = newCentroid[1];
                    }
                    lastCentroid = regionGrowingWithLineBoundImage(inputData, outputData, xyzAux, bounds, getLineEquationFromPlane(P, xyzAux[2]));
                } // for
            } // if (numberOfNoLines != 0)
            lastLine = nearestLine.first;
            lastZ = xyz[2];
            U[0] = lastLine.first.x; U[1] = lastLine.first.y; U[2] = lastZ;
            V[0] = lastLine.second.x; V[1] = lastLine.second.y; V[2] = lastZ;
            if (!isAdjacent(inputData, { xyz[0], xyz[1], xyz[2] }, MIN_WOOD, MAX_WOOD)) {
                xyz[0] = lastCentroid[0];
                xyz[1] = lastCentroid[1];
            }
            if (!isAdjacent(inputData, { xyz[0], xyz[1], xyz[2] }, MIN_WOOD, MAX_WOOD)) {
                Coord2D newCentroid = searchInitialVoxel(inputData, xyz, bounds, MIN_WOOD, MAX_WOOD, getLineEquation(U, V));
                xyz[0] = newCentroid[0];
                xyz[1] = newCentroid[1];
            }
            lastCentroid = regionGrowingWithLineBoundImage(inputData, outputData, xyz, bounds, getLineEquation(U, V));
            numberOfNoLines = 0;
        } // if (nearestLine.second < MIN_ANGLE)
        else {
            numberOfNoLines++;
        }
        if (completeUp && xyz[2] - 1 < bounds.MIN_Z && numberOfNoLines > 0) {
            if (!lastPlane) {
                int A[3] = { lastLine.first.x, lastLine.first.y, lastZ };
                int B[3] = { lastLine.second.x, lastLine.second.y, lastZ };
                int C[3] = { firstLine.first.x, firstLine.first.y, xyz[2] };
                P = getPlaneEquation(A, B, C);
            }
            int xyzAux[3] = { xyz[0], xyz[1], xyz[2] + numberOfNoLines - 1 };
            for (; xyzAux[2] >= xyz[2]; xyzAux[2]--) {
                if (!isAdjacent(inputData, { xyzAux[0], xyzAux[1], xyzAux[2] }, MIN_WOOD, MAX_WOOD)) {
                    xyzAux[0] = lastCentroid[0];
                    xyzAux[1] = lastCentroid[1];
                }
                if (!isAdjacent(inputData, { xyzAux[0], xyzAux[1], xyzAux[2] }, MIN_WOOD, MAX_WOOD)) {
                    Coord2D newCentroid = searchInitialVoxel(inputData, xyzAux, bounds, MIN_WOOD, MAX_WOOD, getLineEquationFromPlane(P, xyzAux[2]));
                    xyzAux[0] = newCentroid[0];
                    xyzAux[1] = newCentroid[1];
                }
                lastCentroid = regionGrowingWithLineBoundImage(inputData, outputData, xyzAux, bounds, getLineEquationFromPlane(P, xyzAux[2]));
            } // for
        } // if (completeUp && xyz[2] - 1 < bounds.MIN_Z && numberOfNoLines > 0)
        xyz[2] = xyz[2] - 1;
    } // while
}
