#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iterator>
#include "calculation.h"
#include "picojson.h"

const char fname[] = "firstMorning.jsonld";

int parseArray(picojson::value v);
int parseObject(picojson::value v);

int main()
{
	std::ifstream ifs(fname, std::ios::in);
	if (ifs.fail()) {
		std::cerr << "failed to read test.json" << std::endl;
		return 1;
	}
	const std::string json((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());
	ifs.close();

	picojson::value v;
	const std::string err = picojson::parse(v, json);
	if (!err.empty()) {
		std::cerr << err << std::endl;
		return 2;
	}

	parseObject(v);

	return 0;
}

int parseArray(picojson::value v)
{
	picojson::array& a = v.get<picojson::array>();
	std::vector<std::string> strings;

	for (picojson::array::iterator it = a.begin(); it < a.end(); it++) {
		static int i = 0;
		strings.emplace_back(it->to_str());
	}

	for (size_t i = 0; i < strings.size(); i++) {
		std::cout << "\t" << strings[i] << "\n";

	}

	return 0;
}

int parseObject(picojson::value v)
{
	picojson::object& obj = v.get<picojson::object>();
	static int i = 0;

	for (const auto& p : obj) {
		for (int j = 0; j < i; j++) {
			printf_s("\t");
		}
		std::cout << p.first << ": " << p.second.to_str() << std::endl;

		if (p.second.to_str() == "array") {
			picojson::value& c = obj[p.first];
			parseArray(c);
		} else if (p.second.to_str() == "object") {
			i++;
			picojson::value& c = obj[p.first];
			parseObject(c);
			i--;
		}
	}

	return 0;
}
