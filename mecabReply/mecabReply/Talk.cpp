#include "Talk.h"
#include <fstream>

namespace OTA {

	Talk::Talk()
	{
		myname = "白石創之介";
		yourname = "ScreenOTA";

		if (getCSVFileData() < 0) {
			setupTalkList();
		}

		mt = std::mt19937(rnd());
	}

	Talk::Talk(char* name)
	{
		myname = name;
		yourname = "ScreenOTA";

		if (getCSVFileData() < 0) {
			setupTalkList();
		}
		mt = std::mt19937(rnd());
	}

	void Talk::setupTalkList()
	{
		char talk[128] = {};

		sprintf_s(talk, "皆さんはじめまして、或いはお久しぶりです。私は出張でこの村を訪れた電気工事士の%sです。", myname.c_str());
		lists content;


		content.talk = talk;
		content.tags.emplace_back("自己紹介");

		talk_list.push_back(content);
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

			talk_list.push_back(tlist);
		}

		ifs.close();

		return 0;
	}

	std::string Talk::replyTalk(talk_t input)
	{
		if (input.content == "") {
			return searchTalkList("自己紹介");
		} else if (END_DETECT) {
			return searchTalkList("退場");
		} else if (input.content == "お前たちの平成って醜くないか？") {
			return "瞬瞬必生";
		}

		yourname = input.name;
		std::vector<mean_t> mecab;

		meaning = Meaning::Meaning();
		meaning.getParseResult(input.content, MeCab::createTagger(""));
		mecab = meaning.getMeaningData();

		for (auto word = mecab.begin(); word != mecab.end(); word++) {
			if (word->means[0] == "感動詞") {
				if (word->phrase == "こんにちは")
					return searchTalkList("こんにちは");
				else if (word->phrase == "おはよう")
					return searchTalkList("おはよう");
				else if (word->phrase == "ありがとう" || word->phrase == "すみません")
					return searchTalkList("謙遜");
				else if (word->phrase == "ねえ" || word->phrase == "おい" || word->phrase == "あの")
					return searchTalkList("応答");
			}
		}

		if (detectionWerewolf(mecab))
			input.tags.push_back("人狼");

		std::vector<std::string> talk = searchTalkList(mecab);
/*		for (size_t i = 0; i < talk.size(); i++) {
			printf_s("%s\n", talk[i].c_str());
		}*/

		talk = searchTalkList(input.tags);
/*		for (size_t i = 0; i < talk.size(); i++) {
			printf_s("%s\n", talk[i].c_str());
		}*/

		if (talk.empty())
			return "ボッ///";

		std::uniform_int_distribution<> randTalk(0, talk.size() - 1);
		return talk[randTalk(mt)];
	}

	std::string Talk::searchTalkList(std::string key)
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
				bool f = false;

				for (size_t fukkin = 0; fukkin < talk_list[n].tags.size(); fukkin++) {
					if (talk_list[n].tags[fukkin] == "退場") {
						f = true;
						break;
					}
				}
				if (!f)
					talks.push_back(insertNameTalk(talk_list[n].talk, yourname));
			}
		}

		return talks;
	}

	std::vector<std::string> Talk::searchTalkList(std::vector<mean_t> key)
	{
		std::vector<std::string> talks;
		bool flag = false;

		for (size_t n = 0; n < talk_list.size(); n++) {
			for (size_t i = 0; i < key.size(); i++) {
				if (talk_list[n].talk.find(key[i].phrase) == std::string::npos) {
					flag = false;
					break;
				}
				flag = true;
			}
			if (flag) {
				flag = false;
				bool f = false;

				for (size_t fukkin = 0; fukkin < talk_list[n].tags.size(); fukkin++) {
					if (talk_list[n].tags[fukkin] == "退場"){
						f = true;
						break;
					}
				}
				if (!f)
					talks.push_back(insertNameTalk(talk_list[n].talk, yourname));
			}
		}

		return talks;
	}
}
