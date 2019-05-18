#include "InteractorStyleSegmentation.h"

vtkStandardNewMacro(InteractorStyleSegmentation)

void InteractorStyleSegmentation::OnLeftButtonDown() {
    if (slicePlane != nullptr && this->GetDefaultRenderer() != nullptr) {
        vtkSmartPointer<vtkVolumePicker> picker = vtkSmartPointer<vtkVolumePicker>::New();
        int* pos = this->GetInteractor()->GetEventPosition();
        picker->Pick(pos[0], pos[1], pos[2], this->GetDefaultRenderer());

        int* ijk = picker->GetPointIJK();

        if (picker->GetPointId() != -1) {
            ijk[2] = static_cast<int>(slicePlane->getPlane()->GetCenter()[2] / sculpture->getImageData()->GetSpacing()[2]);
            int * dimensions = sculpture->getImageData()->GetDimensions();
            Bounds bounds = {};
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
            auto *diag = new LineSelectionDialog();
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
                    default:
                        selectedLine = lines[ijk[2]][5];
                }

                auto *progressDialog = new ProgressDialog(QCoreApplication::translate("InteractorStyleSegmentation", "SEGMENTING"), QCoreApplication::translate("InteractorStyleSegmentation", "SEGMENTING_PIECE_OF_WOOD_SELECTED"));
                progressDialog->show();

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

                progressDialog->close();

                auto *segmentedVolumeDialog = new SegmentedVolumeDialog(segmentedData, sculpture->getTransferFunction(), backgrounds->getVolumeSegmentingBackground());
                segmentedVolumeDialog->render();

                int exportSegmentedVolume = segmentedVolumeDialog->exec();

                if (exportSegmentedVolume == QMessageBox::Yes) {
                    QString vtiFile = nullptr;
                    vtiFile = QFileDialog::getSaveFileName(nullptr, QCoreApplication::translate("InteractorStyleSegmentation", "SAVE_SUB_VOLUME_CAPTION"), QDir(QDir::homePath()).filePath(QCoreApplication::translate("InteractorStyleSegmentation", "SAVE_SUB_VOLUME_DEFAULT_NAME")), "VTI (*.vti) ;; XML (*.xml)");
                    if (vtiFile != nullptr) {
                        progressDialog = new ProgressDialog(QCoreApplication::translate("InteractorStyleSegmentation", "EXPORTING_SUB_VOLUME"), QCoreApplication::translate("InteractorStyleSegmentation", "EXPORTING_SUB_VOLUME_MODEL"));
                        progressDialog->show();

                        vtkSmartPointer<vtkXMLImageDataWriter> writer = vtkSmartPointer<vtkXMLImageDataWriter>::New();
                        writer->SetFileName(vtiFile.toUtf8().constData());
                        writer->SetInputData(segmentedData);
                        writer->Write();

                        progressDialog->close();
                    }
                }
            }
        }
    }
}

void InteractorStyleSegmentation::SetSlicePlane(SlicePlane* p) {
    this->slicePlane = p;
}

void InteractorStyleSegmentation::SetSculpture(Sculpture* s) {
    this->sculpture = s;
}

void InteractorStyleSegmentation::SetBackgrounds(Backgrounds* b) {
    this->backgrounds = b;
}
