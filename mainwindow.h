#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QFile>
#include <QProgressDialog>
#include <QProgressBar>
#include <QPointer>
#include <QListWidgetItem>

#include <sstream>
#include <map>

#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkImageViewer2.h>
#include <vtkSmartPointer.h>
#include <vtkImageMapToWindowLevelColors.h>
#include <vtkLookupTable.h>
#include <vtkWindowToImageFilter.h>
#include <vtkImageWriter.h>
#include <vtkPNGWriter.h>
#include <vtkJPEGWriter.h>
#include <vtkSTLWriter.h>
#include <vtkDistanceWidget.h>
#include <vtkDistanceRepresentation.h>
#include <vtkDecimatePro.h>
#include <vtkSmoothPolyDataFilter.h>
#include <vtkPolyDataConnectivityFilter.h>

#include "measures.h"
#include "utils.h"
#include "figura.h"
#include "plano.h"
#include "interactorStyleImage.h"
#include "interactorStyleDeleter.h"
#include "colorTFChart.h"
#include "opacityTFChart.h"

#define VOLUME_RULE 0
#define SLICE_RULE 1
#define VOLUME_BACKGROUND 0
#define VOLUME_DELETING_BACKGROUND 1
#define MESH_BACKGROUND 2

namespace Ui {
    class MainWindow;
}

/**
* @class MainWIndow
* Clase con la ventana principal
*/
class MainWindow : public QMainWindow {
    Q_OBJECT

public:
	/**
	 * Constructor
	 */
	explicit MainWindow(QWidget *parent = 0);

	/*
	 * Destructor
	 */
    ~MainWindow();

private slots:
	// eventos GUI
	void on_actionOpenDICOM_triggered();
	void on_actionExportVolumeImage_triggered();
	void on_actionExportSliceImage_triggered();
	void on_actionExit_triggered();
	void on_actionEnableDisablePlane_triggered();
	void on_actionSagitalPlane_triggered();
	void on_actionAxialPlane_triggered();
	void on_actionCoronalPlane_triggered();
	void on_actionImportPreset_triggered();
	void on_actionExportPreset_triggered();
	void on_actionCompletePreset_triggered();
	void on_actionWoodPreset_triggered();
	void on_actionStuccoPreset_triggered();
	void on_actionMetalPreset_triggered();
	void on_actionDeleteVolumeParts_triggered();
	void on_actionExtractMesh_triggered();
	void on_actionWoodMesh_triggered();
	void on_actionStuccoMesh_triggered();
	void on_actionMetalMesh_triggered();

	void on_openDICOM_pressed();
	void on_axialPlane_pressed();
	void on_coronalPlane_pressed();
	void on_sagitalPlane_pressed();
	void on_exportSliceImage_pressed();
	void on_exportVolumeImage_pressed();
	void on_importPreset_pressed();
	void on_exportPreset_pressed();
	void on_restoreMaterial_pressed();
	void on_updateProperties_pressed();
	void on_completePreset_pressed();
	void on_woodPreset_pressed();
	void on_stuccoPreset_pressed();
	void on_metalPreset_pressed();
	void on_extractMesh_pressed();
	void on_extractMeshWood_pressed();
	void on_extractMeshStucco_pressed();
	void on_extractMeshMetal_pressed();
	void on_enableDisablePlane_pressed();
	void on_deleteVolumeParts_pressed();
	void on_addSliceRule_pressed();
	void on_addVolumeRule_pressed();
	void on_deleteSliceRule_pressed();
	void on_deleteVolumeRule_pressed();
	void on_enableDisableSliceRule_pressed();
	void on_enableDisableVolumeRule_pressed();
	void on_volumeBackground_pressed();
	void on_volumeDeletingBackground_pressed();
	void on_meshBackground_pressed();
	void on_restoreBackgrounds_pressed();

	void on_colorTFMaxSlider_valueChanged();
	void on_colorTFMinSlider_valueChanged();
	void on_gradientTFMaxSlider_valueChanged();
	void on_gradientTFMinSlider_valueChanged();
	void on_scalarTFMaxSlider_valueChanged();
	void on_scalarTFMinSlider_valueChanged();
	void on_isoValueSlider_valueChanged();

