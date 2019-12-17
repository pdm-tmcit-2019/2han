#include <iostream>
#include "Meaning.h"
#include "Talk.h"

int main()
{
	OTA::Meaning meaning;
	std::vector<OTA::mean_t> meanings;
	char a[256] = {};
	OTA::Talk talk;
	OTA::talk_t input;
	input.name = "たくのろじぃ";

	while (true) {
		gets_s(a, sizeof(a));
		input.content = a;
		std::cout << talk.replyTalk(input) << std::endl;

		if (END_DETECt) {
			break;
		}
	}

	return 0;
}
