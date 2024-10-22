#include "video.h"
#include "utils.h"
#include "user.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <ctime>
#include <chrono>

std::vector<User> users = loadUsers();
std::vector<std::tuple<std::string, std::string, std::string>> videos = loadVideos();
std::vector<std::tuple<std::string, std::string, std::time_t>> rentals = loadRentals();

void allVideo() {
    clearScreen();

    // ���� ��� �ε�
    std::vector<std::string> videoList;
    for (const auto& video : videos) {
        videoList.push_back(std::get<0>(video) + ", " + std::get<1>(video) + ", " + std::get<2>(video));
    }

    // �뿩 ���� �ε�
    std::vector<std::string> rentedVideos;
    for (const auto& rental : rentals) {
        rentedVideos.push_back(std::get<1>(rental)); // videoId
    }

    // ���� ��� ����
    std::sort(videoList.begin(), videoList.end());

    std::cout << "��ü ���� ���:" << std::endl;
    for (const auto& video : videoList) {
        std::string videoId = video.substr(0, video.find(','));
        bool isRented = std::find(rentedVideos.begin(), rentedVideos.end(), videoId) != rentedVideos.end();
        std::cout << video << (isRented ? " (�뿩 ��)" : "") << std::endl;
    }
}



void checkVideoRentalStatus() {
    clearScreen();

    if (rentals.empty()) {
        std::cout << "���� �뿩 ���� ������ �����ϴ�." << std::endl;
        return;
    }

    std::cout << "���� �뿩 ���� ���� ��� �� ���� �ϼ�:" << std::endl;
    for (const auto& rental : rentals) {
        std::string rentalUserId = std::get<0>(rental);
        std::string videoId = std::get<1>(rental);
        std::time_t rentalDate = std::get<2>(rental);

        // ���� �̸� ��������
        auto videoIt = std::find_if(videos.begin(), videos.end(), [&videoId](const std::tuple<std::string, std::string, std::string>& video) {
            return std::get<0>(video) == videoId;
            });

        std::string videoName = (videoIt != videos.end()) ? std::get<1>(*videoIt) : "�� �� ����";
        std::string directorName = (videoIt != videos.end()) ? std::get<2>(*videoIt) : "�� �� ����";

        // �뿩 ��¥�� ���ڿ��� ��ȯ
        std::tm tm;
        localtime_s(&tm, &rentalDate);
        char dateStr[20];
        std::strftime(dateStr, sizeof(dateStr), "%Y-%m-%d", &tm);

        // ���� �ϼ� ���
        auto now = std::chrono::system_clock::now();
        std::time_t now_c = std::chrono::system_clock::to_time_t(now);
        double remainingDays = std::difftime(rentalDate + 7 * 24 * 60 * 60, now_c) / (60 * 60 * 24);

        // �Ҽ��� �ø� ó���Ͽ� ������ ��ȯ
        int remainingDaysInt = static_cast<int>(std::ceil(remainingDays));

        std::cout << "���� ID: " << rentalUserId << ", ���� ID: " << videoId << ", �̸�: " << videoName << ", ����: " << directorName << ", �뿩 ��¥: " << dateStr << ", ���� �ϼ�: " << remainingDaysInt << "��" << std::endl;
    }
}



void returnVideo() {
    std::string userId;
    clearScreen();

    std::cout << "������ �ݳ��� ���� ID: ";
    std::cin >> userId;

    auto it = std::find_if(users.begin(), users.end(), [&userId](const User& user) {
        return user.userId == userId;
        });

    if (it == users.end()) {
        std::cout << "������ ã�� �� �����ϴ�." << std::endl;
        return;
    }

    // �뿩 ���� �ε�
    std::vector<std::tuple<std::string, std::string, std::time_t>> userRentals;

    for (const auto& rental : rentals) {
        if (std::get<0>(rental) == userId) {
            userRentals.push_back(rental);
        }
    }

    if (userRentals.empty()) {
        std::cout << "�ش� ������ �뿩 ���� ������ �����ϴ�." << std::endl;
        return;
    }

    std::cout << "���� �뿩 ���� ���� ���:" << std::endl;
    for (const auto& rental : userRentals) {
        std::string videoId = std::get<1>(rental);
        std::time_t rentalDate = std::get<2>(rental);

        // ���� �̸� ��������
        auto videoIt = std::find_if(videos.begin(), videos.end(), [&videoId](const std::tuple<std::string, std::string, std::string>& video) {
            return std::get<0>(video) == videoId;
            });

        std::string videoName = (videoIt != videos.end()) ? std::get<1>(*videoIt) : "�� �� ����";

        // �뿩 ��¥�� ���ڿ��� ��ȯ
        std::tm tm;
        localtime_s(&tm, &rentalDate);
        char dateStr[20];
        std::strftime(dateStr, sizeof(dateStr), "%Y-%m-%d", &tm);

        std::cout << "���� ID: " << videoId << ", �̸�: " << videoName << ", �뿩 ��¥: " << dateStr << std::endl;
    }

    std::cout << "�ݳ��� ���� ID: ";
    std::string videoId;
    std::cin >> videoId;

    auto rentalIt = std::find_if(userRentals.begin(), userRentals.end(), [&videoId](const std::tuple<std::string, std::string, std::time_t>& rental) {
        return std::get<1>(rental) == videoId;
        });

    if (rentalIt == userRentals.end()) {
        std::cout << "�ش� ������ �뿩 ���� ����� �����ϴ�." << std::endl;
        return;
    }

    // �뿩 ��Ͽ��� ���� ����
    rentals.erase(std::remove(rentals.begin(), rentals.end(), *rentalIt), rentals.end());

    // ����� ���� ������Ʈ
    it->rentedVideos.erase(std::remove_if(it->rentedVideos.begin(), it->rentedVideos.end(), [&videoId](const std::tuple<std::string, std::time_t>& rental) {
        return std::get<0>(rental) == videoId;
        }), it->rentedVideos.end());

    // ����� ���� ����
    saveUsers(users);
    saveRentals(rentals);

    std::cout << "������ ���������� �ݳ��Ǿ����ϴ�." << std::endl;
}


