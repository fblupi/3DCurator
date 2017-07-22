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

#include "Util/Measures.h"
#include "Util/Utils.h"
#include "Core/Sculpture.h"
#include "Core/SlicePlane.h"
#include "Interactor/InteractorStyleImage.h"
#include "Interactor/InteractorStyleDeleter.h"
#include "Interactor/InteractorStyleSegmentation.h"
#include "Chart/ColorTFChart.h"
#include "Chart/OpacityTFChart.h"

#define VOLUME_RULE 0
#define SLICE_RULE 1
#define VOLUME_BACKGROUND 0
#define VOLUME_DELETING_BACKGROUND 1
#define MESH_BACKGROUND 2

namespace Ui {
    class MainWindow;
}

/**
 * @class MainWindow
 * Main window class
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
	// GUI events
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
	void on_actionFilter_triggered();

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
	void on_addRule_pressed();
	void on_deleteRule_pressed();
	void on_enableDisableRule_pressed();
	void on_volumeBackground_pressed();
	void on_volumeDeletingBackground_pressed();
	void on_meshBackground_pressed();
	void on_restoreBackgrounds_pressed();
	void on_segmentate_pressed();
	void on_filter_pressed();

	void on_colorTFMaxSlider_valueChanged();
	void on_colorTFMinSlider_valueChanged();
	void on_gradientTFMaxSlider_valueChanged();
	void on_gradientTFMinSlider_valueChanged();
	void on_scalarTFMaxSlider_valueChanged();
	void on_scalarTFMinSlider_valueChanged();
	void on_isoValueSlider_valueChanged();

	/**
	 * Set renderer color using RGB
	 * @param	ren	Renderer
	 * @param	r	Red
	 * @param	g	Green
	 * @param	b	Blue
	 */
	void setBackgroundColor(vtkSmartPointer<vtkRenderer> ren, float r, float g, float b);

	/**
	 * Connect components of the pipeline
	 */
	void connectComponents();

	/**
	 * Add volume to its viewer, reset camera and render it
	 */
	void drawVolume();

	/**
	 * Add mesh to its viewer, reset camera and render it
	 */
	void drawMesh();

	/**
	 * Remove volume from its viewer, reset camera and render void viewer
	 */
	void removeVolume();

	/**
	 * Remove volume from its viewer, reset camera and render void viewer
	 */
	void removeMesh();

	/**
	 * Render volume viewer
	 */
	void renderVolume();

	/**
	 * Render mesh viewer
	 */
	void renderMesh();

	/**
	 * Render slice viewer
	 */
	void renderSlice();

	/**
	 * Set default transfer function
	 */
	void defaultTF();

	/**
	 * Set default material
	 */
	void defaultMaterial();

	/**
	 * Set default viewers background colors
	 */
	void defaultBackgroundsColors();

	/**
	 * Set default plane position
	 */
	void defaultPlanePosition();

	/**
	 * Update material with GUI values
	 */
	void updateMaterial();

	/**
	 * Update sliders using transfer function bounds
	 */
	void updateSliders();

	/**
	 * Import DICOM files
	 */
	void importDICOM();

	/**
	 * Import transfer function preset
	 */
	void importPreset();

	/**
	 * Load one of the default presets
	 * @param	file	File with the preset that will be used
	 */
	void loadDefaultPreset(QFile *file);

	/**
	 * Export image from a render window
	 * @param	renWin		RenderWindow from which we will export the image
	 * @param	filename	Output filename
	 */
	void exportImageFromRenderWindow(vtkSmartPointer<vtkRenderWindow> renWin, const QString filename);

	/**
	 * Export preset of the current transfer function
	 * @param	filename	Output filename
	 */
	void exportPreset(const QString filename);

	/**
	 * Export Mesh to STL file
	 * @param	filename	Output filename
	 */
	void exportMeshToFile(const QString filename);

	/**
	 * Export mesh if volume is loaded
	 */
	void exportMesh();

	/**
	 * Update mesh from the current volume and isosurface value using marching cubes
	 */
	void updateMesh();

	/**
	 * Get exported image filename
	 * @param	defaultFilename	Default filename (date and hour)
	 * @return	Output filename
	 */
	QString getExportImageFilename(const QString defaultFilename);

	/**
	 * Get exported preset filename
	 * @param	defaultFilename	Default filename (transfer function name)
	 * @return	Output filename
	 */
	QString getExportPresetFilename(const QString defaultFilename);

	/**
	 * Get exported mesh filename
	 * @param	defaultFilename	Default filename
	 * @return	Output filename
	 */
	QString getExportMeshFilename(const QString defaultFilename);

	/**
	 * Show plane in viewer
	 */
	void enablePlane();

	/**
	 * Hide plane in viewer
	 */
	void disablePlane();

	/**
	 * Show or hide plane in viewer
	 */
	void enableDisablePlane();

	/**
	 * Set plane in axial poisition
	 */
	void axialPlane();

	/**
	 * Set plane in coronal position
	 */
	void coronalPlane();

	/**
	 * Set plane in sagital position
	 */
	void sagitalPlane();

	/**
	 * Enable or disable delete mode
	 */
	void deleteVolumeParts();

	/**
	 * Import all materials preset
	 */
	void importCompletePreset();

	/**
	 * Import wood materials preset
	 */
	void importWoodPreset();

	/**
	 * Import stucco materials preset
	 */
	void importStuccoPreset();

	/**
	 * Import metal materials preset
	 */
	void importMetalPreset();

	/**
	 * Add new rule to measure
	 */
	void addRule();

	/**
	 * Delete selected rule
	 */
	void deleteRule();

	/**
	 * Enable or disable selected rule
	 */
	void enableDisableRule();

	/**
	 * Enable selected rule
	 */
	void enableRule();

	/**
	 * Disable selected rule
	 */
	void disableRule();

	/**
	 * Delete all rules
	 */
	void clearAllRules();

	/**
	 * Restore default viewers background colors
	 */
	void restoreBackgroundsColors();

	/**
	 * Launch a warning message
	 * @param	message	Message that will be shown
	 */
	void launchWarning(const std::string message);

	/**
	 * Launch a warning message saying there is no volume loaded
	 */
	void launchWarningNoVolume();

	/**
	 * Launch a warning message saying there is no rule selected
	 */
	void launchWarningNoRule();

	/**
	 * Launch a warning message saying there are already too many rules
	 */
	void launchWarningTooManyRules();

	/**
	 * Change background color of a viewer
	 * @param	widget	0: 3D Model, 1: 3D Model (deleting), 2: Mesh
	 */
	void changeBackgroundColor(const int widget);

	/**
	 * Enable or disable segmentation mode
	 */
	void segmentateOnOff();

	/**
	 * Reduce noise with a gaussian filter
	 */
	void filter();

