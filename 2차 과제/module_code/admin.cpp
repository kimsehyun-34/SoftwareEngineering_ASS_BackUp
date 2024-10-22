#include "admin.h"
#include "utils.h"
#include "user.h"
#include "video.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <limits>

// 보안: ctime_s는 버퍼 오버플로우를 방지하는 안전한 함수입니다.
// 호환성 : 기존 코드와 쉽게 통합할 수 있습니다.
// 간단함 : 구현이 간단하고 이해하기 쉽습니다.

void adminMenu() {
    int choice;

    while (true) {
        clearScreen();

        std::cout << "===== 관리자 메뉴 =====" << std::endl;
        std::cout << "1. 비디오 추가" << std::endl;
        std::cout << "2. 비디오 반납" << std::endl;
        std::cout << "3. 사용자에게 코인 추가" << std::endl;
        std::cout << "4. 비디오 삭제" << std::endl;
        std::cout << "5. 대여 상태 확인" << std::endl;
        std::cout << "6. 모든 사용자 출력" << std::endl; // 새로운 메뉴 항목 추가
        std::cout << "7. 관리자 추가" << std::endl;
        std::cout << "8. 로그아웃" << std::endl;
        std::cout << "선택: ";
        std::cin >> choice;

        if (std::cin.fail()) { // 문자가 들어올경우 실행(정수형입력에 실패한 경우)
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // 메뉴에서 문자 입력 무시
            continue;
        }

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
            printAllUsers();
            break;
        case 7:
            addadmin();
            break;
        case 8:
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

    // 사용자 목록 로드
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

    // 사용자 정보를 파일에 저장
    saveUsers(users);

    std::cout << "코인이 추가되었습니다." << std::endl;
}


void addVideo() { // 비디오 추가 기능
    std::string videoName, directorName;
    clearScreen();

    std::cout << "비디오 이름: ";
    std::cin.ignore();
    std::getline(std::cin, videoName);

    std::cout << "감독 이름: ";
    std::cin.ignore();
    std::getline(std::cin, directorName);

    // 비디오 목록 로드
    std::vector<std::tuple<std::string, std::string, std::string>> videos = loadVideos();

    // 현재 비디오의 개수를 확인하여 순서를 결정
    size_t videoCount = videos.size();

    // 새로운 비디오 추가
    videos.push_back(std::make_tuple(std::to_string(videoCount + 1), videoName, directorName));

    // 비디오 정보를 파일에 저장
    saveVideos(videos);

    std::cout << "비디오 추가가 완료되었습니다." << std::endl;
}


void delVideo() {
    std::string videoName;
    clearScreen();

    std::cout << "비디오 삭제를 진행합니다." << std::endl;
    std::cout << "비디오 이름: ";
    std::cin.ignore();
    std::getline(std::cin, videoName);

    // 비디오 목록 로드
    std::vector<std::tuple<std::string, std::string, std::string>> videos = loadVideos();

    std::vector<int> indices;
    for (size_t i = 0; i < videos.size(); ++i) {
        if (std::get<1>(videos[i]).find(videoName) != std::string::npos) {
            indices.push_back(static_cast<int>(i));
        }
    }

    if (indices.empty()) {
        std::cout << "해당 이름의 비디오를 찾을 수 없습니다." << std::endl;
        return;
    }

    std::cout << "삭제할 비디오를 선택하십시오" << std::endl;
    std::cout << "------------------------------------" << std::endl;
    for (size_t i = 0; i < indices.size(); ++i) {
        std::cout << i + 1 << ". " << std::get<1>(videos[indices[i]]) << std::endl;
    }

    int choice;
    std::cout << "선택: ";
    std::cin >> choice;

    if (choice < 1 || choice > static_cast<int>(indices.size())) {
        std::cout << "잘못된 선택입니다." << std::endl;
        return;
    }

    // 선택한 비디오 삭제
    videos.erase(videos.begin() + indices[choice - 1]);

    // 비디오 정보를 파일에 저장
    saveVideos(videos);

    std::cout << "비디오가 삭제되었습니다." << std::endl;
}


void addadmin() {
    std::string userId;
    clearScreen();

    std::cout << "관리자 추가를 진행합니다." << std::endl;
    std::cout << "추가할 관리자 ID: ";
    std::cin >> userId;

    // 사용자 목록 로드
    std::vector<User> users = loadUsers();

    auto it = std::find_if(users.begin(), users.end(), [&userId](const User& user) {
        return user.userId == userId;
        });

    if (it == users.end()) {
        std::cout << "사용자를 찾을 수 없습니다." << std::endl;
        return;
    }

    it->isAdmin = true;

    // 사용자 정보를 파일에 저장
    saveUsers(users);

    std::cout << "관리자가 추가되었습니다." << std::endl;
}


void printAllUsers() {
    clearScreen();

    // 사용자 목록 로드
    std::vector<User> users = loadUsers();

    std::cout << "===== 모든 사용자 목록 =====" << std::endl;
    for (const auto& user : users) {
        std::cout << "ID: " << user.userId << std::endl;
        std::cout << "이름: " << user.name << std::endl;
        std::cout << "생년월일: " << user.birthDate << std::endl;
        std::cout << "전화번호: " << user.phoneNumber << std::endl;
        std::cout << "관리자 여부: " << (user.isAdmin ? "예" : "아니오") << std::endl;
        std::cout << "코인: " << user.coins << std::endl;

        std::cout << "--------------------------" << std::endl;
    }
}
