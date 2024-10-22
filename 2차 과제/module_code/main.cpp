#include <iostream>
#include "user.h"
#include "admin.h"
#include "utils.h"

int main() {
    int choice;

    while (true) {
        clearScreen();

        std::cout << "메뉴를 선택하십시오:" << std::endl;
        std::cout << "1. 로그인" << std::endl;
        std::cout << "2. 회원가입" << std::endl;
        std::cout << "3. 종료" << std::endl;
        std::cout << "선택: ";

        std::cin >> choice;


        if (std::cin.fail()) { // 문자가 들어올경우 실행(정수형입력에 실패한 경우)
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // 메뉴에서 문자 입력 무시
            continue;
        }

        switch (choice) {
        case 1:
            login();
            break;
        case 2:
            signUp();
            break;
        case 3:
            std::cout << "프로그램을 종료합니다." << std::endl;
            return 0;
        default:
            std::cout << "잘못된 선택입니다." << std::endl;
            break;
        }
        std::cout << "메뉴로 이동하려면 아무 키나 누르십시오...";
        std::cin.ignore();
        std::cin.get();
    }

    return 0;
}