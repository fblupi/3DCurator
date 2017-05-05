#ifndef UTILS_H
#define UTILS_H

#include <ctime>
#include <string>
#include <algorithm>
#include <limits>

/**
 * Separa una cadena en subcadenas dado un delimitador y se queda con la �ltima
 * @param	s			Cadena inicial
 * @param	delimeter	Delimitador
 * @return	�ltima subcadena encontrada
 */
std::string splitAndGetLast(std::string s, const std::string delimiter);

/**
 * Dado un archivo, devuelve su extensi�n
 * @param	s			Nombre del archivo
 * @return	Extensi�n del archivo
 */
std::string getFileExtension(std::string s);

/**
 * Dada una cadena la devuelve en may�sculas
 * @param	s			Cadena inicial
 * @return	Cadena inicial en may�sculas
 */
std::string toUpper(std::string s);

/**
 * Devuelve una cadena con la fecha en formato AAAAMMDDHHMMSS
 * @return	Cadena con la fecha
 */
std::string getCurrentDate();

#endif // UTILS_H
