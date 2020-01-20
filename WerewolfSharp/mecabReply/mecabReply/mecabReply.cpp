#include <iostream>
#include "Meaning.h"
#include "Talk.h"

int main()
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
