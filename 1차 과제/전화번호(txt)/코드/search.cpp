#include "search.h"
#include <iostream>
#include <fstream>
#include "clear_screen.h"

void search(const std::vector<std::pair<std::string, std::string>>& phonebook)
{
    clearScreen();
    std::string name;
    std::cout << "검색할 이름을 입력하세요: ";
    std::cin.ignore();
    std::getline(std::cin, name);

    bool found = false;
    for (const auto& contact : phonebook) {
        if (contact.first.find(name) != std::string::npos) {
            std::cout << "--------------------------" << std::endl;
            std::cout << "이름: " << contact.first << ", 전화번호: " << contact.second << std::endl;
            std::cout << "--------------------------" << std::endl;
            found = true;
        }
    }

    if (!found) {
        std::cout << "연락처를 찾을 수 없습니다." << std::endl;
    }
}