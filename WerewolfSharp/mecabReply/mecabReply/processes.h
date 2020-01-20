#ifndef CALCULATION_H
#define CALCULATION_H

#include <vector>
#include <string>

namespace OTA {
	std::vector<std::string> split(const std::string& str, char sep);
	std::vector<std::string> split(const std::string& str, char sep, int max);
}

#endif // !CALCULATION_H