void rentVideo() {
    if (currentUser == nullptr) {
        std::cout << "�α����� �ʿ��մϴ�." << std::endl;
        return;
    }

    // ��ü ���� Ȯ��
    if (hasOverdueVideos(*currentUser, rentals)) {
        std::cout << "��ü ���� ������ �־� �뿩�� �� �����ϴ�." << std::endl;
        return;
    }

    const int rentalCost = 1; // ���� �뿩 ���

    if (currentUser->coins < rentalCost) {
        std::cout << "������ �����մϴ�. �����ڿ��� �����ϼ���." << std::endl;
        return;
    }

    std::string videoName;
    clearScreen();

    std::cout << "���� �̸�: ";
    std::cin.ignore(); // ���� �Է��� ���� ���ڸ� ����
    std::getline(std::cin, videoName);

    // ���� ����� �ε�
    std::vector<std::tuple<std::string, std::string, std::string>> videoList; // <ID, Name, Director>
    for (const auto& video : videos) {
        videoList.push_back(video);
    }

    // �뿩 ���� �ε�
    std::vector<std::string> rentedVideoIds;
    for (const auto& rental : rentals) {
        rentedVideoIds.push_back(std::get<1>(rental));
    }

    std::cout << "�뿩 ������ ���� ���:" << std::endl;
    for (const auto& video : videoList) {
        std::string videoId = std::get<0>(video);
        std::string videoName = std::get<1>(video);
        std::string directorName = std::get<2>(video);

        bool isRented = std::find(rentedVideoIds.begin(), rentedVideoIds.end(), videoId) != rentedVideoIds.end();

        if (!isRented) {
            std::cout << "���� ID: " << videoId << ", �̸�: " << videoName << ", ����: " << directorName << std::endl;
        }
    }

    std::string videoId;
    std::cout << "�뿩�� ���� ID�� �Է��ϼ���: ";
    std::cin >> videoId;

    // ������ �̹� �뿩 ������ Ȯ��
    auto rentalIt = std::find_if(rentals.begin(), rentals.end(), [&videoId](const std::tuple<std::string, std::string, std::time_t>& rental) {
        return std::get<1>(rental) == videoId;
        });

    if (rentalIt != rentals.end()) {
        std::cout << "������ �̹� �뿩 ���Դϴ�." << std::endl;
        return;
    }

    // �뿩 ��¥ ����
    std::time_t now = std::time(nullptr);

    // �뿩 ���� �߰�
    rentals.push_back(std::make_tuple(currentUser->userId, videoId, now));

    // ������ �뿩 ��Ͽ� �߰�
    currentUser->rentedVideos.push_back(std::make_tuple(videoId, now));
    currentUser->coins -= rentalCost;

    // ���� ������ �뿩 ���� ����
    auto userIt = std::find_if(users.begin(), users.end(), [](const User& user) {
        return user.userId == currentUser->userId;
        });

    if (userIt != users.end()) {
        *userIt = *currentUser;
    }

    saveUsers(users);
    saveRentals(rentals);

    std::cout << "������ ���������� �뿩�Ǿ����ϴ�." << std::endl;
}



void checkRemainingDays() {
    clearScreen();

    if (currentUser == nullptr) {
        std::cout << "�α����� �ʿ��մϴ�." << std::endl;
        return;
    }

    if (rentals.empty()) {
        std::cout << "���� �뿩 ���� ������ �����ϴ�." << std::endl;
        return;
    }

    std::cout << "���� �뿩 ���� ���� ��� �� ���� �ϼ�:" << std::endl;
    for (const auto& rental : rentals) {
        std::string rentalUserId = std::get<0>(rental);
        if (rentalUserId != currentUser->userId) {
            continue; // �α����� ������� �뿩 ������ ���
        }
        std::string videoId = std::get<1>(rental);
        std::time_t rentalDate = std::get<2>(rental);

        // ���� �̸� ��������
        auto videoIt = std::find_if(videos.begin(), videos.end(), [&videoId](const std::tuple<std::string, std::string, std::string>& video) {
            return std::get<0>(video) == videoId;
            });

        std::string videoName = (videoIt != videos.end()) ? std::get<1>(*videoIt) : "�� �� ����";

        // �뿩 ��¥�� ���ڿ��� ��ȯ
        std::tm tm;
        localtime_s(&tm, &rentalDate);
        char dateStr[20];
        std::strftime(dateStr, sizeof(dateStr), "%Y-%m-%d", &tm);

        // ���� �ϼ� ���
        auto now = std::chrono::system_clock::now();
        std::time_t now_c = std::chrono::system_clock::to_time_t(now);
        double remainingDays = std::difftime(rentalDate + 7 * 24 * 60 * 60, now_c) / (60 * 60 * 24);

        // �Ҽ��� �ø� ó���Ͽ� ������ ��ȯ
        int remainingDaysInt = static_cast<int>(std::ceil(remainingDays));

        std::cout << "���� ID: " << videoId << ", �̸�: " << videoName << ", �뿩 ��¥: " << dateStr << ", ���� �ϼ�: " << remainingDaysInt << "��" << std::endl;
    }
}
