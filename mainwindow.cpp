#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
	ui->setupUi(this); // crea la GUI
	ui->isoValueSlider->setTracking(false); // el evento de cambio de slider cambiado no se lanza hasta que se suelta

	deleting = false; // no está en modo borrado
	showPlane = true; // se muestra el plano

	// se inicializan los contadores de reglas
	volumeRuleCounter = 0;
	sliceRuleCounter = 0;

	itemListEnabled = QFont();
	itemListDisabled = QFont();
	itemListDisabled.setItalic(true); // la fuenta de deshabilitado es en cursiva

	volumeRen = vtkSmartPointer<vtkRenderer>::New();
	meshRen = vtkSmartPointer<vtkRenderer>::New();
	sliceViewer = vtkSmartPointer<vtkImageViewer2>::New();
	volumeStyle = vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New();
	sliceStyle = vtkSmartPointer<InteractorStyleImage>::New();
	deleterStyle = vtkSmartPointer<InteractorStyleDeleter>::New();
	plano = new Plano();
	figura = new Figura();
	defaultTF(); // define la función de transferencia, necesaria para definir las gráficas y el visor de cortes
	defaultMaterial(); // asigna un material por defecto a la figura
	defaultBackgroundColors(); // asigna los colores de fondo por defecto

	colorTFChart = new ColorTFChart(ui->volumeWidget->GetRenderWindow(), ui->colorTFWidget->GetRenderWindow(), figura->getTransferFunction()->getColorFun(), "Densidad", "", MIN_INTENSITY, MAX_INTENSITY);
	scalarTFChart = new OpacityTFChart(ui->volumeWidget->GetRenderWindow(), ui->scalarTFWidget->GetRenderWindow(), figura->getTransferFunction()->getScalarFun(), "Densidad", "Opacidad", MIN_INTENSITY, MAX_INTENSITY);
	gradientTFChart = new OpacityTFChart(ui->volumeWidget->GetRenderWindow(), ui->gradientTFWidget->GetRenderWindow(), figura->getTransferFunction()->getGradientFun(), "Gradiente", "Opacidad", 0, MAX_INTENSITY - MIN_INTENSITY);
	updateSliders(); // actualiza valores de los sliders

	sliceViewer->GetWindowLevel()->SetLookupTable(figura->getTransferFunction()->getColorFun()); // usa los mismo colores en el slice viewer que los usados en la TF
	sliceViewer->SetColorLevel(-600); // nivel de color del viewer
	sliceViewer->SetColorWindow(400); // color de ventana del viewer

	setBackgroundColor(volumeRen, volumeBackground.redF(), volumeBackground.greenF(), volumeBackground.blueF()); // fondo azul oscuro
	setBackgroundColor(meshRen, meshBackground.redF(), meshBackground.greenF(), meshBackground.blueF()); // fondo azul oscuro

    connectComponents(); // conecta los renderers con los widgets

	renderVolume(); // renderiza el volumen
	renderMesh(); // renderiza la malla

	plano->show(false); // no muestra el corte del plano
	enablePlane(); // muestra el plano
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::setBackgroundColor(vtkSmartPointer<vtkRenderer> ren, float r, float g, float b) {
	ren->SetBackground(r, g, b); // cambia el color del renderer
}

void MainWindow::connectComponents() {
	ui->volumeWidget->GetRenderWindow()->AddRenderer(volumeRen); // conecta el volume widget con el renderer
	ui->meshWidget->GetRenderWindow()->AddRenderer(meshRen); // conecta el mesh widget con el renderer

	ui->slicesWidget->SetRenderWindow(sliceViewer->GetRenderWindow()); // conecta el slice widget con el viewer
	sliceViewer->SetInputData(plano->getPlane()->GetResliceOutput()); // asigna el flujo de salida de los cortes del plano al slice viewer

	ui->volumeWidget->GetRenderWindow()->GetInteractor()->SetInteractorStyle(volumeStyle); // asigna el estilo al interactor del volume widget
	plano->getPlane()->SetInteractor(ui->volumeWidget->GetRenderWindow()->GetInteractor()); // asigna el interactor al plano para poder verlo y moverlo

	sliceViewer->SetupInteractor(ui->slicesWidget->GetInteractor()); // asigna el interactor al viewer
	sliceStyle->SetPlano(plano); // asigna el plano
	sliceStyle->SetDefaultRenderer(sliceViewer->GetRenderer()); // asigna el renderer de los cortes
	sliceStyle->SetLabel(ui->coordsAndValueLabel); // asigna la etiqueta
	ui->slicesWidget->GetInteractor()->SetInteractorStyle(sliceStyle); // asigna el estilo al interactor del slice widget

	plano->setViewer(sliceViewer); // asigna el slice viewer al plano para que pueda renderizar cuando se de el evento de mover el plano

	deleterStyle->SetFigura(figura); // asigna la figura al estilo para borrar partes
	deleterStyle->SetPlano(plano); // asigna el plano al estilo para borrar partes
	deleterStyle->SetDefaultRenderer(volumeRen); // asigna el renderer al estilo para borrar partes
	deleterStyle->SetViewer(sliceViewer); // asigna la ventana de cortes
	deleterStyle->SetDefaultRenderWindow(ui->volumeWidget->GetRenderWindow()); // asigna la ventana de renderizado al estilo para borrar partes
}

void MainWindow::drawVolume() {
	volumeRen->AddViewProp(figura->getVolume()); // añade el volumen al renderer
	volumeRen->ResetCamera(); // resetea la cámera
	renderVolume(); // renderiza el volumen
}

