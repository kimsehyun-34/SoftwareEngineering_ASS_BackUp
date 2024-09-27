#ifndef FILE_IO_H
#define FILE_IO_H

#include <vector>
#include <string>

void saveToTxt(const std::vector<std::pair<std::string, std::string>>& phonebook);
void loadFromTxt(std::vector<std::pair<std::string, std::string>>& phonebook);

#endif