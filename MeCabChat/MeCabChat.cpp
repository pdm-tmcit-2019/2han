#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <random>
#include <fstream>
#include <mecab.h>

#include "processes.h"
#include "Meaning.h"

constexpr auto template_name = "village_g10.csv";

typedef struct template_wolf
{
	std::string chapter;
	std::string name;
	std::string role;
	std::string talk;

	std::vector<OTA::mean_t> means;
	std::vector<std::string> mean_array;
} talk_t;

int main()
{
	std::string my_name = "ヴィレボット";
	std::vector<talk_t> talk;
	{
		std::ifstream templa(template_name);
		if (templa.fail()) {
			printf_s("テンプレートデータの取得に失敗しました。またのご利用をお待ちしております。\n");
			return -11;
		}

		std::vector<std::string> tmp;
		std::string str;

		while (std::getline(templa, str)) {
			tmp = OTA::split(str, ',');
			if (tmp.size() >= 3) {
				talk_t tmp_templa;
				tmp_templa.chapter = tmp[0];
				tmp_templa.name = tmp[1];
				tmp_templa.role = tmp[2];
				tmp_templa.talk = "";
				my_name = tmp_templa.name;

				for (size_t i = 3; i < tmp.size(); i++)
					tmp_templa.talk += tmp[i];
				
				talk.emplace_back(tmp_templa);
			} else {
				printf_s("ﾖｸﾞﾓｫ!ﾖｸｸﾓｵﾚﾀﾁｦﾀﾞﾏｼﾃｸﾚﾀﾅ!ｾﾞｯﾁｪﾕﾙｼｬﾈｪ!( 0`w'0)\n");
				return -13;
			}
		}
	}
	printf_s("テンプレートデータゲットー♪\nいいデータありがとうございます☆\n");
	printf_s("\n\n---------------------------------------------------\n\n");

	for (size_t i = 0; i < talk.size() - 1; i++) {
		OTA::Meaning meanings;
		bool wolflag = false/*, interrogative = false*/;

		meanings.getParseResult(talk[i].talk, MeCab::createTagger(""));
//		meanings.printPargeResult();
		talk[i].means = meanings.getMeaningData();

		if (talk[i].name == my_name)
			talk[i].mean_array.emplace_back("自分の発言");

		for (size_t j = 1; j < talk[i].means.size(); j++) {
			if ((talk[i].means[j - 1].phrase + talk[i].means[j].phrase == "人狼") && !wolflag) {
				talk[i].mean_array.emplace_back("人狼");
				wolflag = true;
			} else if ((talk[i].means[j].phrase == "?") || ((talk[i].means[j].phrase == "かしら")&&(talk[i].means[j].means[1]=="終助詞"))) {
				talk[i].mean_array.emplace_back("疑問文");
		//		printf_s("%s\n", talk[i].talk.c_str());
			} else if ((talk[i].means[j].phrase == ">>") && (talk[i].means[j + 1].means[1] == "数")) {
				int a = 0;
				talk[i].mean_array.emplace_back(talk[i].means[j + 1].phrase + "に言及");
			}

	//		if (talk[i].means[j].means[0] == "名詞")
	//			printf_s("来たー[%s]\n", talk[i].means[j].phrase.c_str());
		}
		talk[i].mean_array.emplace_back("人狼ゲーム");
//		printf_s("%4lu | %s\n", i, talk[i].mean_array);
	}

	std::random_device random0;
	std::uniform_int_distribution<> rnd(talk.size() / 5 * 3, talk.size() - 1);
	uint8_t flag[5] = {};
	for (size_t i = rnd(random0); i < talk.size() - 1; i++) {
		std::cout << i << " : ";
		for (int j = 0; j < talk[i].mean_array.size(); j++) std::cout << talk[i].mean_array[j];
		std::cout << std::endl;

		for (size_t j = 0; j < talk[i].mean_array.size(); j++) {
			if (talk[i].mean_array[j] == "自分の発言")
				break;
			else if (talk[i].mean_array[j] == "人狼ゲーム")
				flag[0]++;
			else if (talk[i].mean_array[j] == "疑問文")
				flag[1]++;
			else if (talk[i].mean_array[j] == "人狼")
				flag[2]++;
		}
	}

	if (flag[2] >= 1) {
		talk[talk.size() - 1].talk = "人狼ねえ…まさか本当に来るとは";
	} else if (flag[0] >= talk.size() / 5)
		talk[talk.size() - 1].talk = "とりあえずもう遅い、一回休もうぜ！";

	std::ofstream result("result.csv");
	if (result.fail()) {
		printf_s("結果を保存することが出来ないようで。\n");
		return -14;
	}

	for (size_t i = 0; i < talk.size(); i++)
		result << talk[i].chapter << "," << talk[i].name << "," << talk[i].role << "," << talk[i].talk << std::endl;

	result.close();

	return 0;
}