void MainWindow::drawMesh() {
	meshRen->AddActor(figura->getMesh()); // añade la malla al renderer
	meshRen->ResetCamera(); // resetea la cámara
	renderMesh(); // renderiza la malla
}

void MainWindow::removeVolume() {
	volumeRen->RemoveAllViewProps(); // borra todos los elementos
	volumeRen->ResetCamera(); // resetea la cámara
	renderVolume(); // renderiza el volumen
}

void MainWindow::removeMesh() {
	meshRen->RemoveAllViewProps(); // borra todos los elementos
	meshRen->ResetCamera(); // resetea la cámara
	renderMesh(); // renderiza la malla
}

void MainWindow::renderVolume() {
	ui->volumeWidget->GetRenderWindow()->Render(); // renderiza
}

void MainWindow::renderMesh() {
	ui->meshWidget->GetRenderWindow()->Render(); // renderiza
}

void MainWindow::renderSlice() {
	sliceViewer->Render(); // renderiza
}

void MainWindow::loadDefaultPreset(QFile *file) {
	if (file->open(QIODevice::ReadOnly | QIODevice::Text)) { // se lee el archivo
		std::istringstream ss;
		ss.str(QString(file->readAll()).toStdString()); // obtiene istringstream a parteir del QFile

		figura->getTransferFunction()->read(ss); // lee la función de transferencia
		file->close(); // se cierra el archivo

		// actualiza etiquetas
		ui->tfName->setText(QString::fromUtf8(figura->getTransferFunction()->getName().c_str()));
		ui->tfDescription->setText(QString::fromUtf8(figura->getTransferFunction()->getDescription().c_str()));
	} else {
		cerr << "Error abriendo archivo por defecto de función de transferencia" << endl;
		exit(-1); // si no lo puede leer se sale
	}
}

void MainWindow::defaultTF() {
	QFile file(":/presets/ct-woodsculpture.xml"); // fichero con el preset
	loadDefaultPreset(&file); // carga el preset a partir dle fichero
}

void MainWindow::defaultMaterial() {
	ui->ambientValue->setValue(0.1); // componente ambiental
	ui->diffuseValue->setValue(0.9); // componente difusa
	ui->specularValue->setValue(0.2); // componente escalar
	ui->powerValue->setValue(10.0); // componente de potencia especular
}

void MainWindow::defaultBackgroundColors() {
	// crea los colores por defecto
	volumeBackground = QColor::fromRgbF(0.1, 0.2, 0.3);
	volumeDeletingBackground = QColor::fromRgbF(0.2, 0.3, 0.1);
	meshBackground = QColor::fromRgbF(0.1, 0.2, 0.3);

	// cambia el color de los botones con los colores de los fondos
	ui->volumeBackground->setStyleSheet("background-color: " + volumeBackground.name());
	ui->volumeDeletingBackground->setStyleSheet("background-color: " + volumeDeletingBackground.name());
	ui->meshBackground->setStyleSheet("background-color: " + meshBackground.name());
}

void MainWindow::defaultPlanePosition() {
	if (figura->getVolume() != NULL) { // hay un volumen
		// dimensión del volumen
		double xSize = figura->getMaxXBound() - figura->getMinXBound(), 
			   ySize = figura->getMaxYBound() - figura->getMinYBound(), 
			   zSize = figura->getMaxZBound() - figura->getMinZBound();
		plano->setOrigin(xSize / 2, ySize / 2, zSize / 2); // coloca el centro del plano en el centro de la figura
		plano->setAxial(); // coloca el plano en posición axial
	} else {
		launchWarningNoVolume(); // lanza mensaje informando que no hay volumen
	}
}

void MainWindow::updateMaterial() {
	// actualiza el material con los valores de la GUI
	figura->setMaterial(
		ui->ambientValue->value(),
		ui->diffuseValue->value(),
		ui->specularValue->value(),
		ui->powerValue->value()
		);
}

void MainWindow::updateSliders() {
	// Color
	ui->colorTFMinSlider->setMinimum((int)MIN_INTENSITY);
	ui->colorTFMinSlider->setValue((int)figura->getTransferFunction()->getColorFun()->GetRange()[0]);
	ui->colorTFMinSlider->setMaximum((int)figura->getTransferFunction()->getColorFun()->GetRange()[1] - 1);

	ui->colorTFMaxSlider->setMinimum((int)figura->getTransferFunction()->getColorFun()->GetRange()[0] + 1);
	ui->colorTFMaxSlider->setValue((int)figura->getTransferFunction()->getColorFun()->GetRange()[1]);
	ui->colorTFMaxSlider->setMaximum((int)MAX_INTENSITY);

	// Scalar
	ui->scalarTFMinSlider->setMinimum((int)MIN_INTENSITY);
	ui->scalarTFMinSlider->setValue((int)figura->getTransferFunction()->getScalarFun()->GetRange()[0]);
	ui->scalarTFMinSlider->setMaximum((int)figura->getTransferFunction()->getScalarFun()->GetRange()[1] - 1);

	ui->scalarTFMaxSlider->setMinimum((int)figura->getTransferFunction()->getScalarFun()->GetRange()[0] + 1);
	ui->scalarTFMaxSlider->setValue((int)figura->getTransferFunction()->getScalarFun()->GetRange()[1]);
	ui->scalarTFMaxSlider->setMaximum((int)MAX_INTENSITY);

	// Gradient
	ui->gradientTFMinSlider->setMinimum(0);
	ui->gradientTFMinSlider->setValue((int)figura->getTransferFunction()->getGradientFun()->GetRange()[0]);
	ui->gradientTFMinSlider->setMaximum((int)figura->getTransferFunction()->getGradientFun()->GetRange()[1] - 1);

	ui->gradientTFMaxSlider->setMinimum((int)figura->getTransferFunction()->getGradientFun()->GetRange()[0] + 1);
	ui->gradientTFMaxSlider->setValue((int)figura->getTransferFunction()->getGradientFun()->GetRange()[1]);
	ui->gradientTFMaxSlider->setMaximum((int)MAX_INTENSITY);
}

