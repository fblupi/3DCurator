#ifndef UTILS_H
#define UTILS_H

#include <ctime>
#include <string>
#include <algorithm>
#include <limits>
#include <array>

/**
 * Separa una cadena en subcadenas dado un delimitador y se queda con la última
 * @param	s			Cadena inicial
 * @param	delimeter	Delimitador
 * @return	Última subcadena encontrada
 */
std::string splitAndGetLast(std::string s, const std::string delimiter);

/**
 * Dado un archivo, devuelve su extensión
 * @param	s			Nombre del archivo
 * @return	Extensión del archivo
 */
std::string getFileExtension(std::string s);

/**
 * Dada una cadena la devuelve en mayúsculas
 * @param	s			Cadena inicial
 * @return	Cadena inicial en mayúsculas
 */
std::string toUpper(std::string s);

/**
 * Devuelve una cadena con la fecha en formato AAAAMMDDHHMMSS
 * @return	Cadena con la fecha
 */
std::string getCurrentDate();

/**
* Get line vector from two points
* @param A First Point
* @param B Second Point
* @return  Vector from B to A
*/
std::array<int, 3> getVector(const int A[3], const int B[3]);

/**
* Get normalized distance betweent two lines
* @param A  First Point of First Line
* @param A_ Second Point of First Line
* @param B  First Point of Second Line
* @param B_ Second Point of Second Line
* @return   Normalized distance between two lines
*/
double getDistance(const int A[3], const int A_[3], const int B[3], const int B_[3]);

/**
* Get line equation y = a * x + b by giving two points
* @param A First Point
* @param B Second Point
* @return  a and b parameters of the equation y = a * x + b
*/
std::array<double, 2> getEquation(const int A[3], const int B[3]);

#endif // UTILS_H
