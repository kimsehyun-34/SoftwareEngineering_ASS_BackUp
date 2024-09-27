#include "addition.h"
#include <iostream>
#include <regex>
#include "file_io.h"
#include "clear_screen.h"

void addition(std::vector<std::pair<std::string, std::string>>& phonebook)
{
    std::string name, phoneNumber;
    std::regex phoneRegex("^(010-[0-9]{4}-[0-9]{4}|02-[0-9]{3,4}-[0-9]{4}|[0-6]{3}-[0-9]{3,4}-[0-9]{4})$");
    std::regex phoneRegexNoDash("^(010[0-9]{8}|02[0-9]{7,8}|[0-6]{3}[0-9]{7,8})$");

    while (true) {
        clearScreen();

        std::cout << "이름: ";
        std::cin.ignore();
        std::getline(std::cin, name);

        if (name.empty()) {
            std::cout << "이름이 비어 있습니다. 다시 입력하세요." << std::endl;
        }
        else {
            break;
        }
    }

    while (true)
    {
        std::cout << "전화번호(해외번호의 경우 '-'와 함께 입력): ";
        std::getline(std::cin, phoneNumber);

        if (phoneNumber.empty()) {
            std::cout << "전화번호가 비어 있습니다. 다시 입력해 주세요." << std::endl;
        }
        else if (std::regex_match(phoneNumber, phoneRegexNoDash)) { // - 추가
            if (phoneNumber.substr(0, 2) == "02" && phoneNumber.length() == 9) { // 서울지역번호 2자리-3자리-4자리
                phoneNumber = phoneNumber.substr(0, 2) + "-" + phoneNumber.substr(2, 3) + "-" + phoneNumber.substr(5, 4);
            }
            else if (phoneNumber.substr(0, 2) == "02" && phoneNumber.length() == 10) { // 서울지역번호 2자리-4자리-4자리
                phoneNumber = phoneNumber.substr(0, 2) + "-" + phoneNumber.substr(2, 4) + "-" + phoneNumber.substr(6, 4);
            }
            else if ((phoneNumber.substr(0, 3) == "031" || phoneNumber.substr(0, 3) == "032" || phoneNumber.substr(0, 3) == "042" ||
                phoneNumber.substr(0, 3) == "051" || phoneNumber.substr(0, 3) == "052" || phoneNumber.substr(0, 3) == "053" ||
                phoneNumber.substr(0, 3) == "062" || phoneNumber.substr(0, 3) == "064" || phoneNumber.substr(0, 3) == "033" ||
                phoneNumber.substr(0, 3) == "041" || phoneNumber.substr(0, 3) == "043" || phoneNumber.substr(0, 3) == "054" ||
                phoneNumber.substr(0, 3) == "055" || phoneNumber.substr(0, 3) == "061" || phoneNumber.substr(0, 3) == "063") &&
                phoneNumber.length() == 10) { // 지역번호 3자리-3자리-4자리
                phoneNumber = phoneNumber.substr(0, 3) + "-" + phoneNumber.substr(3, 3) + "-" + phoneNumber.substr(6, 4);
            }
            else if ((phoneNumber.substr(0, 3) == "031" || phoneNumber.substr(0, 3) == "032" || phoneNumber.substr(0, 3) == "042" ||
                phoneNumber.substr(0, 3) == "051" || phoneNumber.substr(0, 3) == "052" || phoneNumber.substr(0, 3) == "053" ||
                phoneNumber.substr(0, 3) == "062" || phoneNumber.substr(0, 3) == "064" || phoneNumber.substr(0, 3) == "033" ||
                phoneNumber.substr(0, 3) == "041" || phoneNumber.substr(0, 3) == "043" || phoneNumber.substr(0, 3) == "054" ||
                phoneNumber.substr(0, 3) == "055" || phoneNumber.substr(0, 3) == "061" || phoneNumber.substr(0, 3) == "063") &&
                phoneNumber.length() == 11) { // 지역번호 3자리-4자리-4자리
                phoneNumber = phoneNumber.substr(0, 3) + "-" + phoneNumber.substr(3, 4) + "-" + phoneNumber.substr(7, 4);
            }
            else if (phoneNumber.substr(0, 3) == "010" && phoneNumber.length() == 11) {
                phoneNumber = phoneNumber.substr(0, 3) + "-" + phoneNumber.substr(3, 4) + "-" + phoneNumber.substr(7, 4); // 휴대폰번호 010-4자리-4자리
            }
            else {
                std::cout << "잘못된 전화번호 형식입니다. 다시 입력해 주세요." << std::endl;
                continue;
            }
            break;
        }
        else if (std::regex_match(phoneNumber, phoneRegex)) {// - 있는경우 패스
            break;
        }
        else {
            std::cout << "잘못된 전화번호 형식입니다. 전화번호는 010-xxxx-xxxx 또는 010xxxxxxxx 이거나 지역전화의 경우 (지역번호)-(x)xxx-xxxx, (지역번호)(x)xxxxxxx 형식이어야 합니다." << std::endl;
        }
    }

    for (const auto& contact : phonebook) {
        if (contact.second == phoneNumber) {
            std::cout << "중복된 전화번호가 이미 존재합니다." << std::endl;
            return;
        }
    }

    phonebook.push_back(std::make_pair(name, phoneNumber));
    std::cout << "추가 완료!" << std::endl;

    saveToTxt(phonebook);
}