void MainWindow::importDICOM() {
	QString dicomFolder = QFileDialog::getExistingDirectory(
		this, tr("Abrir carpeta DICOM"), QDir::homePath(), QFileDialog::ShowDirsOnly); // obtiene directorio

	if (dicomFolder != NULL) { // la carpeta se ha leído bien
		// lanza barra de progreso
		QPointer<QProgressBar> bar = new QProgressBar(0);
		QPointer<QProgressDialog> progressDialog = new QProgressDialog(0);
		progressDialog->setWindowTitle(QString("Cargando..."));
		progressDialog->setLabelText(QString::fromLatin1("Cargando los datos DICOM especificados"));
		progressDialog->setWindowIcon(QIcon(":/icons/3DCurator.png"));
		progressDialog->setWindowFlags(progressDialog->windowFlags() & ~Qt::WindowCloseButtonHint);
		progressDialog->setCancelButton(0);
		progressDialog->setBar(bar);
		progressDialog->show();
		bar->close();
		QApplication::processEvents();

		removeVolume(); // borra volumen
		removeMesh(); // borra malla
		clearAllRules(); // elimina reglas

		plano->show(false); // esconde el plano
		disablePlane(); // deshabilita el plano
		figura->setDICOMFolder(dicomFolder.toUtf8().constData()); // carga los archivos DICOM de la carpeta a la figura
		plano->setInputData(figura->getImageData()); // conecta el plano con los datos del volumen
		ui->labelFolder->setText(dicomFolder); // actualiza el label con el path de la carpeta con los archivos DICOM
		defaultPlanePosition(); // coloca el plano en una posición inicial
		plano->show(true); // muestra el plano
		enablePlane(); // habilita el plano

		drawVolume(); // dibuja volumen
		drawMesh(); // dibuja la malla
		renderSlice(); // dibuja el corte

		progressDialog->close(); // cierra barra de progreso
	}
}

void MainWindow::importPreset() {
	QString presetFile = QFileDialog::getOpenFileName(this, tr("Importar preset"), QDir::homePath()); // obtiene fichero

	if (presetFile != NULL) { // no se ha cancelado la operación
		std::string s = presetFile.toUtf8().constData();
		figura->getTransferFunction()->read(s); // lee función de transferencia

		// actualiza etiquetas
		ui->tfName->setText(QString::fromUtf8(figura->getTransferFunction()->getName().c_str()));
		ui->tfDescription->setText(QString::fromUtf8(figura->getTransferFunction()->getDescription().c_str()));

		// rangos por defecto
		colorTFChart->defaultRange(); 
		scalarTFChart->defaultRange();
		gradientTFChart->defaultRange();

		updateSliders(); // actualiza sliders
	}
}

void MainWindow::exportImageFromRenderWindow(vtkSmartPointer<vtkRenderWindow> renWin, const QString filename) {
	if (filename != NULL) { // el archivo se ha leído bien
		vtkSmartPointer<vtkWindowToImageFilter> filter = vtkSmartPointer<vtkWindowToImageFilter>::New(); // crea el filter
		filter->SetInput(renWin); // conecta el filter al widget
		filter->Update(); // actualiza el filter
		vtkSmartPointer<vtkImageWriter> writer;
		if (toUpper(getFileExtension(filename.toUtf8().constData())) == "PNG") { // comprueba si es PNG
			writer = vtkSmartPointer<vtkPNGWriter>::New(); // crea el writer de PNG
		} else { // si no, es JPG
			writer = vtkSmartPointer<vtkJPEGWriter>::New(); // crea el writer de JPG
		}
		writer->SetFileName(filename.toUtf8().constData()); // le pone el nombre que se había indicado
		writer->SetInputConnection(filter->GetOutputPort()); // conecta el writer con el filter
		writer->Write(); // crea la imagen de salida
	}
}