	/**
	 * Establece un color a un Renderer
	 * @param	ren Renderer al que se le quiere cambiar el color
	 * @param	r	Componente roja
	 * @param	g	Componente verde
	 * @param	b	Componente azul
	 */
	void setBackgroundColor(vtkSmartPointer<vtkRenderer> ren, float r, float g, float b);

	/**
	 * Conecta los componentes de VTK con las interfaces
	 */
	void connectComponents();

	/**
	 * Añade el volumen a su respectivo visor
	 */
	void drawVolume();

	/**
	 * Añade la malla a su respectivo visor
	 */
	void drawMesh();

	/**
	 * Elimina el volumen de su respectivo visor
	 */
	void removeVolume();

	/**
	 * Elimina la malla de su respectivo visor
	 */
	void removeMesh();

	/**
	 * Renderiza la ventana del volumen y el plano
	 */
	void renderVolume();

	/**
	 * Renderiza la ventana de la malla
	 */
	void renderMesh();

	/**
	 * Renderiza la ventana del corte producidor por el plano en el volumen
	 */
	void renderSlice();

	/**
	 * Asigna una función de trasnferencia por defecto
	 */
	void defaultTF();

	/**
	 * Asigna un material por defecto
	 */
	void defaultMaterial();

	/**
	 * Asigna colores de fondo por defecto
	 */
	void defaultBackgroundColors();

	/**
	 * Coloca el plano en una posición por defecto
	 */
	void defaultPlanePosition();

	/**
	 * Actualiza el material
	 */
	void updateMaterial();

	/**
	 * Actualiza los sliders dándole los valores según la función de transferencia
	 */
	void updateSliders();

	/**
	 * Importa archivos DICOM para representarlos
	 */
	void importDICOM();

	/**
	 * Importa un preset de una función de transferencia
	 */
	void importPreset();

	/**
	 * Carga un preset de los que por defecto incluye el programa
	 * @param	file	Archivo con el preset que se va a cargar
	 */
	void loadDefaultPreset(QFile *file);

	/**
	 * Exporta una imagen de un Render Window
	 * @param	renWin		RenderWindow del que se quiere extraer una imagen
	 * @param	filename	Nombre del archivo de salida
	 */
	void exportImageFromRenderWindow(vtkSmartPointer<vtkRenderWindow> renWin, const QString filename);

	/**
	 * Exporta el preset
	 * @param	filename	Nombre del archivo de salida
	 */
	void exportPreset(const QString filename);

	/**
	 * Exporta la malla a un archivo
	 * @param	filename	Nombre del archivo de salida
	 */
	void exportMeshToFile(const QString filename);

	/**
	 * Exporta la malla
	 */
	void exportMesh();

	/**
	 * Actualiza la malla
	 */
	void updateMesh();

	/**
	 * Obtiene el nombre del archivo de salida para exportar una imagen
	 * @param	defaultFilename		Nombre que se dará por defecto (fecha y hora)
	 * @return	Archivo de salida
	 */
	QString getExportImageFilename(const QString defaultFilename);

	/**
	 * Obtiene el nombre del archivo de salida para exportar un preset
	 * @param	defaultFilename		Nombre que se dará por defecto (nombre de la función de transferencia)
	 * @return	Archivo de salida
	 */
	QString getExportPresetFilename(const QString defaultFilename);

	/**
	 * Obtiene el nombre del archivo de salida para exportar una malla
	 * @param	defaultFilename		Nombre que se dará por defecto
	 * @return	Archivo de salida
	 */
	QString getExportMeshFilename(const QString defaultFilename);

	/**
	 * Habilita el plano
	 */
	void enablePlane();

	/**
	 * Deshabilita el plano
	 */
	void disablePlane();

	/**
	 * Habilita o deshabilita el plano
	 */
	void enableDisablePlane();

	/**
	 * Coloca el plano en posición axial
	 */
	void axialPlane();

	/**
	 * Coloca el plano en posición axial
	 */
	void coronalPlane();

	/**
	 * Coloca el plano en posición axial
	 */
	void sagitalPlane();

	/**
	 * Entra o sale del modo de borrado donde borra partes del volumen
	 */
	void deleteVolumeParts();

	/**
	 * Importa el preset para mostrar la figura completa
	 */
	void importCompletePreset();

