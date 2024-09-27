#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include "addition.h"
#include "search.h"
#include "correction.h"
#include "delete.h"
#include "file_io.h"
#include "display.h"
#include "clear_screen.h"

std::vector<std::pair<std::string, std::string>> phonebook;

int main()
{
    loadFromTxt(phonebook);

    int choice;

    while (true) {
        clearScreen();

        std::cout << "========메뉴 선택=======" << std::endl;
        std::cout << "1. 연락처 추가" << std::endl;
        std::cout << "2. 연락처 검색" << std::endl;
        std::cout << "3. 연락처 수정" << std::endl;
        std::cout << "4. 연락처 삭제" << std::endl;
        std::cout << "5. 연락처 전체 보기" << std::endl;
        std::cout << "6. 프로그램 종료" << std::endl;
        std::cout << "====================" << std::endl;
        std::cout << "번호를 입력하세요: ";

        std::cin >> choice;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        switch (choice) {
        case 1:
            addition(phonebook);
            break;
        case 2:
            search(phonebook);
            break;
        case 3:
            corr(phonebook);
            break;
        case 4:
            del(phonebook);
            break;
        case 5:
            displayAllContacts(phonebook);
            break;
        case 6:
            saveToTxt(phonebook);
            std::cout << "프로그램을 종료합니다." << std::endl;
            return 0;
        default:
            std::cout << "잘못된 선택입니다. 다시 시도하세요." << std::endl;
            break;
        }

        std::cout << "메뉴로 이동하려면 아무 키나 누르세요...";
        std::cin.ignore();
        std::cin.get();
    }

    return 0;
}