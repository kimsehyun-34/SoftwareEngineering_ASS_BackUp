#include "search.h"
#include <iostream>
#include <fstream>
#include "clear_screen.h"

void search(const std::vector<std::pair<std::string, std::string>>& phonebook)
{
    clearScreen();
    std::string name;
    std::cout << "�˻��� �̸��� �Է��ϼ���: ";
    std::cin.ignore();
    std::getline(std::cin, name);

    bool found = false;
    for (const auto& contact : phonebook) {
        if (contact.first.find(name) != std::string::npos) {
            std::cout << "--------------------------" << std::endl;
            std::cout << "�̸�: " << contact.first << ", ��ȭ��ȣ: " << contact.second << std::endl;
            std::cout << "--------------------------" << std::endl;
            found = true;
        }
    }

    if (!found) {
        std::cout << "����ó�� ã�� �� �����ϴ�." << std::endl;
    }
}