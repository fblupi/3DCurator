#ifndef FIGURA_H
#define FIGURA_H

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

#include <itkImage.h>
#include <itkImageFileReader.h>
#include <itkImageToVTKImageFilter.h>
#include <itkVTKImageToImageFilter.h>
#include <itkCastImageFilter.h>
#include <itkMedianImageFilter.h>

#include "transferFunction.h"
#include "measures.h"

/**
 * @class Figura
 * Clase que encapsula el los datos del volumen, el volumen y la malla y permite gestionarlos
 */
class Figura {
public:
	/**
	 * Constructor
	 */
    Figura();

	/*
	 * Destructor
	 */
    ~Figura();

	/**
	 * Obtiene la funci�n de transferencia
	 * @return	Puntero a la funci�n de transferencia
	 */
	TransferFunction *getTransferFunction() const;

	/**
	 * Obtiene el volumen
	 * @return	Puntero al volumen
	 */
	vtkSmartPointer<vtkVolume> getVolume() const;

	/**
	 * Obtiene la matriz 3D con los datos del volumen
	 * @return	Puntero a los datos del volumen
	 */
	vtkSmartPointer<vtkImageData> getImageData() const;

	/**
	 * Obtiene la malla extraida
	 * @return	Puntero al actor de la malla
	 */
	vtkSmartPointer<vtkActor> getMesh() const;

	/**
	 * Obtiene el valor de isosuperficie
	 * @return	Valor de isosuperficie
	 */
	double getIsoValue() const;

	/**
	 * Obtiene el flag para comprobar si est� o no cargado el volumen
	 * @return	Flag de cargado o no cargado
	 */
	bool getLoaded() const;

	/**
	 * Obtiene el l�mite inferior de la figura en el eje X
	 * @return	L�mite
	 */
	double getMinXBound() const;

	/**
	 * Obtiene el l�mite inferior de la figura en el eje Y
	 * @return	L�mite
	 */
	double getMinYBound() const;

	/**
	 * Obtiene el l�mite inferior de la figura en el eje Z
	 * @return	L�mite
	 */
	double getMinZBound() const;

	/**
	 * Obtiene el l�mite superior de la figura en el eje X
	 * @return	L�mite
	 */
	double getMaxXBound() const;

	/**
	 * Obtiene el l�mite superior de la figura en el eje Y
	 * @return	L�mite
	 */
	double getMaxYBound() const;

	/**
	 * Obtiene el l�mite superior de la figura en el eje Z
	 * @return	L�mite
	 */
	double getMaxZBound() const;

	/**
	 * Establece la carpeta de donde se leer�n los archivos DICOM
	 * @param	s	Carpeta con los datos DICOM
	 */
	void setDICOMFolder(const std::string s);

	/**
	 * Asigna el material al volumen
	 * @param	ambient		Componente ambiental
	 * @param	diffuse		Componente difusa
	 * @param	specular	Componente especular
	 * @param	power		Potencia especular
	 */
	void setMaterial(const double ambient, const double diffuse, const double specular, const double power);

	/**
	 * Establece el valor de isosuperficie para generar la malla
	 * @param	isoValue	isoValue
	 */
	void setIsoValue(const double isoValue);

	/**
	 * Crea la malla
	 */
	void createMesh();

	void filter();

private:
	vtkSmartPointer<vtkImageData> imageData; /**< Matriz 3D con los valores escalares de la figura */
    vtkSmartPointer<vtkVolume> volume; /**< Volumen con la figura */
	vtkSmartPointer<vtkSmartVolumeMapper> volumeMapper; /**< Mapeador que usa DVR GPU-Raycasting */
	vtkSmartPointer<vtkVolumeProperty> volumeProperty; /**< Propiedades del volumen */
	vtkSmartPointer<vtkMarchingCubes> surface; /**< Malla extraida del volumen mediante marching cubes */
	vtkSmartPointer<vtkPolyDataMapper> meshMapper; /**< Mapeador de la malla */
	vtkSmartPointer<vtkActor> meshActor; /**< Actor de la malla extraida */
	TransferFunction *tf; /**< Funci�n de transferencia */
	double isoValue; /**< Valor de isosuperficia para la malla */
	bool loaded; /**< Flag que determina si hay un volumen cargado */
	
	/**
	 * Establece las propiedades del volumen y la malla (llamado desde el constructor)
	 */
    void setProperties();

	/**
	 * Conecta los componentes del volumen y la malla (llamado desde el constructor)
	 */
	void connectComponents();
};

#endif // FIGURA_H
