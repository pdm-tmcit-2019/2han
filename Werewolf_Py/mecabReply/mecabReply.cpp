#include <iostream>
#include "Meaning.h"
#include "Talk.h"

#ifdef __cplusplus
#define DLLEXPORT extern "C" __declspec(dllexport)
#else
#define DLLEXPORT __declspec(dllexport)
#endif

int main(std::string text)
{
	std::vector<OTA::mean_t> mean;
	char a[256] = {};
	OTA::Talk talk;
	OTA::talk_t input;
	input.name = "たくのろじぃ";

	while (true) {
		gets_s(a, sizeof(a));
		input.content = a;
		std::cout << talk.replyTalk(input) << std::endl << std::endl;
//		OTA::Meaning(input.content).printPargeResult();

		if (END_DETECT) {
			break;
		}
	}

	return 0;
}

DLLEXPORT std::string FromPy(std::string text) {
	std::vector<OTA::mean_t> mean;
	OTA::Talk talk;
	OTA::talk_t input;
	//main(text);
	input.name = "たくのろじぃ";
	input.content = text;
	return talk.replyTalk(input);
}

DLLEXPORT void MainPy() {
	std::vector<OTA::mean_t> mean;
	char a[256] = {};
	OTA::Talk talk;
	OTA::talk_t input;
	input.name = "たくのろじぃ";

	while (true) {
		gets_s(a, sizeof(a));
		input.content = a;
		std::cout << talk.replyTalk(input) << std::endl << std::endl;
		//		OTA::Meaning(input.content).printPargeResult();

		if (END_DETECT) {
			break;
		}
	}
}

DLLEXPORT int TestPy(int a) {
	return a * 10;
}