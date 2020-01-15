#ifndef TALK_H
#define TALK_H

#include "Meaning.h"
#include "processes.h"
#include <iostream>
#include <random>

#define END_DETECT (input.content == "終わり" || input .content== "end" || input .content== "END" || input .content== "終")

namespace OTA {
	struct lists
	{
		std::string talk;
		std::vector <std::string> tags;
	};

	struct talk_t
	{
		std::string name;
		std::string content;
		std::vector<std::string> tags;
	};

	class Talk
	{
	public:
		Talk();
		Talk(char *name);

		void printAllTalkList();
		std::string replyTalk(talk_t input);
		std::string searchTalkList(std::string key);
		std::vector<std::string> searchTalkList(std::vector<std::string> key);
		std::vector<std::string> searchTalkList(std::vector<mean_t> key);

	private:
		Meaning meaning;
		std::string myname, yourname;
		std::vector<lists> talk_list;
		std::random_device rnd;
		std::mt19937 mt;

		std::string insertNameTalk(std::string talk, std::string name);

		void setupTalkList();
		int getCSVFileData();
		bool detectionWerewolf(std::vector<mean_t> input);
	};

	inline void Talk::printAllTalkList()
	{
		for (size_t i = 0; i < talk_list.size(); i++) {
			std::cout << talk_list[i].talk << std::endl << "タグ:";
			for (size_t tag = 0; tag < talk_list[i].tags.size(); tag++) {
				std::cout << talk_list[i].tags[tag] << ", ";
			}

			printf_s("\n\n");
		}
	}

	inline std::string Talk::insertNameTalk(std::string talk, std::string name)
	{
		std::vector<std::string> tmp = split(talk, '@');

		if (tmp.size() >= 2)
			return tmp[0] + name + tmp[1];
		return tmp[0];
	}

	inline bool Talk::detectionWerewolf(std::vector<mean_t> input)
	{
		for (size_t i = 0; i < input.size() - 1; i++) {
			if (input[i].phrase + input[i + 1].phrase == "人狼") {
				return true;
			}
		}

		return false;
	}

}

#endif // !TALK_H
