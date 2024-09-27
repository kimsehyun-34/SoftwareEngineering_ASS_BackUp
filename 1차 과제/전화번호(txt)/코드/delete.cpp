#include "delete.h"
#include <iostream>
#include <algorithm>
#include "file_io.h"
#include "clear_screen.h"

void del(std::vector<std::pair<std::string, std::string>>& phonebook)
{
    clearScreen();
    std::string name;
    std::cout << "������ ����ó�� �̸�: ";
    std::cin.ignore(); // ���� ����
    std::getline(std::cin, name);

    std::vector<int> indices;
    for (size_t i = 0; i < phonebook.size(); ++i) {
        if (phonebook[i].first == name) {
            indices.push_back(i);
        }
    }

    if (indices.empty()) {
        std::cout << "����ó�� ã�� �� �����ϴ�." << std::endl;
        return;
    }

    std::cout << "----------------------" << std::endl;
    for (size_t i = 0; i < indices.size(); ++i) {
        std::cout << i + 1 << ". �̸�: " << phonebook[indices[i]].first << " , ��ȭ��ȣ: " << phonebook[indices[i]].second << std::endl;
    }
    std::cout << "----------------------" << std::endl;
    std::cout << "������ ����ó�� ��ȣ�� �Է��ϼ���: ";

    size_t choice;
    std::cin >> choice;

    if (choice < 1 || choice > indices.size()) {
        std::cout << "�߸��� �����Դϴ�. ������ ��ҵǾ����ϴ�." << std::endl;
        return;
    }

    phonebook.erase(phonebook.begin() + indices[choice - 1]);
    std::cout << "���� �Ϸ�." << std::endl;
    // ����ó ���� �� �ڵ����� TXT ���Ͽ� ����
    saveToTxt(phonebook);
}
