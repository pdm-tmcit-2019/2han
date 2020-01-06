#include <iostream>
#include "Meaning.h"
#include "Talk.h"
#include <string.h>

#ifdef __cplusplus
#define DLLEXPORT __declspec(dllexport)
#else
#define DLLEXPORT __declspec(dllexport)
#endif

int main(std::string text)
{
	std::vector<OTA::mean_t> mean;
	//char a[256] = {};
	OTA::Talk talk;
	OTA::talk_t input;
	input.name = "たくのろじぃ";

	//while (true) {
		//gets_s(a, sizeof(a));
		input.content = text;
		std::cout << talk.replyTalk(input) << std::endl;
		OTA::Meaning(input.content).printPargeResult();

		/*if (END_DETECt) {
			break;
		}*/
	//}
	return 0;
}

//C#からの入力があって、出力を返す。
DLLEXPORT std::string __stdcall getFromCSharp(char* text)
{
	OTA::Talk talk;
	OTA::talk_t input;
	main(text);
	input.content = text;
	return talk.replyTalk(input);
}