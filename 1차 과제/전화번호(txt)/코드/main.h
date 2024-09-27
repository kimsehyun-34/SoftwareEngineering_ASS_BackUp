#ifndef PHONEBOOK_H
#define PHONEBOOK_H

#include <string>
#include <vector>

void addition();
void search();
void corr();
void del();
void clearScreen();
void saveToTxt();
void loadFromTxt();
void displayAllContacts();
void searchInTxt(const std::string& name);
void modifyName(const std::string& oldName);
void modifyPhoneNumber(const std::string& name);

extern std::vector<std::pair<std::string, std::string>> phonebook;

#endif // PHONEBOOK_H
