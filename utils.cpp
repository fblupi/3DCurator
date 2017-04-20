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

std::array<int, 3> getVector(const int A[3], const int B[3]) {
	return{ B[0] - A[0], B[1] - A[1], B[2] - A[2] };
}

double getDistance(const int A[3], const int A_[3], const int B[3], const int B_[3]) {
	std::array<int, 3> u = getVector(A, A_);
	std::array<int, 3> v = getVector(B, B_);
	return abs((double)abs((B[0] - A[0]) * u[1] * u[2] + (B[1] - A[1]) * u[2] * v[0] + (B[2] - A[2]) * u[0] * v[1] - (B[2] - A[2]) * u[1] * u[0] - (B[1] - A[1]) * u[0] * v[2] - (B[0] - A[0]) * u[2] * v[1]) / (u[0] * v[1] - u[1] * v[2])) / abs(A[2] - B[2]);
}

std::array<double, 2> getEquation(const int A[3], const int B[3]) {
	std::array<int, 3> u = getVector(A, B);
	return{ (double)u[1] / u[0], -((double)(A[0] * u[1]) / u[0]) + A[1] };
}