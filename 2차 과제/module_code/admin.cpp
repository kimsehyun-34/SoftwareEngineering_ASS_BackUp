#include "admin.h"
#include "utils.h"
#include "user.h"
#include "video.h"
#include <iostream>
#include <fstream>
#include <algorithm>

void adminMenu() {
    int choice;

    while (true) {
        clearScreen();

        std::cout << "===== 관리자 메뉴 =====" << std::endl;
        std::cout << "1. 비디오 추가" << std::endl;
        std::cout << "2. 비디오 삭제" << std::endl;
        std::cout << "3. 사용자에게 코인 추가" << std::endl;
        std::cout << "4. 비디오 삭제" << std::endl;
        std::cout << "5. 대여 상태 확인" << std::endl;
        std::cout << "6. 로그아웃" << std::endl;
        std::cout << "선택: ";
        std::cin >> choice;

        switch (choice) {
        case 1:
            addVideo();
            break;
        case 2:
            returnVideo();
            break;
        case 3:
            addCoinsToUser();
            break;
        case 4:
            delVideo();
            break;
        case 5:
            checkVideoRentalStatus();
            break;
        case 6:
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

void addCoinsToUser() {
    std::string userId;
    int coinsToAdd;
    clearScreen();

    std::vector<User> users = loadUsers();

    std::cout << "코인을 추가할 사용자 ID: ";
    std::cin >> userId;

    auto it = std::find_if(users.begin(), users.end(), [&userId](const User& user) {
        return user.userId == userId;
        });

    if (it == users.end()) {
        std::cout << "사용자를 찾을 수 없습니다." << std::endl;
        return;
    }

    std::cout << "추가할 코인 수: ";
    std::cin >> coinsToAdd;

    it->coins += coinsToAdd;

    std::ofstream userFile("users.txt");
    for (const auto& user : users) {
        userFile << user.userId << "," << user.password << "," << user.name << "," << user.birthDate << "," << user.phoneNumber << "," << user.isAdmin << "," << user.coins << std::endl;
    }

    std::cout << "코인이 추가되었습니다." << std::endl;
}

void addVideo() { // 비디오 추가 기능
    std::string videoName;
    clearScreen();

    std::cout << "비디오 추가를 시작합니다." << std::endl;
    std::cout << "비디오 이름: ";
    std::cin.ignore(); // 이전 입력의 개행 문자를 무시
    std::getline(std::cin, videoName);

    // 현재 비디오의 개수를 확인하여 순서를 결정
    std::ifstream infile("videos.txt");
    int videoCount = 0;
    std::string line;
    while (std::getline(infile, line)) {
        videoCount++;
    }
    infile.close();

    // 비디오 정보를 파일에 저장
    std::ofstream outfile("videos.txt", std::ios_base::app);
    outfile << videoCount + 1 << ". " << videoName << std::endl;

    std::cout << "비디오 추가가 완료되었습니다." << std::endl;
}

void delVideo() {
    std::string videoName;
    clearScreen();

    std::cout << "비디오 삭제를 진행합니다." << std::endl;
    std::cout << "비디오 이름: ";
    std::cin.ignore();
    std::getline(std::cin, videoName);

    std::ifstream infile("videos.txt");
    std::vector<std::string> videoList;
    std::string line;
    while (std::getline(infile, line)) {
        videoList.push_back(line);
    }
    infile.close();

    std::vector<int> indices;
    for (size_t i = 0; i < videoList.size(); ++i) {
        if (videoList[i].find(videoName) != std::string::npos) {
            indices.push_back(i);
        }
    }

    if (indices.empty()) {
        std::cout << "해당 이름의 비디오를 찾을 수 없습니다." << std::endl;
        return;
    }

    std::cout << "삭제할 비디오를 선택하십시오" << std::endl;
    std::cout << "------------------------------------" << std::endl;
    for (size_t i = 0; i < indices.size(); ++i) {
        std::cout << i + 1 << ". " << videoList[indices[i]] << std::endl;
    }

    int choice;
    std::cout << "선택: ";
    std::cin >> choice;

    if (choice < 1 || choice > indices.size()) {
        std::cout << "잘못된 선택입니다. 작업이 취소되었습니다." << std::endl;
        return;
    }

    videoList.erase(videoList.begin() + indices[choice - 1]);
    std::cout << "삭제 완료." << std::endl;

    std::ofstream outfile("videos.txt");
    for (const auto& video : videoList) {
        outfile << video << std::endl;
    }
    outfile.close();
}

void addadmin() {
    std::string userId, password, name, birthDate, phoneNumber;
    clearScreen();

    std::vector<User> users = loadUsers();

    std::cout << "관리자 추가를 진행합니다." << std::endl;
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
    outfile << userId << "," << password << "," << name << "," << birthDate << "," << phoneNumber << ",1,0" << std::endl;

    std::cout << "관리자가 추가되었습니다." << std::endl;
}