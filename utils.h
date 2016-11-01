#ifndef UTILS_H
#define UTILS_H

#include <ctime>
#include <string>
#include <algorithm>
#include <limits>

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

#endif // UTILS_H
