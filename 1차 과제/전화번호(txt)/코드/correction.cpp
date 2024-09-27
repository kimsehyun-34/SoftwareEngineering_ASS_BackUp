#include "correction.h"
#include <iostream>
#include <regex>
#include "file_io.h"
#include "clear_screen.h"


void corr(std::vector<std::pair<std::string, std::string>>& phonebook)
{
    clearScreen();
    std::string name;
    std::cout << "수정할 연락처의 이름: ";
    std::cin.ignore(); // 버퍼 비우기
    std::getline(std::cin, name);

    std::vector<int> indices;
    for (size_t i = 0; i < phonebook.size(); ++i) {
        if (phonebook[i].first == name) {
            indices.push_back(static_cast<int>(i)); // 수정된 부분
        }
    }

    if (indices.empty()) {
        std::cout << "연락처를 찾을 수 없습니다." << std::endl;
        return;
    }

    std::cout << "==== 검색된 연락처 ====" << std::endl;
    for (size_t i = 0; i < indices.size(); ++i) {
        std::cout << i + 1 << ". 이름: " << phonebook[indices[i]].first << ", 전화번호: " << phonebook[indices[i]].second << std::endl;
    }

    int contactChoice;
    std::cout << "수정할 연락처의 번호를 입력하세요: ";
    std::cin >> contactChoice;

    if (contactChoice < 1 || contactChoice > static_cast<int>(indices.size())) {
        std::cout << "잘못된 선택입니다. 다시 시도하세요." << std::endl;
        return;
    }

    int index = indices[contactChoice - 1];

    int choice;
    std::cout << "==== 수정하고 싶은 항목을 선택해 주세요 ====" << std::endl;
    std::cout << "1. 이름 수정" << std::endl;
    std::cout << "2. 전화번호 수정" << std::endl;
    std::cout << "숫자를 입력하여 선택: ";
    std::cin >> choice;

    switch (choice) {
    case 1:
        modifyName(phonebook, index); // 수정된 부분
        break;
    case 2:
        modifyPhoneNumber(phonebook, index); // 수정된 부분
        break;
    default:
        std::cout << "잘못된 선택입니다. 다시 시도하세요." << std::endl;
        break;
    }

    // 연락처 수정 후 자동으로 TXT 파일에 저장
    saveToTxt(phonebook);
}


// 이름을 수정하는 함수
void modifyName(std::vector<std::pair<std::string, std::string>>& phonebook, int index) {
    std::string newName;
    std::cout << "새 이름을 입력하세요: ";
    std::cin.ignore();
    std::getline(std::cin, newName);

    phonebook[index].first = newName;
    std::cout << "이름이 수정되었습니다." << std::endl;
}

