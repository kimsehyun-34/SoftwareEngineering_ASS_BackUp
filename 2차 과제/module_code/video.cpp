#include "video.h"
#include "utils.h"
#include "user.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <ctime>

void allVideo() {
    clearScreen();

    std::ifstream videoFile("videos.txt");
    std::ifstream rentalFile("rentals.txt");
    std::string line;
    std::vector<std::string> videoList;
    std::vector<std::string> rentedVideos;

    while (std::getline(rentalFile, line)) {
        size_t pos1 = line.find(',');
        size_t pos2 = line.find(',', pos1 + 1);
        std::string videoId = line.substr(pos1 + 1, pos2 - pos1 - 1);
        rentedVideos.push_back(videoId);
    }

    while (std::getline(videoFile, line)) {
        videoList.push_back(line);
    }

    std::sort(videoList.begin(), videoList.end());

    std::cout << "전체 비디오 목록:" << std::endl;
    for (const auto& video : videoList) {
        std::cout << video << std::endl;
    }

    videoFile.close();
    rentalFile.close();
}

void checkVideoRentalStatus() {
    clearScreen();

    std::ifstream rentalFile("rentals.txt");
    std::string line;
    std::vector<std::tuple<std::string, std::string, std::string>> rentalList;

    while (std::getline(rentalFile, line)) {
        size_t pos1 = line.find(',');
        size_t pos2 = line.find(',', pos1 + 1);
        std::string rentalUserId = line.substr(0, pos1);
        std::string videoId = line.substr(pos1 + 1, pos2 - pos1 - 1);
        std::string rentalDate = line.substr(pos2 + 1);

        rentalList.push_back(std::make_tuple(rentalUserId, videoId, rentalDate));
    }
    rentalFile.close();

    if (rentalList.empty()) {
        std::cout << "현재 대여 중인 비디오가 없습니다." << std::endl;
        return;
    }

    std::cout << "현재 대여 중인 비디오 목록:" << std::endl;
    for (const auto& rental : rentalList) {
        std::cout << "사용자 ID: " << std::get<0>(rental) << ", 비디오 ID: " << std::get<1>(rental) << ", 대여 날짜: " << std::get<2>(rental) << std::endl;
    }

    std::cout << "메뉴로 돌아가려면 아무 키나 누르십시오...";
    std::cin.ignore();
    std::cin.get();
}

void returnVideo() {
    std::string userId;
    clearScreen();

    std::vector<User> users = loadUsers();

    std::cout << "비디오를 반납할 사용자 ID: ";
    std::cin >> userId;

    auto it = std::find_if(users.begin(), users.end(), [&userId](const User& user) {
        return user.userId == userId;
        });

    if (it == users.end()) {
        std::cout << "사용자를 찾을 수 없습니다." << std::endl;
        return;
    }

    std::ifstream rentalFile("rentals.txt");
    std::string line;
    std::vector<std::tuple<std::string, std::string, std::string>> rentalList;

    while (std::getline(rentalFile, line)) {
        size_t pos1 = line.find(',');
        size_t pos2 = line.find(',', pos1 + 1);
        std::string rentalUserId = line.substr(0, pos1);
        std::string videoId = line.substr(pos1 + 1, pos2 - pos1 - 1);
        std::string rentalDate = line.substr(pos2 + 1);

        if (rentalUserId == userId) {
            rentalList.push_back(std::make_tuple(rentalUserId, videoId, rentalDate));
        }
    }
    rentalFile.close();

    if (rentalList.empty()) {
        std::cout << "현재 대여 중인 비디오가 없습니다." << std::endl;
        return;
    }

    std::cout << "반납할 비디오를 선택하십시오" << std::endl;
    std::cout << "------------------------------------" << std::endl;
    for (size_t i = 0; i < rentalList.size(); ++i) {
        std::cout << i + 1 << ". 비디오 ID: " << std::get<1>(rentalList[i]) << ", 대여 날짜: " << std::get<2>(rentalList[i]) << std::endl;
    }

    int choice;
    std::cout << "선택: ";
    std::cin >> choice;

    if (choice < 1 || choice > rentalList.size()) {
        std::cout << "잘못된 선택입니다. 작업이 취소되었습니다." << std::endl;
        return;
    }

    std::string videoIdToReturn = std::get<1>(rentalList[choice - 1]);
    rentalList.erase(rentalList.begin() + choice - 1);

    std::ofstream outfile("rentals.txt");
    for (const auto& rental : rentalList) {
        outfile << std::get<0>(rental) << "," << std::get<1>(rental) << "," << std::get<2>(rental) << std::endl;
    }
    outfile.close();

    std::cout << "비디오가 반납되었습니다." << std::endl;
}

