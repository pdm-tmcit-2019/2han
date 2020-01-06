#include "Talk.h"
#include <fstream>

namespace OTA {

	Talk::Talk()
	{
		myname = "���Αn�V��";

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

	void Talk::setupTalkList()
	{
		char talk[128] = {};

		sprintf_s(talk, "�F����͂��߂܂��āA�����͂��v���Ԃ�ł��B���͏o���ł��̑���K�ꂽ�d�C�H���m��%s�ł��B", myname.c_str());
		lists content;


		content.talk = talk;
		content.tags.emplace_back("���ȏЉ�");

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
				printf_s("���̍s�͓ǂݍ��߂܂���B\n");
				continue;
			}

			tlist.talk = data[0];
			tlist.tags = split(data[1], ':');

			if (tlist.tags[0] == "���ȏЉ�") {
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
			return searchTalkList("���ȏЉ�");
		} else if (END_DETECt) {
			return searchTalkList("�ޏ�");
		} else if (input.content == "���O�����̕������ďX���Ȃ����H") {
			return "�u�u�K��";
		}

		std::vector<mean_t> mecab;

		meaning.getParseResult(input.content, MeCab::createTagger(""));
		mecab = meaning.getMeaningData();
		meaning.clearInputString();

		for (auto word = mecab.begin(); word != mecab.end(); word++) {
			if (word->means[0] == "������") {
				if (word->phrase == "����ɂ���")
					return searchTalkList("����ɂ���");
				else if (word->phrase == "���͂悤")
					return searchTalkList("���͂悤");
				else if (word->phrase == "���肪�Ƃ�" || word->phrase == "���݂܂���")
					return searchTalkList("����");
				else if (word->phrase == "�˂�" || word->phrase == "����" || word->phrase == "����")
					return searchTalkList("����");
			}
		}

		std::vector<std::string> key;
		key.emplace_back("�l�T");
		key.emplace_back("����");


		std::vector<std::string> talk = searchTalkList(key);
		for (size_t i = 0; i < talk.size(); i++) {
			printf_s("%s\n", talk[i].c_str());
		}

		return "�{�b///";
	}

	std::string Talk::searchTalkList(const char* key)
	{
		for (size_t i = 0; i < talk_list.size(); i++) {
			for (size_t j = 0; j < talk_list[i].tags.size(); j++) {
				if (talk_list[i].tags[j] == key)
					return talk_list[i].talk;
			}
		}
		return "���̎d���͐l�Ԃ��P�����Ɓc�I";
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
