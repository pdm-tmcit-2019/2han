#ifndef CALCULATION_H
#define CALCULATION_H

#define _USE_MATH_DEFINES

#include <cstdio>
#include <cmath>
#include <vector>
#include <fstream>
#include <string>

#define X 0
#define Y 1
#define Z 2

typedef struct
{
	std::vector<double> value;
	std::string label;
} data_t;

typedef struct
{
	int num = 0;
	double value = 0;
} array_data_t;

namespace OTA {
	std::vector<std::string> split(const std::string& str, char sep);
	int getCSVFileData(const char* name, std::vector<std::vector<std::string>>* csv_data);
}

#endif // !CALCULATION_H
