#include "display.h"
#include <iostream>
#include <algorithm>

// 사용자 정의 비교 함수
bool compareContacts(const std::pair<std::string, std::string>& a, const std::pair<std::string, std::string>& b) {
    return a.first < b.first;
}

void displayAllContacts(const std::vector<std::pair<std::string, std::string>>& phonebook)
{
    if (phonebook.empty()) {
        std::cout << "연락처가 없습니다." << std::endl;
        return;
    }

    // 정렬된 복사본을 만들기 위해 벡터를 복사
    std::vector<std::pair<std::string, std::string>> sortedPhonebook = phonebook;
    std::sort(sortedPhonebook.begin(), sortedPhonebook.end(), compareContacts);

    std::cout << "-------------------------" << std::endl;
    for (const auto& contact : sortedPhonebook) {
        std::cout << "이름: " << contact.first << " , 전화번호: " << contact.second << std::endl;
        std::cout << "-------------------------" << std::endl;
    }
}