void MainWindow::exportMeshToFile(const QString filename) {
	if (filename != NULL) { // el archivo se ha leído bien
		// lanza barra de progreso
		QPointer<QProgressBar> bar = new QProgressBar(0);
		QPointer<QProgressDialog> progressDialog = new QProgressDialog(0);
		progressDialog->setWindowTitle(QString("Extrayendo..."));
		progressDialog->setLabelText(QString::fromLatin1("Extrayendo la malla del modelo"));
		progressDialog->setWindowIcon(QIcon(":/icons/3DCurator.png"));
		progressDialog->setWindowFlags(progressDialog->windowFlags() & ~Qt::WindowCloseButtonHint);
		progressDialog->setCancelButton(0);
		progressDialog->setBar(bar);
		progressDialog->show();
		bar->close();
		QApplication::processEvents();

		vtkSmartPointer<vtkMarchingCubes> surface = vtkSmartPointer<vtkMarchingCubes>::New();
		surface->SetInputData(figura->getImageData()); // usa los datos del volumen para hacer marching cubes
		surface->UpdateInformation(); // actualiza datos
		surface->ComputeScalarsOn(); // computa escalares
		surface->ComputeGradientsOn(); // computa gradientes
		surface->ComputeNormalsOn(); // computa normales
		surface->SetValue(0, figura->getIsoValue()); // establece valor de isosuperfice

		vtkSmartPointer<vtkPolyData> marched = vtkSmartPointer<vtkPolyData>::New();
		surface->Update(); // actualiza marching cubes
		marched->DeepCopy(surface->GetOutput()); // copia el resultado en un PolyData

		vtkSmartPointer<vtkDecimatePro> decimator = vtkSmartPointer<vtkDecimatePro>::New();
		decimator->SetInputData(marched); // la salida del polyData es la entrada para el reductor
		decimator->SetTargetReduction(0.5); // factor de reducción
		decimator->SetPreserveTopology(true); // preserva topología
		decimator->Update(); // actualiza reductor

		vtkSmartPointer<vtkSmoothPolyDataFilter> smoother = vtkSmartPointer<vtkSmoothPolyDataFilter>::New();
		smoother->SetInputData(decimator->GetOutput()); // la salida del reductor es la entrada del smoother
		smoother->SetNumberOfIterations(5); // número de iteraciones
		smoother->SetFeatureAngle(60); // ángulo para detectar sharp edge
		smoother->SetRelaxationFactor(0.05); // factor de relajación para el laplacian smoothing
		smoother->FeatureEdgeSmoothingOff(); // no suaviza aristas
		smoother->Update(); // actualiza smoother

		vtkSmartPointer<vtkPolyData> mesh = vtkSmartPointer<vtkPolyData>::New();
		mesh->ShallowCopy(smoother->GetOutput()); // la salida del smoother es la entrada de la malla final

		vtkSmartPointer<vtkSTLWriter> stlWriter = vtkSmartPointer<vtkSTLWriter>::New();
		stlWriter->SetFileName(filename.toUtf8().constData()); // nombre donde se guardará la malla
		stlWriter->SetInputData(mesh); // malla
		stlWriter->Write(); // guarda

		progressDialog->close(); // cierra barra de progreso
	}
}

void MainWindow::exportPreset(const QString filename) {
	if (filename != NULL) { // el nombre del archivo es correcto
		// establece nombre y descripción de la GUI a la TF
		figura->getTransferFunction()->setName(ui->tfName->text().toUtf8().constData());
		figura->getTransferFunction()->setDescription(ui->tfDescription->text().toUtf8().constData());

		std::string s = filename.toUtf8().constData();
		figura->getTransferFunction()->write(s); // guarda el archivo
	}
}

QString MainWindow::getExportPresetFilename(const QString defaultFilename) {
	return QFileDialog::getSaveFileName(
		this, tr("Exportar preset"), QDir(QDir::homePath()).filePath(defaultFilename), "XML (*.xml)"); // obtiene fichero para guardar archivo XML
}

QString MainWindow::getExportImageFilename(const QString defaultFilename) {
	return QFileDialog::getSaveFileName(
		this, tr("Exportar imagen"), QDir(QDir::homePath()).filePath(defaultFilename), "PNG (*.png);;JPG (*.jpg)"); // obtiene fichero para guardar archivo PNG o JPG
}

QString MainWindow::getExportMeshFilename(const QString defaultFilename) {
	return QFileDialog::getSaveFileName(
		this, tr("Exportar malla"), QDir(QDir::homePath()).filePath(defaultFilename), "STL (*.stl)"); // obtiene fichero para guardar archivo STL
}

void MainWindow::enablePlane() {
	plano->enable(true); // habilita el plano
	QIcon icon(":/icons/eye-slash.png");
	ui->enableDisablePlane->setIcon(icon); // cambia el icono
	showPlane = true; // flag del plano true
}

void MainWindow::disablePlane() {
	plano->enable(false); // deshabilita el plano
	QIcon icon(":/icons/eye.png");
	ui->enableDisablePlane->setIcon(icon); // cambia el icono
	showPlane = false; // flag del plano false
}

void MainWindow::exportMesh() {
	if (figura->getLoaded()) { // hay un volumen
		exportMeshToFile(getExportMeshFilename("Mesh")); // exporta malla
	} else {
		launchWarningNoVolume(); // lanza mensaje informando que no hay volumen
	}
}

void MainWindow::updateMesh() {
	if (figura->getLoaded()) { // hay un volumen
		// lanza barra de progreso
		QPointer<QProgressBar> bar = new QProgressBar(0);
		QPointer<QProgressDialog> progressDialog = new QProgressDialog(0);
		progressDialog->setWindowTitle(QString("Actualizando..."));
		progressDialog->setLabelText(QString::fromLatin1("Generando el modelo con la isosuperficie especificada"));
		progressDialog->setWindowIcon(QIcon(":/icons/3DCurator.png"));
		progressDialog->setWindowFlags(progressDialog->windowFlags() & ~Qt::WindowCloseButtonHint);
		progressDialog->setCancelButton(0);
		progressDialog->setBar(bar);
		progressDialog->show();
		bar->close();
		QApplication::processEvents();

		figura->createMesh(); // actualiza la malla
		meshRen->Render(); // renderiza

		progressDialog->close(); // cierra barra de progreso

	} else {
		launchWarningNoVolume(); // lanza mensaje informando que no hay volumen
	}
}

