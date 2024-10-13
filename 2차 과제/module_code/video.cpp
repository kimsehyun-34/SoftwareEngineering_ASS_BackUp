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

    std::cout << "��ü ���� ���:" << std::endl;
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
        std::cout << "���� �뿩 ���� ������ �����ϴ�." << std::endl;
        return;
    }

    std::cout << "���� �뿩 ���� ���� ���:" << std::endl;
    for (const auto& rental : rentalList) {
        std::cout << "����� ID: " << std::get<0>(rental) << ", ���� ID: " << std::get<1>(rental) << ", �뿩 ��¥: " << std::get<2>(rental) << std::endl;
    }

    std::cout << "�޴��� ���ư����� �ƹ� Ű�� �����ʽÿ�...";
    std::cin.ignore();
    std::cin.get();
}

void returnVideo() {
    std::string userId;
    clearScreen();

    std::vector<User> users = loadUsers();

    std::cout << "������ �ݳ��� ����� ID: ";
    std::cin >> userId;

    auto it = std::find_if(users.begin(), users.end(), [&userId](const User& user) {
        return user.userId == userId;
        });

    if (it == users.end()) {
        std::cout << "����ڸ� ã�� �� �����ϴ�." << std::endl;
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
        std::cout << "���� �뿩 ���� ������ �����ϴ�." << std::endl;
        return;
    }

    std::cout << "�ݳ��� ������ �����Ͻʽÿ�" << std::endl;
    std::cout << "------------------------------------" << std::endl;
    for (size_t i = 0; i < rentalList.size(); ++i) {
        std::cout << i + 1 << ". ���� ID: " << std::get<1>(rentalList[i]) << ", �뿩 ��¥: " << std::get<2>(rentalList[i]) << std::endl;
    }

    int choice;
    std::cout << "����: ";
    std::cin >> choice;

    if (choice < 1 || choice > rentalList.size()) {
        std::cout << "�߸��� �����Դϴ�. �۾��� ��ҵǾ����ϴ�." << std::endl;
        return;
    }

    std::string videoIdToReturn = std::get<1>(rentalList[choice - 1]);
    rentalList.erase(rentalList.begin() + choice - 1);

    std::ofstream outfile("rentals.txt");
    for (const auto& rental : rentalList) {
        outfile << std::get<0>(rental) << "," << std::get<1>(rental) << "," << std::get<2>(rental) << std::endl;
    }
    outfile.close();

    std::cout << "������ �ݳ��Ǿ����ϴ�." << std::endl;
}

#include <ctime>

void rentVideo() {
    if (currentUser == nullptr) {
        std::cout << "�α����� �ʿ��մϴ�." << std::endl;
        return;
    }

    if (hasOverdueVideos(*currentUser)) {
        std::cout << "��ü�� ������ �ֽ��ϴ�. �ݳ� �� �ٽ� �õ��Ͻʽÿ�." << std::endl;
        return;
    }

    const int rentalCost = 1;
    if (currentUser->coins < rentalCost) {
        std::cout << "������ �����մϴ�." << std::endl;
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
        std::cout << "�뿩 ������ ������ �����ϴ�." << std::endl;
        return;
    }

    std::cout << "�뿩�� ������ �����Ͻʽÿ�" << std::endl;
    std::cout << "------------------------------------" << std::endl;
    for (size_t i = 0; i < videoList.size(); ++i) {
        std::cout << i + 1 << ". " << videoList[i] << std::endl;
    }

    int choice;
    std::cout << "����: ";
    std::cin >> choice;

    if (choice < 1 || choice > videoList.size()) {
        std::cout << "�߸��� �����Դϴ�. �۾��� ��ҵǾ����ϴ�." << std::endl;
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
        std::cout << "�̹� �뿩 ���� �����Դϴ�." << std::endl;
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

    std::cout << "������ �뿩�Ǿ����ϴ�." << std::endl;
}


void checkRemainingDays() {
    if (currentUser == nullptr) {
        std::cout << "�α����� �ʿ��մϴ�." << std::endl;
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
        std::cout << "���� �뿩 ���� ������ �����ϴ�." << std::endl;
        return;
    }

    std::cout << "�뿩 ���� ���� ���:" << std::endl;
    for (const auto& rental : rentalList) {
        std::cout << "���� ID: " << std::get<1>(rental) << ", �뿩 ��¥: " << std::get<2>(rental) << std::endl;
    }

    std::cout << "�޴��� ���ư����� �ƹ� Ű�� �����ʽÿ�...";
    std::cin.ignore();
    std::cin.get();
}