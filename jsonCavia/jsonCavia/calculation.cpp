#include "calculation.h"

namespace OTA {
	std::vector<std::string> split(const std::string& str, char sep)
	{
		std::vector<std::string> v;        // �������ʂ��i�[����x�N�^�[
		auto first = str.begin();              // �e�L�X�g�̍ŏ����w���C�e���[�^
		while (first != str.end()) {         // �e�L�X�g���c���Ă���ԃ��[�v
			auto last = first;                      // ���������񖖔��ւ̃C�e���[�^
			while (last != str.end() && *last != sep)       // ���� or �Z�p���[�^�����܂Ői�߂�
				++last;
			v.push_back(std::string(first, last));       // �����������o��
			if (last != str.end())
				++last;
			first = last;          // ���̏����̂��߂ɃC�e���[�^��ݒ�
		}
		return v;
	}

	int getCSVFileData(const char* name, std::vector<std::vector<std::string>>* csv_data)
	{
		std::string line;

		std::ifstream ifs(name);
		if (ifs.fail()) {
			printf_s("csv input error.\n");
			return -11;
		}
		printf_s("csv input successful.\n");

		while (getline(ifs, line)) {
			csv_data->emplace_back(split(line, ','));
		}

		ifs.close();

		return 0;
	}
}
