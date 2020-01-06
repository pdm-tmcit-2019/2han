#include <iostream>
#include "processes.h"

namespace OTA {
	std::vector<std::string> split(const std::string &str, char sep)
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

	std::vector<std::string> split(const std::string& str, char sep, int max)
	{
		int i = 0;
		std::vector<std::string> v;        // 分割結果を格納するベクター
		auto first = str.begin();              // テキストの最初を指すイテレータ
		while ((first != str.end()) || (i++ < max)) {         // テキストが残っている間ループ
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
}