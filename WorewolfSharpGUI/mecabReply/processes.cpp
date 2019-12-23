#include <iostream>
#include "processes.h"

namespace OTA {
	std::vector<std::string> split(const std::string &str, char sep)
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

	std::vector<std::string> split(const std::string& str, char sep, int max)
	{
		int i = 0;
		std::vector<std::string> v;        // �������ʂ��i�[����x�N�^�[
		auto first = str.begin();              // �e�L�X�g�̍ŏ����w���C�e���[�^
		while ((first != str.end()) || (i++ < max)) {         // �e�L�X�g���c���Ă���ԃ��[�v
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
}