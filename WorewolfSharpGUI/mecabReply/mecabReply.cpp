#include <iostream>
#include "Meaning.h"
#include "Talk.h"

#include <string.h>


#ifdef __cplusplus
#define DLLEXPORT extern "C" __declspec(dllexport)
#else
#define DLLEXPORT __declspec(dllexport)
#endif

int main(std::string dest)
{
	OTA::Meaning meaning;
	std::vector<OTA::mean_t> meanings;
	char a[256] = {};
	//a = dest;
	OTA::Talk talk;
	OTA::talk_t input;
	input.name = "たくのろじぃ";

	//while (true) {
		//gets_s(dest, sizeof(dest));
		input.content = dest;
		std::cout << "C#から渡された値は " << dest << " です" << std::endl; //DLL引数渡す用
		std::cout << talk.replyTalk(input) << std::endl;

		if (END_DETECt) {
			//break;
		}
	//}

	return 0;
}

//C#からの入力
DLLEXPORT void __stdcall mystrcpy(char* dest)
{
	main(dest);
}

