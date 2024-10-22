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

    // 비디오 목록 로드
    std::vector<std::string> videoList;
    for (const auto& video : videos) {
        videoList.push_back(std::get<0>(video) + ", " + std::get<1>(video) + ", " + std::get<2>(video));
    }

    // 대여 정보 로드
    std::vector<std::string> rentedVideos;
    for (const auto& rental : rentals) {
        rentedVideos.push_back(std::get<1>(rental)); // videoId
    }

    // 비디오 목록 정렬
    std::sort(videoList.begin(), videoList.end());

    std::cout << "전체 비디오 목록:" << std::endl;
    for (const auto& video : videoList) {
        std::string videoId = video.substr(0, video.find(','));
        bool isRented = std::find(rentedVideos.begin(), rentedVideos.end(), videoId) != rentedVideos.end();
        std::cout << video << (isRented ? " (대여 중)" : "") << std::endl;
    }
}



void checkVideoRentalStatus() {
    clearScreen();

    if (rentals.empty()) {
        std::cout << "현재 대여 중인 비디오가 없습니다." << std::endl;
        return;
    }

    std::cout << "현재 대여 중인 비디오 목록 및 남은 일수:" << std::endl;
    for (const auto& rental : rentals) {
        std::string rentalUserId = std::get<0>(rental);
        std::string videoId = std::get<1>(rental);
        std::time_t rentalDate = std::get<2>(rental);

        // 비디오 이름 가져오기
        auto videoIt = std::find_if(videos.begin(), videos.end(), [&videoId](const std::tuple<std::string, std::string, std::string>& video) {
            return std::get<0>(video) == videoId;
            });

        std::string videoName = (videoIt != videos.end()) ? std::get<1>(*videoIt) : "알 수 없음";
        std::string directorName = (videoIt != videos.end()) ? std::get<2>(*videoIt) : "알 수 없음";

        // 대여 날짜를 문자열로 변환
        std::tm tm;
        localtime_s(&tm, &rentalDate);
        char dateStr[20];
        std::strftime(dateStr, sizeof(dateStr), "%Y-%m-%d", &tm);

        // 남은 일수 계산
        auto now = std::chrono::system_clock::now();
        std::time_t now_c = std::chrono::system_clock::to_time_t(now);
        double remainingDays = std::difftime(rentalDate + 7 * 24 * 60 * 60, now_c) / (60 * 60 * 24);

        // 소수점 올림 처리하여 정수로 변환
        int remainingDaysInt = static_cast<int>(std::ceil(remainingDays));

        std::cout << "유저 ID: " << rentalUserId << ", 비디오 ID: " << videoId << ", 이름: " << videoName << ", 감독: " << directorName << ", 대여 날짜: " << dateStr << ", 남은 일수: " << remainingDaysInt << "일" << std::endl;
    }
}



void returnVideo() {
    std::string userId;
    clearScreen();

    std::cout << "비디오를 반납할 유저 ID: ";
    std::cin >> userId;

    auto it = std::find_if(users.begin(), users.end(), [&userId](const User& user) {
        return user.userId == userId;
        });

    if (it == users.end()) {
        std::cout << "유저를 찾을 수 없습니다." << std::endl;
        return;
    }

    // 대여 정보 로드
    std::vector<std::tuple<std::string, std::string, std::time_t>> userRentals;

    for (const auto& rental : rentals) {
        if (std::get<0>(rental) == userId) {
            userRentals.push_back(rental);
        }
    }

    if (userRentals.empty()) {
        std::cout << "해당 유저는 대여 중인 비디오가 없습니다." << std::endl;
        return;
    }

    std::cout << "현재 대여 중인 비디오 목록:" << std::endl;
    for (const auto& rental : userRentals) {
        std::string videoId = std::get<1>(rental);
        std::time_t rentalDate = std::get<2>(rental);

        // 비디오 이름 가져오기
        auto videoIt = std::find_if(videos.begin(), videos.end(), [&videoId](const std::tuple<std::string, std::string, std::string>& video) {
            return std::get<0>(video) == videoId;
            });

        std::string videoName = (videoIt != videos.end()) ? std::get<1>(*videoIt) : "알 수 없음";

        // 대여 날짜를 문자열로 변환
        std::tm tm;
        localtime_s(&tm, &rentalDate);
        char dateStr[20];
        std::strftime(dateStr, sizeof(dateStr), "%Y-%m-%d", &tm);

        std::cout << "비디오 ID: " << videoId << ", 이름: " << videoName << ", 대여 날짜: " << dateStr << std::endl;
    }

    std::cout << "반납할 비디오 ID: ";
    std::string videoId;
    std::cin >> videoId;

    auto rentalIt = std::find_if(userRentals.begin(), userRentals.end(), [&videoId](const std::tuple<std::string, std::string, std::time_t>& rental) {
        return std::get<1>(rental) == videoId;
        });

    if (rentalIt == userRentals.end()) {
        std::cout << "해당 비디오를 대여 중인 기록이 없습니다." << std::endl;
        return;
    }

    // 대여 목록에서 비디오 제거
    rentals.erase(std::remove(rentals.begin(), rentals.end(), *rentalIt), rentals.end());

    // 사용자 정보 업데이트
    it->rentedVideos.erase(std::remove_if(it->rentedVideos.begin(), it->rentedVideos.end(), [&videoId](const std::tuple<std::string, std::time_t>& rental) {
        return std::get<0>(rental) == videoId;
        }), it->rentedVideos.end());

    // 변경된 정보 저장
    saveUsers(users);
    saveRentals(rentals);

    std::cout << "비디오가 성공적으로 반납되었습니다." << std::endl;
}


