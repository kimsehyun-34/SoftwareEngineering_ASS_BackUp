#include "file_io.h"
#include <fstream>

void saveToTxt(const std::vector<std::pair<std::string, std::string>>& phonebook)
{
    std::ofstream file("phonebook_nonjson.txt");
    for (const auto& contact : phonebook) {
        file << contact.first << "," << contact.second << "\n";
    }
}

void loadFromTxt(std::vector<std::pair<std::string, std::string>>& phonebook)
{
    std::ifstream file("phonebook_nonjson.txt");
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            size_t commaPos = line.find(",");
            if (commaPos != std::string::npos) {
                std::string name = line.substr(0, commaPos);
                std::string phoneNumber = line.substr(commaPos + 1);
                phonebook.push_back(std::make_pair(name, phoneNumber));
            }
        }
    }
}