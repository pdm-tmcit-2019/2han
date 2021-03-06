#include "Talk.h"
#include <fstream>

namespace OTA {

	Talk::Talk()
	{
		myname = "白石創之介";

		if (getCSVFileData() < 0) {
			setupTalkList();
		}
	}

	Talk::Talk(char* name)
	{
		myname = name;

		if (getCSVFileData() < 0) {
			setupTalkList();
		}
	}

	Talk::~Talk()
	{
	}

	void Talk::setupTalkList()
	{
		char talk[128] = {};

		sprintf_s(talk, "皆さんはじめまして、或いはお久しぶりです。私は出張でこの村を訪れた電気工事士の%sです。", myname.c_str());
		lists content;


		content.talk = talk;
		content.tags.emplace_back("自己紹介");

		talk_list.emplace_back(content);
	}

	int Talk::getCSVFileData()
	{
		std::string line;
		std::vector<std::string> data;
		lists tlist;

		std::ifstream ifs("talklist.csv");
		if (ifs.fail()) {
			printf_s("csv input error.\n");
			return -11;
		}
		printf_s("csv input successful.\n");

		while (getline(ifs, line)) {
			data = split(line, ',');
			if (data.size() != 2) {
				printf_s("この行は読み込めません。\n");
				continue;
			}

			tlist.talk = data[0];
			tlist.tags = split(data[1], ':');

			if (tlist.tags[0] == "自己紹介") {
				tlist.talk = insertNameTalk(tlist.talk, myname);
			}

			talk_list.emplace_back(tlist);
		}

		ifs.close();

		return 0;
	}

	std::string Talk::replyTalk(talk_t input)
	{
		if (input.content == "") {
			return searchTalkList("自己紹介");
		} else if (END_DETECt) {
			return searchTalkList("退場");
		} else if (input.content == "お前たちの平成って醜くないか？") {
			return "瞬瞬必生";
		}

		std::vector<mean_t> mecab;

		meaning.getParseResult(input.content, MeCab::createTagger(""));
		meaning.printPargeResult();
		mecab = meaning.getMeaningData();

		std::vector<std::string> key;
		key.emplace_back("人狼");
		key.emplace_back("さん");
		std::vector<std::string> talk = searchTalkList(key);
		for (size_t i = 0; i < talk.size(); i++) {
			printf_s("%s\n", talk[i].c_str());
		}
/*/
		for (size_t i = 0; i < mecab.size() - 1; i++) {
			if (mecab[i].phrase + mecab[i + 1].phrase == "人狼") {
				return insertNameTalk(searchTalkList("白"), input.name);
			}
		}*/

		return "ボッ///";
	}

	std::string Talk::searchTalkList(const char* key)
	{
		for (size_t i = 0; i < talk_list.size(); i++) {
			for (size_t j = 0; j < talk_list[i].tags.size(); j++) {
				if (talk_list[i].tags[j] == key)
					return talk_list[i].talk;
			}
		}
		return "私の仕事は人間を襲うこと…！";
	}

	std::vector<std::string> Talk::searchTalkList(std::vector<std::string> key)
	{
		std::vector<std::string> talks;
		bool flag = false;

		for (size_t n = 0; n < talk_list.size(); n++) {
			for (size_t i = 0; i < key.size(); i++) {
				if (talk_list[n].talk.find(key[i]) == std::string::npos) {
					flag = false;
					break;
				}
				flag = true;
			}
			if (flag) {
				flag = false;
				talks.emplace_back(talk_list[n].talk);
			}
		}

		return talks;
	}
}
