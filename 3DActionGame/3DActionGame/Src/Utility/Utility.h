#ifndef UTILITY_H_
#define UTILITY_H_

#include <string>
#include <vector>

std::vector<std::string> Split(std::string str_, char del_);

void Replace(char searchChar_, char replaceChar_, char* buffer_);

#endif