#ifndef TRANSFERFUNCTION_H
#define TRANSFERFUNCTION_H

#include <vector>
#include <string>
#include <iostream>

#include <boost/property_tree/xml_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/foreach.hpp>

#include <vtkSmartPointer.h>
#include <vtkColorTransferFunction.h>
#include <vtkPiecewiseFunction.h>

using boost::property_tree::ptree;

/**
 * Clase con la funci�n de transferencia
 */
class TransferFunction {
public:
	/**
	 * Constructor
	 */
	TransferFunction();

	/*
	 * Destructor
	 */
	~TransferFunction();

	/**
	 * Obtener funci�n de transferencia de color
	 * @return	Funci�n de transferencia de color
	 */
	vtkSmartPointer<vtkColorTransferFunction> getColorFun() const;

	/**
	 * Obtener funci�n de transferencia de opacidad escalar
	 * @return	Funci�n de transferencia de opacidad escalar
	 */
	vtkSmartPointer<vtkPiecewiseFunction> getScalarFun() const;

	/**
	 * Obtener funci�n de transferencia de opacidad gradiente
	 * @return	Funci�n de transferencia de opacidad gradiente
	 */
	vtkSmartPointer<vtkPiecewiseFunction> getGradientFun() const;

	/**
	 * Obtener el nombre de la funci�n de transferencia
	 * @return	Nombre
	 */
	std::string getName() const;

	/**
	 * Obtener la descripci�n de la funci�n de transferencia
	 * @return	Descripci�n
	 */
	std::string getDescription() const;

	/**
	 * Establecer el nombre de la funci�n de transferencia
	 * @param	name	Nombre
	 */
	void setName(const std::string name);

	/**
	 * Establecer la descripci�n de la funci�n de transferencia
	 * @param	description		Descripci�n
	 */
	void setDescription(const std::string description);

	/**
	 * Lee la funci�n de transferencia de un archivo XML
	 * @param	filename	Ruta del archivo de origen
	 */
	void read(std::string &filename);

	/**
	 * Lee la funci�n de transferencia de un archivo XML
	 * @param	file	Archivo de origen
	 */
	void read(std::istream &file);

	/**
	 * Escribe la funci�n de transferencia en un archivo XML
	 * @param	filename	Archivo de salida
	 */
	void write(std::string &filename);

	/**
	 * Limpia todos los puntos de todas las partes de la funci�n de transferencia
	 */
	void clear();

	/**
	 * A�ade un punto en la parte de color de la funci�n de transfencia
	 * @param	x	Valor de densidad
	 * @param	r	Componente roja
	 * @param	g	Componente verde
	 * @param	b	Componente azul
	 */
	void addColorPoint(const double x, const double r, const double g, const double b);

	/**
	 * A�ade un punto en la parte de opacidad escalar de la funci�n de transfencia
	 * @param	x	Valor de densidad
	 * @param	y	Opacidad
	 */
	void addScalarPoint(const double x, const double y);

	/**
	 * A�ade un punto en la parte de opacidad gradiente de la funci�n de transfencia
	 * @param	x	Valor de gradiente
	 * @param	y	Opacidad
	 */
	void addGradientPoint(const double x, const double y);

private:
	std::string name; /**< Nombre de la funci�n de transferencia */
	std::string description; /**< Descripci�n de la funci�n de transferencia */
	vtkSmartPointer<vtkColorTransferFunction> colorFun; /**< Parte de color de la funci�n de transferencia */
	vtkSmartPointer<vtkPiecewiseFunction> scalarFun; /**< Parte de opacidad escalar de la funci�n de transferencia */
	vtkSmartPointer<vtkPiecewiseFunction> gradientFun; /**< Parte de opacidad gradiente de la funci�n de transferencia */

	/**
	 * Escribe la funci�n de transferencia dado un �rbol extraido de un archivo XML
	 * @param	ptree	�rbol con la funci�n de transferencia
	 */
	void readData(ptree pt);
};

#endif // TRANSFERFUNCTION_H
