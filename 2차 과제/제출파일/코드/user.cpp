#include "user.h"
#include "utils.h"
#include "admin.h"
#include "video.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <ctime>
#include <windows.h>
#include <regex>
#include <limits>

#undef max // 'max' 매크로 정의 해제

User* currentUser = nullptr;

void signUp() {
    std::string userId, password, name, birthDate, phoneNumber;

    std::regex phoneRegex("^(010-[0-9]{4}-[0-9]{4}|02-[0-9]{3,4}-[0-9]{4}|[0-6]{3}-[0-9]{3,4}-[0-9]{4})$"); // '-'가 포함된 전화번호의 정규 표현식
    std::regex phoneRegexNoDash("^(010[0-9]{8}|02[0-9]{7,8}|[0-6]{3}[0-9]{7,8})$"); // '-'가 미포함된 전화번호의 정규 표현식
    std::regex nameRegex("^[^0-9]+$"); // 숫자가 포함되지 않은 이름의 정규 표현식
    std::regex passwordRegex("^[^\uAC00-\uD7A3]+$"); // 한글이 포함되지 않은 비밀번호의 정규 표현식
    std::regex birthDateRegex("^[0-9-]+$"); // 한글과 영어가 포함되지 않은 생년월일의 정규 표현식

    clearScreen();

    std::vector<User> users = loadUsers();

    std::cout << "회원가입을 진행합니다." << std::endl;
    std::cout << "사용자 ID: ";
    std::cin >> userId;
    std::cin.ignore(); // 버퍼 비우기

    if (!isUserIdUnique(userId, users)) {
        std::cout << "이미 존재하는 사용자 ID입니다. 다시 시도하십시오." << std::endl;
        return;
    }

    while (true) {
        std::cout << "비밀번호: ";
        std::getline(std::cin, password);

        if (!std::regex_match(password, passwordRegex)) { // 비밀번호에 한글이 포함된 경우
            std::cout << "비밀번호에 한글이 포함될 수 없습니다. 다시 입력하세요." << std::endl;
        }
        else {
            break;
        }
    }

    while (true) {
        std::cout << "이름: ";
        std::getline(std::cin, name);

        if (name.empty()) { // 이름이 공백일 경우
            std::cout << "이름이 비어 있습니다. 다시 입력하세요." << std::endl;
        }
        else if (!std::regex_match(name, nameRegex)) { // 이름에 숫자가 포함된 경우
            std::cout << "이름에 숫자가 포함될 수 없습니다. 다시 입력하세요." << std::endl;
        }
        else {
            break;
        }
    }

    while (true) {
        std::cout << "생년월일 (YYYY-MM-DD): ";
        std::getline(std::cin, birthDate);

        if (!std::regex_match(birthDate, birthDateRegex)) { // 생년월일에 한글과 영어가 포함된 경우
            std::cout << "생년월일에 한글과 영어가 포함될 수 없습니다. 다시 입력하세요." << std::endl;
        }
        else {
            break;
        }
    }

    while (true) {
        std::cout << "전화번호: ";
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
        else if (std::regex_match(phoneNumber, phoneRegex)) { // - 있는 경우 패스
            break;
        }
        else {
            std::cout << "잘못된 전화번호 형식입니다. 전화번호는 010-xxxx-xxxx 또는 010xxxxxxxx 이거나 지역전화의 경우 (지역번호)-(x)xxx-xxxx, (지역번호)(x)xxxxxxx 형식이어야 합니다." << std::endl;
        }
    }

    if (!isPhoneNumberUnique(phoneNumber, users)) {
        std::cout << "이미 존재하는 사용자 전화번호 입니다. 다시 시도하십시오." << std::endl;
        return;
    }

    std::ofstream outfile("users.txt", std::ios_base::app);
    outfile << userId << "," << password << "," << name << "," << birthDate << "," << phoneNumber << ",0,0" << std::endl;

    std::cout << "회원가입이 완료되었습니다." << std::endl;
}

void login() {
    std::string userId, password;
    clearScreen();

    std::vector<User> users = loadUsers();

    std::cout << "로그인을 진행합니다." << std::endl;
    std::cout << "사용자 ID: ";
    std::cin >> userId;
    std::cout << "비밀번호: ";
    std::cin >> password;

    clearScreen();
    User* user = authenticateUser(userId, password, users);
    if (user) {
        currentUser = user;

        // 대여 비디오 정보를 로드하여 연체 여부 확인
        std::vector<std::tuple<std::string, std::string, std::time_t>> rentals = loadRentals();
        if (hasOverdueVideos(*user, rentals)) {
            std::cout << "***경고***  !!연체된 비디오가 있습니다!! ***경고***" << std::endl;
            Sleep(4000);
        }

        if (user->isAdmin) {
            adminMenu();
        }
        else {
            userMenu();
        }
    }
    else {
        std::cout << "로그인 실패. 사용자 ID 또는 비밀번호가 잘못되었습니다." << std::endl;
    }
}

bool isUserIdUnique(const std::string& userId, const std::vector<User>& users) { // ID 중복 조회
    for (const auto& user : users) {
        if (user.userId == userId) {
            return false;
        }
    }
    return true;
}

bool isPhoneNumberUnique(const std::string& phoneNumber, const std::vector<User>& users) { // 전화번호 중복 조회
    for (const auto& user : users) {
        if (user.phoneNumber == phoneNumber) {
            return false;
        }
    }
    return true;
}

User* authenticateUser(const std::string& userId, const std::string& password, std::vector<User>& users) {
    for (auto& user : users) {
        if (user.userId == userId && user.password == password) {
            return &user;
        }
    }
    return nullptr;
}

bool hasOverdueVideos(const User& user, const std::vector<std::tuple<std::string, std::string, std::time_t>>& rentals) {
    std::time_t now = std::time(nullptr);
    const int rentalPeriod = 7 * 24 * 60 * 60;

    for (const auto& rental : rentals) {
        if (std::get<0>(rental) == user.userId) {
            std::time_t rentalDate = std::get<2>(rental);
            if (now - rentalDate > rentalPeriod) {
                return true;
            }
        }
    }
    return false;
}

void userMenu() {
    int choice;
    while (true) {
        clearScreen();

        std::cout << "===== 사용자 메뉴 =====" << std::endl;
        std::cout << "보유 코인 수: " << currentUser->coins << std::endl;
        std::cout << "========================" << std::endl;

        std::cout << "1. 전체 비디오 목록" << std::endl;
        std::cout << "2. 비디오 대여" << std::endl;
        std::cout << "3. 대여 기간 확인" << std::endl;
        std::cout << "4. 로그아웃" << std::endl;
        std::cout << "선택: ";

        std::cin >> choice;

        if (std::cin.fail()) { // 문자가 들어올경우 실행(정수형입력에 실패한 경우)
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // 메뉴에서 문자 입력 무시
            continue;
        }

        switch (choice) {
        case 1:
            allVideo();
            break;
        case 2:
            rentVideo();
            break;
        case 3:
            checkRemainingDays();
            break;
        case 4:
            return;
        default:
            std::cout << "잘못된 선택입니다." << std::endl;
            break;
        }
        std::cout << "메뉴로 이동하려면 아무 키나 누르십시오...";
        std::cin.ignore();
        std::cin.get();
    }
}