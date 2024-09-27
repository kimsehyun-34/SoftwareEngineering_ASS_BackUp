#include "display.h"
#include <iostream>
#include <algorithm>

// ����� ���� �� �Լ�
bool compareContacts(const std::pair<std::string, std::string>& a, const std::pair<std::string, std::string>& b) {
    return a.first < b.first;
}

void displayAllContacts(const std::vector<std::pair<std::string, std::string>>& phonebook)
{
    if (phonebook.empty()) {
        std::cout << "����ó�� �����ϴ�." << std::endl;
        return;
    }

    // ���ĵ� ���纻�� ����� ���� ���͸� ����
    std::vector<std::pair<std::string, std::string>> sortedPhonebook = phonebook;
    std::sort(sortedPhonebook.begin(), sortedPhonebook.end(), compareContacts);

    std::cout << "-------------------------" << std::endl;
    for (const auto& contact : sortedPhonebook) {
        std::cout << "�̸�: " << contact.first << " , ��ȭ��ȣ: " << contact.second << std::endl;
        std::cout << "-------------------------" << std::endl;
    }
}