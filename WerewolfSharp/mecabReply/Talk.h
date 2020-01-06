#ifndef TALK_H
#define TALK_H

#include "Meaning.h"
#include "processes.h"
#include <iostream>

#define END_DETECt (input.content == "終わり" || input .content== "end" || input .content== "END" || input .content== "終")

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
	};

	class Talk
	{
	public:
		Talk();
		Talk(char *name);

		void printAllTalkList();
		std::string replyTalk(talk_t input);
		std::vector<std::string> searchTalkList(std::vector<std::string> key);

	private:
		Meaning meaning;
		std::string myname;
		std::vector<lists> talk_list;

		std::string searchTalkList(const char *key);
		std::string insertNameTalk(std::string talk, std::string name);

		void setupTalkList();
		int getCSVFileData();
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

		return tmp[0] + name + tmp[1];
	}

}

#endif // !TALK_H