#include <ctime>

void rentVideo() {
    if (currentUser == nullptr) {
        std::cout << "로그인이 필요합니다." << std::endl;
        return;
    }

    if (hasOverdueVideos(*currentUser)) {
        std::cout << "연체된 비디오가 있습니다. 반납 후 다시 시도하십시오." << std::endl;
        return;
    }

    const int rentalCost = 1;
    if (currentUser->coins < rentalCost) {
        std::cout << "코인이 부족합니다." << std::endl;
        return;
    }

    std::ifstream infile("videos.txt");
    std::string line;
    std::vector<std::string> videoList;

    while (std::getline(infile, line)) {
        videoList.push_back(line);
    }
    infile.close();

    if (videoList.empty()) {
        std::cout << "대여 가능한 비디오가 없습니다." << std::endl;
        return;
    }

    std::cout << "대여할 비디오를 선택하십시오" << std::endl;
    std::cout << "------------------------------------" << std::endl;
    for (size_t i = 0; i < videoList.size(); ++i) {
        std::cout << i + 1 << ". " << videoList[i] << std::endl;
    }

    int choice;
    std::cout << "선택: ";
    std::cin >> choice;

    if (choice < 1 || choice > videoList.size()) {
        std::cout << "잘못된 선택입니다. 작업이 취소되었습니다." << std::endl;
        return;
    }

    std::string selectedVideoId = videoList[choice - 1];

    std::ifstream rentalFile("rentals.txt");
    std::vector<std::string> rentedVideoIds;
    while (std::getline(rentalFile, line)) {
        size_t pos1 = line.find(',');
        size_t pos2 = line.find(',', pos1 + 1);
        std::string videoId = line.substr(pos1 + 1, pos2 - pos1 - 1);
        rentedVideoIds.push_back(videoId);
    }
    rentalFile.close();

    if (std::count(rentedVideoIds.begin(), rentedVideoIds.end(), selectedVideoId) > 0) {
        std::cout << "이미 대여 중인 비디오입니다." << std::endl;
        return;
    }

    std::ofstream outfile("rentals.txt", std::ios_base::app);
    std::time_t now = std::time(nullptr);
    std::tm now_tm;
    localtime_s(&now_tm, &now);
    char dateStr[20];
    std::strftime(dateStr, sizeof(dateStr), "%Y-%m-%d", &now_tm);

    outfile << currentUser->userId << "," << selectedVideoId << "," << dateStr << std::endl;
    outfile.close();

    currentUser->coins -= rentalCost;

    std::ofstream userFile("users.txt");
    for (const auto& user : loadUsers()) {
        userFile << user.userId << "," << user.password << "," << user.name << "," << user.birthDate << "," << user.phoneNumber << "," << user.isAdmin << "," << user.coins << std::endl;
    }

    std::cout << "비디오가 대여되었습니다." << std::endl;
}


void checkRemainingDays() {
    if (currentUser == nullptr) {
        std::cout << "로그인이 필요합니다." << std::endl;
        return;
    }

    std::ifstream rentalFile("rentals.txt");
    std::string line;
    std::vector<std::tuple<std::string, std::string, std::string>> rentalList;

    while (std::getline(rentalFile, line)) {
        size_t pos1 = line.find(',');
        size_t pos2 = line.find(',', pos1 + 1);
        std::string rentalUserId = line.substr(0, pos1);
        std::string videoId = line.substr(pos1 + 1, pos2 - pos1 - 1);
        std::string rentalDate = line.substr(pos2 + 1);

        if (rentalUserId == currentUser->userId) {
            rentalList.push_back(std::make_tuple(rentalUserId, videoId, rentalDate));
        }
    }
    rentalFile.close();

    if (rentalList.empty()) {
        std::cout << "현재 대여 중인 비디오가 없습니다." << std::endl;
        return;
    }

    std::cout << "대여 중인 비디오 목록:" << std::endl;
    for (const auto& rental : rentalList) {
        std::cout << "비디오 ID: " << std::get<1>(rental) << ", 대여 날짜: " << std::get<2>(rental) << std::endl;
    }

    std::cout << "메뉴로 돌아가려면 아무 키나 누르십시오...";
    std::cin.ignore();
    std::cin.get();
}