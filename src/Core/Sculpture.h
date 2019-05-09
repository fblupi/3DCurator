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

typedef signed short PixelType;
const unsigned int Dimension = 3;
typedef itk::Image<PixelType, Dimension> ImageType;
typedef itk::VTKImageToImageFilter<ImageType> VTKImageToImageType;
typedef itk::ImageToVTKImageFilter<ImageType> ImageToVTKImageType;
typedef itk::MeanImageFilter<ImageType, ImageType> MeanImageFilterType;
typedef itk::MedianImageFilter<ImageType, ImageType> MedianImageFilterType;
typedef itk::BinomialBlurImageFilter<ImageType, ImageType> BinomialBlurFilterType;

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

    /**
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
     * Get iso-surface value
     * @return	Iso-surface value
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
    void setDICOMFolder(const std::string &s);

    /**
     * Set VTI file with volume dataset
     * @param	s	VTI file
     */
    void setVTIFile(const std::string &s);

    /**
     * Set volume material
     * @param	ambient		Ambient component
     * @param	diffuse		Diffuse component
     * @param	specular	Specular component
     * @param	power		Specular power component
     */
    void setMaterial(double ambient, double diffuse, double specular, double power);

    /**
     * Set iso-surface value to extract the mesh
     * @param	isoValue	Iso-surface value
     */
    void setIsoValue(double isoValue);

    /**
     * Create the mesh
     */
    void createMesh();

    /**
     * Filter the volume using a Gaussian filter to reduce noise
     * @param reps	How many times should we apply the blur
     */
    void gaussianFilter(unsigned int reps);

    /**
     * Filter the volume using a mean filter to reduce noise
     * @param radius	Radius of the neighborhood for median filter
     */
    void meanFilter(unsigned int radius);

    /**
     * Filter the volume using a median filter to reduce noise
     * @param radius	Radius of the neighborhood for median filter
     */
    void medianFilter(unsigned int radius);

private:
    vtkSmartPointer<vtkImageData> imageData; /**< 3D Matrix with volume data */
    vtkSmartPointer<vtkVolume> volume; /**< Volume */
    vtkSmartPointer<vtkSmartVolumeMapper> volumeMapper; /**< Mapper that uses DVR GPU Ray-casting */
    vtkSmartPointer<vtkVolumeProperty> volumeProperty; /**< Volume properties */
    vtkSmartPointer<vtkMarchingCubes> surface; /**< Extracted mesh using marching cubes */
    vtkSmartPointer<vtkPolyDataMapper> meshMapper; /**< Mesh mapper */
    vtkSmartPointer<vtkActor> meshActor; /**< Mesh actor */
    TransferFunction *tf; /**< Transfer function */
    double isoValue; /**< Iso-surface value to extract the mesh */
    bool loaded; /**< Volume is loaded or not */

    /**
     * Set properties of volume and mesh
     */
    void setProperties();

    /**
     * Connect components of the pipeline
     */
    void connectComponents();

    /**
     * Load volume from image reader
     * @param imageReader   Image reader with volume info
     */
    void loadVolume(const vtkSmartPointer<vtkAlgorithm> &imageReader);

    /**
     * Get ITK image from VTK
     * @return ITK image
     */
    VTKImageToImageType::Pointer getITKImage();

    /**
     * Convert ITK image into VTK
     * @param filter    ITK image
     */
    void itkToVTK(const ImageType::Pointer &filter);
};

#endif // SCULPTURE_H