void rentVideo() {
    if (currentUser == nullptr) {
        std::cout << "로그인이 필요합니다." << std::endl;
        return;
    }

    // 연체 여부 확인
    if (hasOverdueVideos(*currentUser, rentals)) {
        std::cout << "연체 중인 비디오가 있어 대여할 수 없습니다." << std::endl;
        return;
    }

    const int rentalCost = 1; // 비디오 대여 비용

    if (currentUser->coins < rentalCost) {
        std::cout << "코인이 부족합니다. 관리자에게 문의하세요." << std::endl;
        return;
    }

    std::string videoName;
    clearScreen();

    std::cout << "비디오 이름: ";
    std::cin.ignore(); // 이전 입력의 개행 문자를 무시
    std::getline(std::cin, videoName);

    // 비디오 목록을 로드
    std::vector<std::tuple<std::string, std::string, std::string>> videoList; // <ID, Name, Director>
    for (const auto& video : videos) {
        videoList.push_back(video);
    }

    // 대여 정보 로드
    std::vector<std::string> rentedVideoIds;
    for (const auto& rental : rentals) {
        rentedVideoIds.push_back(std::get<1>(rental));
    }

    std::cout << "대여 가능한 비디오 목록:" << std::endl;
    for (const auto& video : videoList) {
        std::string videoId = std::get<0>(video);
        std::string videoName = std::get<1>(video);
        std::string directorName = std::get<2>(video);

        bool isRented = std::find(rentedVideoIds.begin(), rentedVideoIds.end(), videoId) != rentedVideoIds.end();

        if (!isRented) {
            std::cout << "비디오 ID: " << videoId << ", 이름: " << videoName << ", 감독: " << directorName << std::endl;
        }
    }

    std::string videoId;
    std::cout << "대여할 비디오 ID를 입력하세요: ";
    std::cin >> videoId;

    // 비디오가 이미 대여 중인지 확인
    auto rentalIt = std::find_if(rentals.begin(), rentals.end(), [&videoId](const std::tuple<std::string, std::string, std::time_t>& rental) {
        return std::get<1>(rental) == videoId;
        });

    if (rentalIt != rentals.end()) {
        std::cout << "비디오는 이미 대여 중입니다." << std::endl;
        return;
    }

    // 대여 날짜 설정
    std::time_t now = std::time(nullptr);

    // 대여 정보 추가
    rentals.push_back(std::make_tuple(currentUser->userId, videoId, now));

    // 유저의 대여 목록에 추가
    currentUser->rentedVideos.push_back(std::make_tuple(videoId, now));
    currentUser->coins -= rentalCost;

    // 유저 정보와 대여 정보 저장
    auto userIt = std::find_if(users.begin(), users.end(), [](const User& user) {
        return user.userId == currentUser->userId;
        });

    if (userIt != users.end()) {
        *userIt = *currentUser;
    }

    saveUsers(users);
    saveRentals(rentals);

    std::cout << "비디오가 성공적으로 대여되었습니다." << std::endl;
}



void checkRemainingDays() {
    clearScreen();

    if (currentUser == nullptr) {
        std::cout << "로그인이 필요합니다." << std::endl;
        return;
    }

    if (rentals.empty()) {
        std::cout << "현재 대여 중인 비디오가 없습니다." << std::endl;
        return;
    }

    std::cout << "현재 대여 중인 비디오 목록 및 남은 일수:" << std::endl;
    for (const auto& rental : rentals) {
        std::string rentalUserId = std::get<0>(rental);
        if (rentalUserId != currentUser->userId) {
            continue; // 로그인한 사용자의 대여 정보만 출력
        }
        std::string videoId = std::get<1>(rental);
        std::time_t rentalDate = std::get<2>(rental);

        // 비디오 이름 가져오기
        auto videoIt = std::find_if(videos.begin(), videos.end(), [&videoId](const std::tuple<std::string, std::string, std::string>& video) {
            return std::get<0>(video) == videoId;
            });

        std::string videoName = (videoIt != videos.end()) ? std::get<1>(*videoIt) : "알 수 없음";

        // 대여 날짜를 문자열로 변환
        std::tm tm;
        localtime_s(&tm, &rentalDate);
        char dateStr[20];
        std::strftime(dateStr, sizeof(dateStr), "%Y-%m-%d", &tm);

        // 남은 일수 계산
        auto now = std::chrono::system_clock::now();
        std::time_t now_c = std::chrono::system_clock::to_time_t(now);
        double remainingDays = std::difftime(rentalDate + 7 * 24 * 60 * 60, now_c) / (60 * 60 * 24);

        // 소수점 올림 처리하여 정수로 변환
        int remainingDaysInt = static_cast<int>(std::ceil(remainingDays));

        std::cout << "비디오 ID: " << videoId << ", 이름: " << videoName << ", 대여 날짜: " << dateStr << ", 남은 일수: " << remainingDaysInt << "일" << std::endl;
    }
}
