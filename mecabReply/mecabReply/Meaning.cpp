#include <iostream>
#include "Meaning.h"
#include "processes.h"

namespace OTA {

#define MECAB_CHECK(eval) if (! eval) { \
   const char *e = tagger ? tagger->what() : MeCab::getTaggerError(); \
   std::cerr << "Exception:" << e << std::endl; \
   delete tagger; \
   return -1; }


	Meaning::Meaning()
	{
	}

	Meaning::Meaning(std::string input_str)
	{
		MeCab::Tagger* tagger = MeCab::createTagger("");
		if (!tagger) {

			const char* e = tagger ? tagger->what() : MeCab::getTaggerError();
			std::cerr << "Exception:" << e << std::endl;
			delete tagger;
		} else
			this->getParseResult(input_str, tagger);
	}

	Meaning::Meaning(std::string input_str, MeCab::Tagger* tagger)
	{
		this->getParseResult(input_str, tagger);
	}

	int Meaning::getParseResult(std::string input_str, MeCab::Tagger* tagger)
	{
		MECAB_CHECK(tagger);

		string = input_str;
		std::string result = tagger->parse(input_str.c_str());
		std::vector<std::string> parse_result = split(result, '\n');
		std::vector<std::vector<std::string>> phrase_and_sentence;

		for (size_t i = 0; i < parse_result.size(); i++) {
			mean_t mean;
			phrase_and_sentence.emplace_back(split(parse_result[i], '\t'));
			if (phrase_and_sentence[i].size() == 2) {
				mean.phrase = phrase_and_sentence[i][0];
				mean.means = split(phrase_and_sentence[i][1], ',');
				meanings.emplace_back(mean);
			}
		}

		return 0;
	}

	int Meaning::printPargeResult()
	{
		std::cout << "Origin string >> " << string << std::endl << std::endl;
		printf_s("\n\n---------------------------------------------------\n\n");
		
		for (size_t i = 0; i < meanings.size(); i++) {
			std::cout << meanings[i].phrase << "\t";
			for (size_t j = 0; j < meanings[i].means.size(); j++) {
				std::cout << meanings[i].means[j] << ", ";
			}
			std::cout << std::endl;
		}

		printf_s("\n\n---------------------------------------------------\n\n");

		return 0;
	}

}