void MainWindow::enableDisablePlane() {
	if (showPlane) {
		disablePlane(); // plano activo --> deshabilita
	} else {
		enablePlane(); // si no --> habilita
	}
	renderVolume(); // renderiza volumen
}

void MainWindow::axialPlane() {
	if (figura->getLoaded()) { // hay un volumen
		plano->setAxial(); // cambia posición del plano
		renderVolume(); // renderiza volumen
		renderSlice(); // renderiza corte
	} else {
		launchWarningNoVolume(); // lanza mensaje informando que no hay volumen
	}
}

void MainWindow::coronalPlane() {
	if (figura->getLoaded()) { // hay un volumen
		plano->setCoronal(); // cambia posición del plano
		renderVolume(); // renderiza volumen
		renderSlice(); // renderiza corte
	} else {
		launchWarningNoVolume(); // lanza mensaje informando que no hay volumen
	}
}

void MainWindow::sagitalPlane() {
	if (figura->getLoaded()) { // hay un volumen
		plano->setSagital(); // cambia posición del plano
		renderVolume(); // renderiza volumen
		renderSlice(); // renderiza corte
	} else {
		launchWarningNoVolume(); // lanza mensaje informando que no hay volumen
	}
}

void MainWindow::deleteVolumeParts() {
	if (deleting) { // está borrando
		deleting = false; // cambia flag de borrado
		setBackgroundColor(volumeRen, volumeBackground.redF(), volumeBackground.greenF(), volumeBackground.blueF()); // cambia el color de fondo del widget
		ui->volumeWidget->GetRenderWindow()->GetInteractor()->SetInteractorStyle(volumeStyle); // cambia el interactor
	} else { // no está borrando
		deleting = true; // cambia flag de borrado
		setBackgroundColor(volumeRen, volumeDeletingBackground.redF(), volumeDeletingBackground.greenF(), volumeDeletingBackground.blueF()); // cambia el color de fondo del widget
		ui->volumeWidget->GetRenderWindow()->GetInteractor()->SetInteractorStyle(deleterStyle); // cambia el interactor
	}
	plano->getPlane()->UpdatePlacement(); // actualiza el plano
	renderVolume(); // renderiza volumen
	renderSlice(); // renderiza corte
}

void MainWindow::importCompletePreset() {
	QFile file(":/presets/ct-woodsculpture.xml");
	loadDefaultPreset(&file); // carga preset
	renderVolume(); // renderiza volumen 
}

void MainWindow::importWoodPreset() {
	QFile file(":/presets/ct-onlywood.xml");
	loadDefaultPreset(&file); // carga preset
	renderVolume(); // renderiza volumen
}

void MainWindow::importStuccoPreset() {
	QFile file(":/presets/ct-onlystucco.xml");
	loadDefaultPreset(&file); // carga preset
	renderVolume(); // renderiza volumen
}

void MainWindow::importMetalPreset() {
	QFile file(":/presets/ct-onlymetal.xml");
	loadDefaultPreset(&file); // carga preset
	renderVolume(); // renderiza volumen
}

void MainWindow::addRule(const int type) {
	if (rules.size() < RULES_LIMIT) { // no se ha alcanzado el límite de reglas
		std::string id;
		QListWidgetItem *item = new QListWidgetItem(0); // crea item
		switch (type) {
			case VOLUME_RULE: // regla de volumen
				volumeRuleCounter++; // aumenta contador
				id = "Regla " + std::to_string(volumeRuleCounter); // nombre de la regla
				item->setText(id.c_str()); // actualiza el texto del item
				item->setFont(itemListEnabled); // actualiza la fuente del item
				ui->volumeRulesList->addItem(item); // añade item
				ui->volumeRulesList->setCurrentItem(item); // pasa a ser el item activo
				rules[item] = vtkSmartPointer<vtkDistanceWidget>::New(); // crea la regla
				rules[item]->SetInteractor(ui->volumeWidget->GetInteractor()); // conecta la regla para medir con el interactor de los cortes
				break;
			case SLICE_RULE: // regla de corte
				sliceRuleCounter++; // aumenta contador
				id = "Regla " + std::to_string(sliceRuleCounter); // nombre de la regla
				item->setText(id.c_str()); // actualiza el texto del item
				item->setFont(itemListEnabled); // actualiza la fuente del item
				ui->sliceRulesList->addItem(item); // añade item
				ui->sliceRulesList->setCurrentItem(item); // pasa a ser el item activo
				rules[item] = vtkSmartPointer<vtkDistanceWidget>::New(); // crea la regla
				rules[item]->SetInteractor(ui->slicesWidget->GetInteractor()); // conecta la regla para medir con el interactor de los cortes
				break;
		}
		rules[item]->CreateDefaultRepresentation(); // usa la representación por defecto
		static_cast<vtkDistanceRepresentation *>(rules[item]->GetRepresentation())->SetLabelFormat("%-#6.3g mm"); // cambia el formato de la etiqueta
		rules[item]->On(); // habilita regla
	} else {
		launchWarningTooManyRules(); // lanza mensaje informando que se ha alcanzado el máximo número de reglas
	}
}

