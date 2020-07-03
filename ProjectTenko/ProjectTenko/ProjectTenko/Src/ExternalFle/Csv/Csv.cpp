#include "CSV.h"
#include <fstream>
#include <sstream>
#include <iostream>

bool Csv::Load(const std::string& fileName_, std::vector<std::vector<std::string>>& table_, const char delimiter_)
{
	// ファイルを開く
	std::fstream file_stream(fileName_);
	if (!file_stream.is_open())
	{
		// ファイルが開けなかった場合
		return false;
	}

	// ファイルを読み込む
	while (!file_stream.eof())
	{
		// 1行読み込む
		std::string buffer;
		file_stream >> buffer;

		// ファイルから読み込んだ1行の文字列を区切り文字で分けてリストに追加する
		std::vector<std::string> record;
		std::istringstream stream_buffer(buffer);
		std::string token;
		while (std::getline(stream_buffer, token, delimiter_))
		{
			// 1セル文の文字列をリストに追加する
			record.push_back(token);
		}

		// 1行分の文字列を引数のリストに追加する
		table_.push_back(record);
	}

	return true;
}

bool Csv::Create(const std::string& fileName_, std::vector<std::vector<std::string>>& table_)
{
	// ファイルを生成
	std::ofstream ofs(fileName_);
	if (!ofs.is_open())
	{
		// ファイルを生成できなかった場合
		return false;
	}

	// ファイルに書き込む
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