	/**
	 * Importa el preset para mostrar la madera
	 */
	void importWoodPreset();

	/**
	 * Importa el preset para mostrar el estuco
	 */
	void importStuccoPreset();

	/**
	 * Importa el preset para mostrar el metal
	 */
	void importMetalPreset();

	/**
	 * Añade una nueva regla para medir
	 * @param	type	0: Figura 3D y 1: Cortes
	 */
	void addRule(const int type);

	/**
	 * Elimina la regla seleccionada
	 * @param	type	0: Figura 3D y 1: Cortes
	 */
	void deleteRule(const int type);

	/**
	 * Habilita o deshabilita la regla seleccionada
	 * @param	type	0: Figura 3D y 1: Cortes
	 */
	void enableDisableRule(const int type);

	/**
	 * Habilita la regla
	 * @param	type	0: Figura 3D y 1: Cortes
	 */
	void enableRule(const int type);

	/**
	 * Deshabilita la regla
	 * @param	type	0: Figura 3D y 1: Cortes
	 */
	void disableRule(const int type);

	/**
	 * Borra todas las reglas
	 */
	void clearAllRules();

	/**
	 * Restaura los colores por defecto
	 */
	void restoreBackgroundColors();

	/**
	 * Lanza un mensaje informando
	 * @param	message	Mensaje que se mostrará
	 */
	void launchWarning(const std::string message);

	/**
	 * Lanza un mensaje informando que antes se necesita importar un volumen
	 */
	void launchWarningNoVolume();

	/**
	 * Lanza un mensaje informando que antes se necesita seleccionar una regla
	 */
	void launchWarningNoRule();

	/**
	 * Lanza un mensaje informando que antes se necesita seleccionar una regla
	 */
	void launchWarningTooManyRules();

	/**
	 * Cambia el color de una ventana
	 * @param	widget	0: Figura 3D, 1: Figura 3D (borrado), 2: Malla
	 */
	void changeBackgroundColor(const int widget);

private:
	Ui::MainWindow *ui; /**< Puntero a la interfaz gráfica */

	QFont itemListEnabled; /**< Fuente de los elementos de la lista de reglas habilitados */
	QFont itemListDisabled; /**< Fuente de los elementos de la lista de reglas deshabilitados */

	QColor volumeBackground; /**< Color de fondo del widget del volumen */
	QColor volumeDeletingBackground; /**< Color de fondo del widget del volumen al borrar */
	QColor meshBackground; /**< Color de fondo del widget de la malla */

	Figura *figura; /**< Puntero a la figura */
	Plano *plano; /**< Puntero al plano */

	ColorTFChart *colorTFChart; /**< Puntero a la gráfica de la parte de color de la función de transferencia */
	OpacityTFChart *scalarTFChart; /**< Puntero a la gráfica de la parte de opacida escalar de la función de transferencia */
	OpacityTFChart *gradientTFChart; /**< Puntero a la gráfica de la parte de opacida gradiente de la función de transferencia */

	std::map<QListWidgetItem*, vtkSmartPointer<vtkDistanceWidget>> rules; /**< Almacén de reglas */

	vtkSmartPointer<vtkRenderer> volumeRen; /**< Puntero al Renderer donde estará el volumen y el plano de corte */
	vtkSmartPointer<vtkRenderer> meshRen; /**< Puntero al Renderer donde se visulizará la malla a extraer */
	vtkSmartPointer<vtkImageViewer2> sliceViewer; /**< Puntero al ImageViewer2 donde se verá el corte producido por el plano en el volumen */

	vtkSmartPointer<vtkInteractorStyleTrackballCamera> volumeStyle; /**< Estilo para la ventana donde se visualizará el volumen */
	vtkSmartPointer<InteractorStyleImage> sliceStyle; /**< Estilo para la ventana donde se visualizarán los cortes de la figura con el plano */
	vtkSmartPointer<InteractorStyleDeleter> deleterStyle; /**< Estilo para poder borrar en la ventana donde se visualizará el volumen */

	bool deleting; /**< Variable para ver si está en modo borrado o no */
	bool showPlane; /**< Mostrar el plano */
	int volumeRuleCounter; /**< Contador de índice de regla */
	int sliceRuleCounter; /**< Contador de índice de regla */
};

#endif // MAINWINDOW_H