void MainWindow::deleteRule(const int type) {
	switch (type) {
		case VOLUME_RULE: // regla de volumen
			if (ui->volumeRulesList->currentItem() != NULL) { // hay una regla seleccionada
				rules.erase(ui->volumeRulesList->currentItem()); // borra regla del map
				delete ui->volumeRulesList->currentItem(); // borra item
				renderVolume(); // renderiza volumen
				if (ui->volumeRulesList->count() == 0) { // no ha más reglas
					volumeRuleCounter = 0; // resetea contador
				}
			} else {
				launchWarningNoRule(); // lanza mensaje informando que no hay regla seleccionada
			}
			break;
		case SLICE_RULE: // regla de corte
			if (ui->sliceRulesList->currentItem() != NULL) { // hay una regla seleccionada
				rules.erase(ui->sliceRulesList->currentItem()); // borra regla del map
				delete ui->sliceRulesList->currentItem(); // borra item
				renderSlice(); // renderiza corte
				if (ui->sliceRulesList->count() == 0) { // no ha más reglas
					sliceRuleCounter = 0; // resetea contador
				}
			} else {
				launchWarningNoRule(); // lanza mensaje informando que no hay regla seleccionada
			}
			break;
	}
}

void MainWindow::enableDisableRule(const int type) {
	switch (type) {
		case VOLUME_RULE: // regla de volumen
			if (ui->volumeRulesList->currentItem() != NULL) { // hay una regla seleccionada
				if (ui->volumeRulesList->currentItem()->font() == itemListDisabled) {
					enableRule(type); // habilita regla
					ui->volumeRulesList->currentItem()->setFont(itemListEnabled); // fuente de regla habilitada
				} else {
					disableRule(type); // deshabilita regla
					ui->volumeRulesList->currentItem()->setFont(itemListDisabled); // fuente de regla deshabilitada
				}
			} else {
				launchWarningNoRule(); // lanza mensaje informando que no hay regla seleccionada
			}
			break;
		case SLICE_RULE: // regla de corte
			if (ui->sliceRulesList->currentItem() != NULL) { // hay una regla seleccionada
				if (ui->sliceRulesList->currentItem()->font() == itemListDisabled) {
					enableRule(type); // habilita regla
					ui->sliceRulesList->currentItem()->setFont(itemListEnabled); // fuente de regla habilitada
				} else {
					disableRule(type); // deshabilita regla
					ui->sliceRulesList->currentItem()->setFont(itemListDisabled); // fuente de regla deshabilitada
				}
			} else {
				launchWarningNoRule(); // lanza mensaje informando que no hay regla seleccionada
			}
			break;
	}
}

void MainWindow::enableRule(const int type) {
	switch (type) {
		case VOLUME_RULE: // regla de volumen
			if (ui->volumeRulesList->currentItem() != NULL) { // hay una regla seleccionada
				rules[ui->volumeRulesList->currentItem()]->On(); // habilita
			} else {
				launchWarningNoRule(); // lanza mensaje informando que no hay regla seleccionada
			}
			break;
		case SLICE_RULE: // regla de corte
			if (ui->sliceRulesList->currentItem() != NULL) { // hay una regla seleccionada
				rules[ui->sliceRulesList->currentItem()]->On(); // habilita
			} else {
				launchWarningNoRule(); // lanza mensaje informando que no hay regla seleccionada
			}
			break;
	}
}

void MainWindow::disableRule(const int type) {
	switch (type) {
		case VOLUME_RULE: // regla de volumen
			if (ui->volumeRulesList->currentItem() != NULL) { // hay una regla seleccionada
				rules[ui->volumeRulesList->currentItem()]->Off(); // deshabilita
			} else {
				launchWarningNoRule(); // lanza mensaje informando que no hay regla seleccionada
			}
			break;
		case SLICE_RULE: // regla de corte
			if (ui->sliceRulesList->currentItem() != NULL) { // hay una regla seleccionada
				rules[ui->sliceRulesList->currentItem()]->Off(); // deshabilita
			} else {
				launchWarningNoRule(); // lanza mensaje informando que no hay regla seleccionada
			}
			break;
	}
}

void MainWindow::clearAllRules() {
	rules.clear(); // limpia el map

	// limpia las listas de la GUI
	ui->sliceRulesList->clear();
	ui->volumeRulesList->clear();

	// resetea contadores
	sliceRuleCounter = 0;
	volumeRuleCounter = 0;
}

void MainWindow::changeBackgroundColor(const int widget) {
	QColor color;
	switch (widget) {
		case VOLUME_BACKGROUND: // color del widget del volumen
			color = QColorDialog::getColor(volumeBackground);
			if (color.isValid()) { // no se ha cancelado el dialogo
				volumeBackground = color; // actualiza color
				if (!deleting) { // si no está borrando
					setBackgroundColor(volumeRen, volumeBackground.redF(), volumeBackground.greenF(), volumeBackground.blueF()); // cambia color de fondo
					renderVolume(); // renderiza el volumen
				}
				ui->volumeBackground->setStyleSheet("background-color: " + volumeBackground.name()); // cambia color del botón
			}
			break;
		case VOLUME_DELETING_BACKGROUND: // color del widget del volumen al borrar
			color = QColorDialog::getColor(volumeDeletingBackground);
			if (color.isValid()) { // no se ha cancelado el dialogo
				volumeDeletingBackground = color; // actualiza el color
				if (deleting) { // si está borrando
					setBackgroundColor(volumeRen, volumeDeletingBackground.redF(), volumeDeletingBackground.greenF(), volumeDeletingBackground.blueF()); // cambia color de fondo
					renderVolume(); // renderiza el volumen
				}
				ui->volumeDeletingBackground->setStyleSheet("background-color: " + volumeDeletingBackground.name()); // cambia color del botón
			}
			break;
		case MESH_BACKGROUND: // color del widget de la malla
			color = QColorDialog::getColor(meshBackground);
			if (color.isValid()) { // no se ha cancelado el dialogo 
				meshBackground = color; // actualiza color
				setBackgroundColor(meshRen, meshBackground.redF(), meshBackground.greenF(), meshBackground.blueF()); // cambia color de fondo
				renderMesh(); // renderiza malla
				ui->meshBackground->setStyleSheet("background-color: " + meshBackground.name()); // cambia color del botón
			}
			break;
	}
}

