#include "calculation.h"

namespace OTA {
	std::vector<std::string> split(const std::string& str, char sep)
	{
		std::vector<std::string> v;        // 分割結果を格納するベクター
		auto first = str.begin();              // テキストの最初を指すイテレータ
		while (first != str.end()) {         // テキストが残っている間ループ
			auto last = first;                      // 分割文字列末尾へのイテレータ
			while (last != str.end() && *last != sep)       // 末尾 or セパレータ文字まで進める
				++last;
			v.push_back(std::string(first, last));       // 分割文字を出力
			if (last != str.end())
				++last;
			first = last;          // 次の処理のためにイテレータを設定
		}
		return v;
	}

	int getCSVFileData(const char* name, std::vector<std::vector<std::string>>* csv_data)
	{
		std::string line;

		std::ifstream ifs(name);
		if (ifs.fail()) {
			printf_s("csv input error.\n");
			return -11;
		}
		printf_s("csv input successful.\n");

		while (getline(ifs, line)) {
			csv_data->emplace_back(split(line, ','));
		}

		ifs.close();

		return 0;
	}
}
