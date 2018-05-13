#ifndef SCULPTURE_H
#define SCULPTURE_H

#include <vtkAlgorithm.h>
#include <vtkColorTransferFunction.h>
#include <vtkDICOMImageReader.h>
#include <vtkSmartVolumeMapper.h>
#include <vtkImageData.h>
#include <vtkPiecewiseFunction.h>
#include <vtkSmartPointer.h>
#include <vtkVolume.h>
#include <vtkVolumeProperty.h>
#include <vtkPointData.h>
#include <vtkDataArray.h>
#include <vtkImageAccumulate.h>
#include <vtkImageData.h>
#include <vtkMarchingCubes.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkXMLImageDataReader.h>

#include <itkImage.h>
#include <itkVTKImageToImageFilter.h>
#include <itkImageToVTKImageFilter.h>
#include <itkBinomialBlurImageFilter.h>
#include <itkMeanImageFilter.h>
#include <itkMedianImageFilter.h>

#include "Core/TransferFunction.h"
#include "Util/Measures.h"

/**
 * @class Sculpture
 * Class with volume data and mesh
 */
class Sculpture {
public:
	/**
	 * Constructor
	 */
	Sculpture();

	/*
	 * Destructor
	 */
	~Sculpture();

	/**
	 * Get transfer function
	 * @return	Transfer function pointer
	 */
	TransferFunction *getTransferFunction() const;

	/**
	 * Get volume
	 * @return	Volume pointer
	 */
	vtkSmartPointer<vtkVolume> getVolume() const;

	/**
	 * Get 3D matrix with volume data
	 * @return	volume data pointer
	 */
	vtkSmartPointer<vtkImageData> getImageData() const;

	/**
	 * Get mesh extracted using marching cubes
	 * @return	Mesh pointer
	 */
	vtkSmartPointer<vtkActor> getMesh() const;

	/**
	 * Get isosurface value
	 * @return	Isosurface value
	 */
	double getIsoValue() const;

	/**
	 * Get the flag to see if a volume is loaded or not
	 * @return	Volume is loaded or not
	 */
	bool getLoaded() const;

	/**
	 * Get volume min x bound
	 * @return	Min x bound
	 */
	double getMinXBound() const;

	/**
	 * Get volume min y bound
	 * @return	Min y bound
	 */
	double getMinYBound() const;

	/**
	 * Get volume min z bound
	 * @return	Min z bound
	 */
	double getMinZBound() const;

	/**
	 * Get volume max x bound
	 * @return	Max x bound
	 */
	double getMaxXBound() const;

	/**
	 * Get volume max y bound
	 * @return	Max y bound
	 */
	double getMaxYBound() const;

	/**
	 * Get volume max z bound
	 * @return	Max z bound
	 */
	double getMaxZBound() const;

	/**
	 * Set folder where DICOM files will be read
	 * @param	s	Folder with DICOM files
	 */
	void setDICOMFolder(const std::string s);

	/**
	 * Set VTI file with volume dataset
	 * @param	s	VTI file
	 */
	void setVTIFile(const std::string s);

	/**
	 * Set volume material
	 * @param	ambient		Ambient component
	 * @param	diffuse		Diffuse component
	 * @param	specular	Specular component
	 * @param	power		Specular power component
	 */
	void setMaterial(const double ambient, const double diffuse, const double specular, const double power);

	/**
	 * Set isosurface value to extract the mesh
	 * @param	isoValue	Isosurface value
	 */
	void setIsoValue(const double isoValue);

	/**
	 * Create the mesh
	 */
	void createMesh();

	/**
	 * Filter the volume using a Gaussian filter to reduce noise
	 * @param reps	How many times should we apply the blur
	 */
	void gaussianFilter(const unsigned int reps);

	/**
	 * Filter the volume using a mean filter to reduce noise
	 * @param radius	Radius of the neigbourhood for median filter
	 */
	void meanFilter(const unsigned int radius);

	/**
	 * Filter the volume using a median filter to reduce noise
	 * @param radius	Radius of the neigbourhood for median filter
	 */
	void medianFilter(const unsigned int radius);

private:
	vtkSmartPointer<vtkImageData> imageData; /**< 3D Matrix with volume data */
	vtkSmartPointer<vtkVolume> volume; /**< Volume */
	vtkSmartPointer<vtkSmartVolumeMapper> volumeMapper; /**< Mapper that uses DVR GPU-Raycasting */
	vtkSmartPointer<vtkVolumeProperty> volumeProperty; /**< Volume properties */
	vtkSmartPointer<vtkMarchingCubes> surface; /**< Extracted mesh using marching cubes */
	vtkSmartPointer<vtkPolyDataMapper> meshMapper; /**< Mesh mapper */
	vtkSmartPointer<vtkActor> meshActor; /**< Mesh actor */
	TransferFunction *tf; /**< Transfer function */
	double isoValue; /**< Isosurface value to extract the mesh */
	bool loaded; /**< Volume is loaded or not */
	
	/**
	 * Set properties of volume and mesh
	 */
	void setProperties();

	/**
	 * Connect components of the pipeline
	 */
	void connectComponents();
};

#endif // SCULPTURE_H
