#ifndef CORR_H
#define CORR_H

#include <vector>
#include <string>

void corr(std::vector<std::pair<std::string, std::string>>& phonebook);
void modifyName(std::vector<std::pair<std::string, std::string>>& phonebook, int index);
void modifyPhoneNumber(std::vector<std::pair<std::string, std::string>>& phonebook, int index);

#endif