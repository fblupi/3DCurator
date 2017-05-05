#include "utils.h"

std::string splitAndGetLast(std::string s, const std::string delimiter) {
	size_t pos = 0;
	while ((pos = s.find(delimiter)) != std::string::npos) {
		s.erase(0, pos + delimiter.length());
	}
	return s;
}

std::string getFileExtension(std::string s) {
	return splitAndGetLast(s, ".");
}

std::string toUpper(std::string s) {
	std::transform(s.begin(), s.end(), s.begin(), ::toupper);
	return s;
}

std::string getCurrentDate() {
	time_t t = time(0); // obtiene fecha actual
	struct tm now;
	localtime_s(&now, &t); // obtiene el struct para obtener los distintos componentes
	return std::to_string(now.tm_year + 1900) // año
		+ std::to_string(now.tm_mon + 1) // mes
		+ std::to_string(now.tm_mday) // día
		+ std::to_string(now.tm_hour) // hora
		+ std::to_string(now.tm_min) // minuto
		+ std::to_string(now.tm_sec); // segundo
}