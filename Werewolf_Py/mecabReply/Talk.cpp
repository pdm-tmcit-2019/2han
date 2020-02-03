#include "Talk.h"
#include <fstream>

namespace OTA {

	Talk::Talk()
	{
		myname = "”’Î‘n”V‰î";
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

		sprintf_s(talk, "ŠF‚³‚ñ‚Í‚¶‚ß‚Ü‚µ‚ÄAˆ½‚¢‚Í‚¨‹v‚µ‚Ô‚è‚Å‚·B„‚Ío’£‚Å‚±‚Ì‘º‚ğ–K‚ê‚½“d‹CH–m‚Ì%s‚Å‚·B", myname.c_str());
		lists content;


		content.talk = talk;
		content.tags.emplace_back("©ŒÈĞ‰î");

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
				printf_s("‚±‚Ìs‚Í“Ç‚İ‚ß‚Ü‚¹‚ñB\n");
				continue;
			}

			tlist.talk = data[0];
			tlist.tags = split(data[1], ':');

			if (tlist.tags[0] == "©ŒÈĞ‰î") {
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
			return searchTalkList("©ŒÈĞ‰î");
		} else if (END_DETECT) {
			return searchTalkList("‘Şê");
		} else if (input.content == "‚¨‘O‚½‚¿‚Ì•½¬‚Á‚ÄX‚­‚È‚¢‚©H") {
			return "uu•K¶";
		}

		yourname = input.name;
		std::vector<mean_t> mecab;

		meaning = Meaning::Meaning();
		meaning.getParseResult(input.content, MeCab::createTagger(""));
		mecab = meaning.getMeaningData();

		for (auto word = mecab.begin(); word != mecab.end(); word++) {
			if (word->means[0] == "Š´“®Œ") {
				if (word->phrase == "‚±‚ñ‚É‚¿‚Í")
					return searchTalkList("‚±‚ñ‚É‚¿‚Í");
				else if (word->phrase == "‚¨‚Í‚æ‚¤")
					return searchTalkList("‚¨‚Í‚æ‚¤");
				else if (word->phrase == "‚ ‚è‚ª‚Æ‚¤" || word->phrase == "‚·‚İ‚Ü‚¹‚ñ")
					return searchTalkList("Œª‘»");
				else if (word->phrase == "‚Ë‚¦" || word->phrase == "‚¨‚¢" || word->phrase == "‚ ‚Ì")
					return searchTalkList("‰“š");
			}
		}

		if (detectionWerewolf(mecab))
			input.tags.push_back("l˜T");

		std::vector<std::string> talk = searchTalkList(mecab);
/*		for (size_t i = 0; i < talk.size(); i++) {
			printf_s("%s\n", talk[i].c_str());
		}*/

		talk = searchTalkList(input.tags);
/*		for (size_t i = 0; i < talk.size(); i++) {
			printf_s("%s\n", talk[i].c_str());
		}*/

		if (talk.empty())
			return "ƒ{ƒb///";

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
		return "„‚Ìd–‚ÍlŠÔ‚ğP‚¤‚±‚ÆcI";
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
					if (talk_list[n].tags[fukkin] == "‘Şê") {
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
					if (talk_list[n].tags[fukkin] == "‘Şê"){
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
