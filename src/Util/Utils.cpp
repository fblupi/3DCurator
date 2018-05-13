#include "Utils.h"

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
	time_t t = time(0); // current date
	struct tm now;
	localtime_s(&now, &t); // struct with different components
	return std::to_string(now.tm_year + 1900)
		+ std::to_string(now.tm_mon + 1)
		+ std::to_string(now.tm_mday)
		+ std::to_string(now.tm_hour)
		+ std::to_string(now.tm_min)
		+ std::to_string(now.tm_sec);
}