void MainWindow::restoreBackgroundColors() {
	defaultBackgroundColors(); // colores por defecto
	if (deleting) { // si se está borrando
		setBackgroundColor(volumeRen, volumeDeletingBackground.redF(), volumeDeletingBackground.greenF(), volumeDeletingBackground.blueF()); // color de widget de volumen es el de borrado
	} else { // si no
		setBackgroundColor(volumeRen, volumeBackground.redF(), volumeBackground.greenF(), volumeBackground.blueF()); // color de widget de volumen es el normal
	}
	setBackgroundColor(meshRen, meshBackground.redF(), meshBackground.greenF(), meshBackground.blueF()); // color de widget de malla
	renderVolume(); // renderiza volumen
	renderMesh(); // renderiza malla
}
void MainWindow::launchWarning(const std::string message) {
	// crea mensaje de advertencia
	QPointer<QMessageBox> confirmBox = new QMessageBox(0);
	confirmBox->setWindowTitle(QString::fromLatin1("Advertencia"));
	confirmBox->setWindowIcon(QIcon(":/icons/3DCurator.png"));
	confirmBox->setIcon(QMessageBox::Information);
	confirmBox->setText(QString::fromLatin1(message.c_str()));
	confirmBox->setStandardButtons(QMessageBox::Ok);
	confirmBox->exec(); // y lo ejecuta
}

void MainWindow::launchWarningNoVolume() {
	launchWarning("Hace falta cargar un modelo antes");
}

void MainWindow::launchWarningNoRule() {
	launchWarning("Seleccione una regla antes");
}

void MainWindow::launchWarningTooManyRules() {
	launchWarning("Se ha alcanzado el máximo número de reglas permitidas");
}

//---------------------------------------------------------------------------------------------------------------------------------
// Eventos GUI - MENÚ
//---------------------------------------------------------------------------------------------------------------------------------

void MainWindow::on_actionOpenDICOM_triggered() {
	importDICOM();
}

void MainWindow::on_actionExportVolumeImage_triggered() {
	exportImageFromRenderWindow(
		ui->volumeWidget->GetRenderWindow(), getExportImageFilename(QString::fromStdString(getCurrentDate())));
}

void MainWindow::on_actionExportSliceImage_triggered() {
	exportImageFromRenderWindow(
		ui->slicesWidget->GetRenderWindow(), getExportImageFilename(QString::fromStdString(getCurrentDate())));
}

void MainWindow::on_actionExit_triggered() {
	// crea mensaje de advertencia
	QPointer<QMessageBox> confirmBox = new QMessageBox(0);
	confirmBox->setWindowTitle(QString::fromLatin1("Advertencia"));
	confirmBox->setWindowIcon(QIcon(":/icons/3DCurator.png"));
	confirmBox->setIcon(QMessageBox::Information);
	confirmBox->setText(QString::fromLatin1("¿Seguro que desea salir?"));
	confirmBox->setStandardButtons(QMessageBox::Yes | QMessageBox::No);
	confirmBox->button(QMessageBox::Yes)->setText(QString::fromLatin1("Sí"));
	confirmBox->button(QMessageBox::No)->setText(QString::fromLatin1("No"));
	if (confirmBox->exec() == QMessageBox::Yes) { // lo lanza
		exit(0); // si la respuesta es afirmativa se sale
	}
}

void MainWindow::on_actionEnableDisablePlane_triggered() {
	enableDisablePlane();
}

void MainWindow::on_actionSagitalPlane_triggered() {
	sagitalPlane();
}

void MainWindow::on_actionAxialPlane_triggered() {
	axialPlane();
}

void MainWindow::on_actionCoronalPlane_triggered() {
	coronalPlane();
}

void MainWindow::on_actionImportPreset_triggered() {
	importPreset();
}

void MainWindow::on_actionCompletePreset_triggered() {
	importCompletePreset();
}

void MainWindow::on_actionWoodPreset_triggered() {
	importWoodPreset();
}

void MainWindow::on_actionStuccoPreset_triggered() {
	importStuccoPreset();
}

void MainWindow::on_actionMetalPreset_triggered() {
	importMetalPreset();
}

void MainWindow::on_actionExportPreset_triggered() {
	exportPreset(getExportPresetFilename(ui->tfName->text()));
}

void MainWindow::on_actionDeleteVolumeParts_triggered() {
	deleteVolumeParts();
}

void MainWindow::on_actionExtractMesh_triggered() {
	exportMesh();
}

void MainWindow::on_actionWoodMesh_triggered() {
	ui->isoValueSlider->setValue(WOOD_ISOVALUE);
}

void MainWindow::on_actionStuccoMesh_triggered() {
	ui->isoValueSlider->setValue(STUCCO_ISOVALUE);
}

void MainWindow::on_actionMetalMesh_triggered() {
	ui->isoValueSlider->setValue(METAL_ISOVALUE);
}