private:
	Ui::MainWindow *ui; /**< UI pointer */

	QFont itemListEnabled; /**< Font type for rule list elements enabled */
	QFont itemListDisabled; /**< Font type for rule list elements disabled */

	QColor volumeBackground; /**< Volume viewer background color */
	QColor volumeDeletingBackground; /**< Volume viewer (delete mode) background color */
	QColor meshBackground; /**< Mesh viewer background color */

	Sculpture *sculpture; /**< Sculpture pointer */
	SlicePlane *slicePlane; /**< Plane pointer */

	ColorTFChart *colorTFChart; /**< Color transfer function chart pointer */
	OpacityTFChart *scalarTFChart; /**< Scalar transfer function chart pointer */
	OpacityTFChart *gradientTFChart; /**< Gradient transfer function chart pointer */

	std::map<QListWidgetItem*, vtkSmartPointer<vtkDistanceWidget> > rules; /**< Rules container */

	vtkSmartPointer<vtkRenderer> volumeRen; /**< Volume and slice plane renderer pointer */
	vtkSmartPointer<vtkRenderer> meshRen; /**< Mesh renderer pointer */
	vtkSmartPointer<vtkImageViewer2> sliceViewer; /**< Slice viewer pointer */

	vtkSmartPointer<vtkInteractorStyleTrackballCamera> volumeStyle; /**< Volume viewer interaction style */
	vtkSmartPointer<InteractorStyleImage> sliceStyle; /**< Slice viewer interaction style */
	vtkSmartPointer<InteractorStyleDeleter> deleterStyle; /**< Volume viewer (delete mode) interaction style */
	vtkSmartPointer<InteractorStyleSegmentation> segmentationStyle; /**< Slice viewer (segmentation mode) interaction style */

	bool deleting; /**< Deleting mode enabled or disabled */
	bool segmentating; /**< Segmentating mode enabled or disabled */
	bool showPlane; /**< Show or hide plane */
	int sliceRuleCounter; /**< Number of slice rules */
};

#endif // MAINWINDOW_H
