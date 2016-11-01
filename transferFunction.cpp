#include "transferFunction.h"

TransferFunction::TransferFunction() {
	colorFun = vtkSmartPointer<vtkColorTransferFunction>::New();
	scalarFun = vtkSmartPointer<vtkPiecewiseFunction>::New();
	gradientFun = vtkSmartPointer<vtkPiecewiseFunction>::New();
	name = "tf"; // nombre por defecto para la función de transferencia
	description = ""; // descripción por defecto para la función de transferencia
}

void TransferFunction::readData(ptree pt) {
	name = pt.get<std::string>("tf.<xmlattr>.name"); // lee el atributo "name" del nodo padre del árbol
	description = pt.get<std::string>("tf.<xmlattr>.description"); // lee el atributo "description" del nodo padre del árbol

	BOOST_FOREACH(ptree::value_type const &v, pt.get_child("tf.color")) { // recorre todos los hijos del nodo "color"
		if (v.first == "point") { // si el hijo es un nodo "point"
			colorFun->AddRGBPoint(			// añade un punto a la parte de color de la función de transferencia obteniendo
				v.second.get<double>("x"),	// el valor de densidad
				v.second.get<double>("r"),	// la componente roja
				v.second.get<double>("g"),	// la verde
				v.second.get<double>("b")	// y la azul
				);
		}
	}

	BOOST_FOREACH(ptree::value_type const &v, pt.get_child("tf.scalar")) { // recorre todos los hijos del nodo "scalar"
		if (v.first == "point") { // si el hijo es un nodo "point"
			scalarFun->AddPoint(			// añade un punto a la parte de opacidad escalar de la función de transferencia obteniendo
				v.second.get<double>("x"),	// el valor de densidad
				v.second.get<double>("y")	// y la opacidad
				);
		}
	}

	BOOST_FOREACH(ptree::value_type const &v, pt.get_child("tf.gradient")) { // recorre todos los hijos del nodo "gradient"
		if (v.first == "point") { // si el hijo es un nodo "point"
			gradientFun->AddPoint(			// añade un punto a la parte de opacidad gradiente de la función de transferencia obteniendo
				v.second.get<double>("x"),	// el valor de densidad
				v.second.get<double>("y")	// y la opacidad
				);
		}
	}
}

void TransferFunction::read(std::string &filename) {
	clear(); // elimna los puntos de todas las partes de las funciones

	ptree pt;
	read_xml(filename, pt); // lee el archivo y lo pasa a un árbol

	readData(pt); // lee los datos del árbol
}


void TransferFunction::read(std::istream &file) {
	clear(); // elimna los puntos de todas las partes de las funciones

	ptree pt;
	read_xml(file, pt); // lee el archivo y lo pasa a un árbol

	readData(pt); // lee los datos del árbol
}

void TransferFunction::write(std::string &filename) {
	ptree pt; // árbol donde se creará la estructura del archivo XML

	double *colorFunData = colorFun->GetDataPointer();			// obtiene los puntos de la parte de color de la función de transferencia
	double *scalarFunData = scalarFun->GetDataPointer();		// de la de la opacidad escalar
	double *gradientFunData = gradientFun->GetDataPointer();	// y de la opacidad gradiente

	pt.put("tf.<xmlattr>.name", name); // añade el atributo "name" al nodo padre del archivo
	pt.put("tf.<xmlattr>.description", description); // añade el atributo "description" al nodo padre del archivo

	ptree &color = pt.add("tf.color", ""); // añade un nodo "color" que cuelga del nodo padre
	for (int i = 0; i < colorFun->GetSize(); i++) { // recorre todos los puntos de la parte de color de la función de transferencia
		ptree &node = color.add("point", ""); // añade un nodo "point" que cuelga del nodo "color"
		node.put("x", colorFunData[i * 4]);		// añade un nodo hoja a "point" con la densidad
		node.put("r", colorFunData[i * 4 + 1]);	// otro con la componente roja
		node.put("g", colorFunData[i * 4 + 2]);	// otro con la componente verde
		node.put("b", colorFunData[i * 4 + 3]);	// y otro con la componente azul
	}

	ptree &scalar = pt.add("tf.scalar", ""); // añade un nodo "scalar" que cuelga del nodo padre
	for (int i = 0; i < scalarFun->GetSize(); i++) { // recorre todos los puntos de la parte de opacidad escalar de la función de transferencia
		ptree &node = scalar.add("point", ""); // añade un nodo "point" que cuelga del nodo "scalar"
		node.put("x", scalarFunData[i * 2]);		// añade un nodo hoja a "point" con la densidad
		node.put("y", scalarFunData[i * 2 + 1]);	// y otro con la opacidad
	}

	ptree &gradient = pt.add("tf.gradient", ""); // añade un nodo "gradient" que cuelga del nodo padre
	for (int i = 0; i < gradientFun->GetSize(); i++) { // recorre todos los puntos de la parte de opacidad gradiente de la función de transferencia
		ptree &node = scalar.add("point", ""); // añade un nodo "point" que cuelga del nodo "gradient"
		node.put("x", gradientFunData[i * 2]);		// añade un nodo hoja a "point" con la gradiente
		node.put("y", gradientFunData[i * 2 + 1]);	// y otro con la opacidad
	}

	write_xml(filename, pt);  // escribe en el archivo leyendo del árbol que se ha creado
}
void TransferFunction::clear() {
	colorFun->RemoveAllPoints(); // borra todos los puntos de la función de color
	scalarFun->RemoveAllPoints(); // borra todos los puntos de la función de opacidad escalar
	gradientFun->RemoveAllPoints(); // borra todos los puntos de la función de opacidad gradiente
}

void TransferFunction::addColorPoint(const double x, const double r, const double g, const double b) {
	colorFun->AddRGBPoint(x, r, g, b);
}

void TransferFunction::addScalarPoint(const double x, const double y) {
	scalarFun->AddPoint(x, y);
}

void TransferFunction::addGradientPoint(const double x, const double y) {
	gradientFun->AddPoint(x, y);
}

void TransferFunction::setName(const std::string name) {
	this->name = name;
}

void TransferFunction::setDescription(const std::string description) {
	this->description = description;
}

std::string TransferFunction::getName() const {
	return name;
}

std::string TransferFunction::getDescription() const {
	return description;
}

vtkSmartPointer<vtkColorTransferFunction> TransferFunction::getColorFun() const {
	return colorFun;
}

vtkSmartPointer<vtkPiecewiseFunction> TransferFunction::getScalarFun() const {
	return scalarFun;
}

vtkSmartPointer<vtkPiecewiseFunction> TransferFunction::getGradientFun() const {
	return gradientFun;
}