//---------------------------------------------------------------------------------------------------------------------------------
// Eventos GUI - BOTONES
//---------------------------------------------------------------------------------------------------------------------------------

void MainWindow::on_openDICOM_pressed() {
	importDICOM();
}

void MainWindow::on_axialPlane_pressed() {
	axialPlane();
}

void MainWindow::on_coronalPlane_pressed() {
	coronalPlane();
}

void MainWindow::on_sagitalPlane_pressed() {
	sagitalPlane();
}

void MainWindow::on_exportSliceImage_pressed() {
	exportImageFromRenderWindow(
		ui->slicesWidget->GetRenderWindow(), getExportImageFilename(QString::fromStdString(getCurrentDate())));
}

void MainWindow::on_exportVolumeImage_pressed() {
	exportImageFromRenderWindow(
		ui->volumeWidget->GetRenderWindow(), getExportImageFilename(QString::fromStdString(getCurrentDate())));
}

void MainWindow::on_importPreset_pressed() {
	importPreset();
}

void MainWindow::on_exportPreset_pressed() {
	exportPreset(getExportPresetFilename(ui->tfName->text()));
}

void MainWindow::on_restoreMaterial_pressed() {
	defaultMaterial();
}

void MainWindow::on_updateProperties_pressed() {
	updateMaterial();
	renderVolume();
}

void MainWindow::on_completePreset_pressed() {
	importCompletePreset();
}

void MainWindow::on_woodPreset_pressed() {
	importWoodPreset();
}

void MainWindow::on_stuccoPreset_pressed() {
	importStuccoPreset();
}

void MainWindow::on_metalPreset_pressed() {
	importMetalPreset();
}

void MainWindow::on_extractMesh_pressed() {
	exportMesh();
}

void MainWindow::on_extractMeshWood_pressed() {
	ui->isoValueSlider->setValue(WOOD_ISOVALUE);
}

void MainWindow::on_extractMeshStucco_pressed() {
	ui->isoValueSlider->setValue(STUCCO_ISOVALUE);
}

void MainWindow::on_extractMeshMetal_pressed() {
	ui->isoValueSlider->setValue(METAL_ISOVALUE);
}

void MainWindow::on_enableDisablePlane_pressed() {
	enableDisablePlane();
}

void MainWindow::on_deleteVolumeParts_pressed() {
	deleteVolumeParts();
}

void MainWindow::on_addSliceRule_pressed() {
	addRule(1);
}

void MainWindow::on_addVolumeRule_pressed() {
	addRule(0);
}

void MainWindow::on_deleteSliceRule_pressed() {
	deleteRule(1);
}

void MainWindow::on_deleteVolumeRule_pressed() {
	deleteRule(0);
}

void MainWindow::on_enableDisableSliceRule_pressed() {
	enableDisableRule(1);
}

void MainWindow::on_enableDisableVolumeRule_pressed() {
	enableDisableRule(0);
}

void MainWindow::on_volumeBackground_pressed() {
	changeBackgroundColor(0);
}

void MainWindow::on_volumeDeletingBackground_pressed() {
	changeBackgroundColor(1);
}

void MainWindow::on_meshBackground_pressed() {
	changeBackgroundColor(2);
}

void MainWindow::on_restoreBackgrounds_pressed() {
	restoreBackgroundColors();
}

//---------------------------------------------------------------------------------------------------------------------------------
// Eventos GUI - SLIDERS
//---------------------------------------------------------------------------------------------------------------------------------

void MainWindow::on_colorTFMaxSlider_valueChanged() {
	colorTFChart->setRange((double)ui->colorTFMinSlider->value(), (double)ui->colorTFMaxSlider->value());
	ui->colorTFMinSlider->setMaximum(ui->colorTFMaxSlider->value() - 1);
}

void MainWindow::on_colorTFMinSlider_valueChanged() {
	colorTFChart->setRange((double)ui->colorTFMinSlider->value(), (double)ui->colorTFMaxSlider->value());
	ui->colorTFMaxSlider->setMinimum(ui->colorTFMinSlider->value() + 1);
}

void MainWindow::on_gradientTFMaxSlider_valueChanged() {
	gradientTFChart->setRange((double)ui->gradientTFMinSlider->value(), (double)ui->gradientTFMaxSlider->value());
	ui->gradientTFMinSlider->setMaximum(ui->gradientTFMaxSlider->value() - 1);
}

void MainWindow::on_gradientTFMinSlider_valueChanged() {
	gradientTFChart->setRange((double)ui->gradientTFMinSlider->value(), (double)ui->gradientTFMaxSlider->value());
	ui->gradientTFMaxSlider->setMinimum(ui->gradientTFMinSlider->value() + 1);
}

void MainWindow::on_scalarTFMaxSlider_valueChanged() {
	scalarTFChart->setRange((double)ui->scalarTFMinSlider->value(), (double)ui->scalarTFMaxSlider->value());
	ui->scalarTFMinSlider->setMaximum(ui->scalarTFMaxSlider->value() - 1);
}

void MainWindow::on_scalarTFMinSlider_valueChanged() {
	scalarTFChart->setRange((double)ui->scalarTFMinSlider->value(), (double)ui->scalarTFMaxSlider->value());
	ui->scalarTFMaxSlider->setMinimum(ui->scalarTFMinSlider->value() + 1);
}

void MainWindow::on_isoValueSlider_valueChanged() {
	figura->setIsoValue(ui->isoValueSlider->value());
	updateMesh();
}