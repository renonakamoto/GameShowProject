#include "CSV.h"
#include <fstream>
#include <sstream>
#include <iostream>

bool Csv::Load(const std::string& fileName_, std::vector<std::vector<std::string>>& table_, const char delimiter_)
{
	// �t�@�C�����J��
	std::fstream file_stream(fileName_);
	if (!file_stream.is_open())
	{
		// �t�@�C�����J���Ȃ������ꍇ
		return false;
	}

	// �t�@�C����ǂݍ���
	while (!file_stream.eof())
	{
		// 1�s�ǂݍ���
		std::string buffer;
		file_stream >> buffer;

		// �t�@�C������ǂݍ���1�s�̕��������؂蕶���ŕ����ă��X�g�ɒǉ�����
		std::vector<std::string> record;
		std::istringstream stream_buffer(buffer);
		std::string token;
		while (std::getline(stream_buffer, token, delimiter_))
		{
			// 1�Z�����̕���������X�g�ɒǉ�����
			record.push_back(token);
		}

		// 1�s���̕�����������̃��X�g�ɒǉ�����
		table_.push_back(record);
	}

	return true;
}

bool Csv::Create(const std::string& fileName_, std::vector<std::vector<std::string>>& table_)
{
	// �t�@�C���𐶐�
	std::ofstream ofs(fileName_);
	if (!ofs.is_open())
	{
		// �t�@�C���𐶐��ł��Ȃ������ꍇ
		return false;
	}

	// �t�@�C���ɏ�������
	for (const auto& x : table_)
	{
		for (const auto& y : x)
		{
			ofs << y << ",";
		}
		ofs << std::endl;
	}

	return true;
}
