#ifndef MEANING_H
#define MEANING_H

#include <vector>
#include <string>
#include <mecab.h>

namespace OTA {
	typedef struct
	{
		std::string phrase;
		std::vector<std::string> means;
	} mean_t;

	class Meaning
	{
	private:
		std::vector<mean_t> meanings;
		std::string string;

	public:
		Meaning();
		Meaning(std::string input_str);
		Meaning(std::string input_str, MeCab::Tagger* tagger);

		int getParseResult(std::string input_str, MeCab::Tagger* tagger);
		int printPargeResult();
		std::vector<mean_t> getMeaningData();
		void clearInputString();
	};


	inline std::vector<mean_t> Meaning::getMeaningData()
	{
		return meanings;
	}

	inline void Meaning::clearInputString()
	{
		string.clear();
	}
}

#endif // !MEANING_H
