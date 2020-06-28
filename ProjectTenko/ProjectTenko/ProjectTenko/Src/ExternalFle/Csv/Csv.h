#ifndef CSV_H_
#define CSV_H_

#include <vector>
#include <string>

class Csv
{
public:
	static bool Load(const std::string& fileName_, std::vector<std::vector<std::string>>& table_, const char delimiter_ = ',');

	static bool Create(const std::string& fileName_, std::vector<std::vector<std::string>>& table_, const char delimiter_ = ',');
};

#endif