#include "delete.h"
#include <iostream>
#include <algorithm>
#include "file_io.h"
#include "clear_screen.h"

void del(std::vector<std::pair<std::string, std::string>>& phonebook)
{
    clearScreen();
    std::string name;
    std::cout << "삭제할 연락처의 이름: ";
    std::cin.ignore(); // 버퍼 비우기
    std::getline(std::cin, name);

    std::vector<int> indices;
    for (size_t i = 0; i < phonebook.size(); ++i) {
        if (phonebook[i].first == name) {
            indices.push_back(i);
        }
    }

    if (indices.empty()) {
        std::cout << "연락처를 찾을 수 없습니다." << std::endl;
        return;
    }

    std::cout << "----------------------" << std::endl;
    for (size_t i = 0; i < indices.size(); ++i) {
        std::cout << i + 1 << ". 이름: " << phonebook[indices[i]].first << " , 전화번호: " << phonebook[indices[i]].second << std::endl;
    }
    std::cout << "----------------------" << std::endl;
    std::cout << "삭제할 연락처의 번호를 입력하세요: ";

    size_t choice;
    std::cin >> choice;

    if (choice < 1 || choice > indices.size()) {
        std::cout << "잘못된 선택입니다. 삭제가 취소되었습니다." << std::endl;
        return;
    }

    phonebook.erase(phonebook.begin() + indices[choice - 1]);
    std::cout << "삭제 완료." << std::endl;
    // 연락처 삭제 후 자동으로 TXT 파일에 저장
    saveToTxt(phonebook);
}