// 전화번호 수정
void modifyPhoneNumber(std::vector<std::pair<std::string, std::string>>& phonebook, int index) {
    std::string newPhoneNumber;
    std::regex phoneRegex("^(010-[0-9]{4}-[0-9]{4}|02-[0-9]{3,4}-[0-9]{4}|[0-6]{3}-[0-9]{3,4}-[0-9]{4})$"); // 전화번호 형식 정규표현식
    std::regex phoneRegexNoDash("^(010[0-9]{8}|02[0-9]{7,8}|[0-6]{3}[0-9]{7,8})$"); // 전화번호 형식 정규표현식

    while (true) {
        std::cout << "새 전화번호를 입력하세요: ";
        std::cin.ignore();
        std::getline(std::cin, newPhoneNumber);

        if (newPhoneNumber.empty()) {
            std::cout << "전화번호가 비어 있습니다. 다시 입력해 주세요." << std::endl;
        }
        else if (std::regex_match(newPhoneNumber, phoneRegexNoDash)) { // - 추가
            if (newPhoneNumber.substr(0, 2) == "02" && newPhoneNumber.length() == 9) { // 서울지역번호 2자리-3자리-4자리
                newPhoneNumber = newPhoneNumber.substr(0, 2) + "-" + newPhoneNumber.substr(2, 3) + "-" + newPhoneNumber.substr(5, 4);
            }
            else if (newPhoneNumber.substr(0, 2) == "02" && newPhoneNumber.length() == 10) { // 서울지역번호 2자리-4자리-4자리
                newPhoneNumber = newPhoneNumber.substr(0, 2) + "-" + newPhoneNumber.substr(2, 4) + "-" + newPhoneNumber.substr(6, 4);
            }
            else if ((newPhoneNumber.substr(0, 3) == "031" || newPhoneNumber.substr(0, 3) == "032" || newPhoneNumber.substr(0, 3) == "042" ||
                newPhoneNumber.substr(0, 3) == "051" || newPhoneNumber.substr(0, 3) == "052" || newPhoneNumber.substr(0, 3) == "053" ||
                newPhoneNumber.substr(0, 3) == "062" || newPhoneNumber.substr(0, 3) == "064" || newPhoneNumber.substr(0, 3) == "033" ||
                newPhoneNumber.substr(0, 3) == "041" || newPhoneNumber.substr(0, 3) == "043" || newPhoneNumber.substr(0, 3) == "054" ||
                newPhoneNumber.substr(0, 3) == "055" || newPhoneNumber.substr(0, 3) == "061" || newPhoneNumber.substr(0, 3) == "063") &&
                newPhoneNumber.length() == 10) { // 지역번호 3자리-3자리-4자리
                newPhoneNumber = newPhoneNumber.substr(0, 3) + "-" + newPhoneNumber.substr(3, 3) + "-" + newPhoneNumber.substr(6, 4);
            }
            else if ((newPhoneNumber.substr(0, 3) == "031" || newPhoneNumber.substr(0, 3) == "032" || newPhoneNumber.substr(0, 3) == "042" ||
                newPhoneNumber.substr(0, 3) == "051" || newPhoneNumber.substr(0, 3) == "052" || newPhoneNumber.substr(0, 3) == "053" ||
                newPhoneNumber.substr(0, 3) == "062" || newPhoneNumber.substr(0, 3) == "064" || newPhoneNumber.substr(0, 3) == "033" ||
                newPhoneNumber.substr(0, 3) == "041" || newPhoneNumber.substr(0, 3) == "043" || newPhoneNumber.substr(0, 3) == "054" ||
                newPhoneNumber.substr(0, 3) == "055" || newPhoneNumber.substr(0, 3) == "061" || newPhoneNumber.substr(0, 3) == "063") &&
                newPhoneNumber.length() == 11) { // 지역번호 3자리-4자리-4자리
                newPhoneNumber = newPhoneNumber.substr(0, 3) + "-" + newPhoneNumber.substr(3, 4) + "-" + newPhoneNumber.substr(7, 4);
            }
            else if (newPhoneNumber.substr(0, 3) == "010" && newPhoneNumber.length() == 11) {
                newPhoneNumber = newPhoneNumber.substr(0, 3) + "-" + newPhoneNumber.substr(3, 4) + "-" + newPhoneNumber.substr(7, 4); // 휴대폰번호 010-4자리-4자리
            }
            else {
                std::cout << "잘못된 전화번호 형식입니다. 다시 입력해 주세요." << std::endl;
                continue;
            }
            break;
        }
        else if (std::regex_match(newPhoneNumber, phoneRegex)) {// - 있는경우 패스
            break;
        }
        else {
            std::cout << "잘못된 전화번호 형식입니다. 전화번호는 010-xxxx-xxxx 또는 010xxxxxxxx 이거나 지역전화의 경우 (지역번호)-(x)xxx-xxxx, (지역번호)(x)xxxxxxx 형식이어야 합니다." << std::endl;
        }
    }

    phonebook[index].second = newPhoneNumber;
    std::cout << "전화번호가 수정되었습니다." << std::endl;
}
