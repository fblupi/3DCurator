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
 * Clase con la función de transferencia
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
	 * Obtener función de transferencia de color
	 * @return	Función de transferencia de color
	 */
	vtkSmartPointer<vtkColorTransferFunction> getColorFun() const;

	/**
	 * Obtener función de transferencia de opacidad escalar
	 * @return	Función de transferencia de opacidad escalar
	 */
	vtkSmartPointer<vtkPiecewiseFunction> getScalarFun() const;

	/**
	 * Obtener función de transferencia de opacidad gradiente
	 * @return	Función de transferencia de opacidad gradiente
	 */
	vtkSmartPointer<vtkPiecewiseFunction> getGradientFun() const;

	/**
	 * Obtener el nombre de la función de transferencia
	 * @return	Nombre
	 */
	std::string getName() const;

	/**
	 * Obtener la descripción de la función de transferencia
	 * @return	Descripción
	 */
	std::string getDescription() const;

	/**
	 * Establecer el nombre de la función de transferencia
	 * @param	name	Nombre
	 */
	void setName(const std::string name);

	/**
	 * Establecer la descripción de la función de transferencia
	 * @param	description		Descripción
	 */
	void setDescription(const std::string description);

	/**
	 * Lee la función de transferencia de un archivo XML
	 * @param	filename	Ruta del archivo de origen
	 */
	void read(std::string &filename);

	/**
	 * Lee la función de transferencia de un archivo XML
	 * @param	file	Archivo de origen
	 */
	void read(std::istream &file);

	/**
	 * Escribe la función de transferencia en un archivo XML
	 * @param	filename	Archivo de salida
	 */
	void write(std::string &filename);

	/**
	 * Limpia todos los puntos de todas las partes de la función de transferencia
	 */
	void clear();

	/**
	 * Añade un punto en la parte de color de la función de transfencia
	 * @param	x	Valor de densidad
	 * @param	r	Componente roja
	 * @param	g	Componente verde
	 * @param	b	Componente azul
	 */
	void addColorPoint(const double x, const double r, const double g, const double b);

	/**
	 * Añade un punto en la parte de opacidad escalar de la función de transfencia
	 * @param	x	Valor de densidad
	 * @param	y	Opacidad
	 */
	void addScalarPoint(const double x, const double y);

	/**
	 * Añade un punto en la parte de opacidad gradiente de la función de transfencia
	 * @param	x	Valor de gradiente
	 * @param	y	Opacidad
	 */
	void addGradientPoint(const double x, const double y);

private:
	std::string name; /**< Nombre de la función de transferencia */
	std::string description; /**< Descripción de la función de transferencia */
	vtkSmartPointer<vtkColorTransferFunction> colorFun; /**< Parte de color de la función de transferencia */
	vtkSmartPointer<vtkPiecewiseFunction> scalarFun; /**< Parte de opacidad escalar de la función de transferencia */
	vtkSmartPointer<vtkPiecewiseFunction> gradientFun; /**< Parte de opacidad gradiente de la función de transferencia */

	/**
	 * Escribe la función de transferencia dado un árbol extraido de un archivo XML
	 * @param	ptree	Árbol con la función de transferencia
	 */
	void readData(ptree pt);
};

#endif // TRANSFERFUNCTION_H
