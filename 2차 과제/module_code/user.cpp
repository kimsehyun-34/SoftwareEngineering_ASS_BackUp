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

User* currentUser = nullptr;

void signUp() {
    std::string userId, password, name, birthDate, phoneNumber;
    clearScreen();

    std::vector<User> users = loadUsers();

    std::cout << "회원가입을 진행합니다." << std::endl;
    std::cout << "사용자 ID: ";
    std::cin >> userId;

    if (!isUserIdUnique(userId, users)) {
        std::cout << "이미 존재하는 사용자 ID입니다. 다시 시도하십시오." << std::endl;
        return;
    }

    std::cout << "비밀번호: ";
    std::cin >> password;
    std::cout << "이름: ";
    std::cin >> name;
    std::cout << "생년월일 (YYYY-MM-DD): ";
    std::cin >> birthDate;
    std::cout << "전화번호: ";
    std::cin >> phoneNumber;

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
        if (hasOverdueVideos(*user)) {
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

bool isUserIdUnique(const std::string& userId, const std::vector<User>& users) {
    for (const auto& user : users) {
        if (user.userId == userId) {
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

bool hasOverdueVideos(const User& user) {
    std::time_t now = std::time(nullptr);
    const int rentalPeriod = 7 * 24 * 60 * 60;

    for (const auto& rental : user.rentedVideos) {
        std::time_t rentalDate = std::get<1>(rental);
        if (now - rentalDate > rentalPeriod) {
            return true;
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