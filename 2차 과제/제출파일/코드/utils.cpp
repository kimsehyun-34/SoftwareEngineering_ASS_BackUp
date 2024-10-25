#include "utils.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <windows.h>
#include <cstdlib>

void clearScreen() {
    system("cls");
}

std::vector<User> loadUsers() {
    std::vector<User> users;
    std::ifstream infile("users.txt");
    std::string line;
    while (std::getline(infile, line)) {
        std::istringstream ss(line);
        User user;
        std::string dateStr;

        std::getline(ss, user.userId, ',');
        std::getline(ss, user.password, ',');
        std::getline(ss, user.name, ',');
        std::getline(ss, user.birthDate, ',');
        std::getline(ss, user.phoneNumber, ',');

        std::string isAdminStr;
        std::getline(ss, isAdminStr, ',');
        user.isAdmin = (isAdminStr == "1");
        std::string coinsStr;
        std::getline(ss, coinsStr, ',');
        user.coins = std::stoi(coinsStr);

        // rentedVideos 초기화
        std::vector<std::tuple<std::string, std::time_t>> rentedVideos;
        while (std::getline(ss, line, ',')) {
            std::string videoId = line;
            std::getline(ss, dateStr, ',');

            std::tm tm = {};
            std::istringstream dateStream(dateStr);
            dateStream >> std::get_time(&tm, "%Y-%m-%d");
            std::time_t rentalDate = std::mktime(&tm);

            rentedVideos.push_back(std::make_tuple(videoId, rentalDate));
        }
        user.rentedVideos = rentedVideos;

        users.push_back(user);
    }
    return users;
}


std::vector<std::tuple<std::string, std::string, std::time_t>> loadRentals() {
    std::vector<std::tuple<std::string, std::string, std::time_t>> rentals;
    std::ifstream infile("rentals.txt");
    std::string line;
    while (std::getline(infile, line)) {
        std::istringstream ss(line);
        std::string userId, videoId, dateStr;
        std::getline(ss, userId, ',');
        std::getline(ss, videoId, ',');
        std::getline(ss, dateStr, ',');

        std::tm tm = {};
        std::istringstream dateStream(dateStr);
        dateStream >> std::get_time(&tm, "%Y-%m-%d");
        std::time_t rentalDate = std::mktime(&tm);

        rentals.push_back(std::make_tuple(userId, videoId, rentalDate));
    }
    return rentals;
}

void saveUsers(const std::vector<User>& users) {
    std::ofstream userFile("users.txt");
    for (const auto& user : users) {
        userFile << user.userId << "," << user.password << "," << user.name << "," << user.birthDate << "," << user.phoneNumber << "," << user.isAdmin << "," << user.coins << std::endl;
    }
    userFile.close();
}

void saveRentals(const std::vector<std::tuple<std::string, std::string, std::time_t>>& rentals) {
    std::ofstream rentalFile("rentals.txt");
    for (const auto& rental : rentals) {
        std::tm tm;
        localtime_s(&tm, &std::get<2>(rental));
        char dateStr[20];
        std::strftime(dateStr, sizeof(dateStr), "%Y-%m-%d", &tm);

        rentalFile << std::get<0>(rental) << "," << std::get<1>(rental) << "," << dateStr << std::endl;
    }
    rentalFile.close();
}

void saveVideos(const std::vector<std::tuple<std::string, std::string, std::string>>& videos) {
    std::ofstream outfile("videos.txt");
    for (const auto& video : videos) {
        outfile << std::get<0>(video) << "," << std::get<1>(video) << "," << std::get<2>(video) << std::endl;
    }
    outfile.close();
}


std::vector<std::tuple<std::string, std::string, std::string>> loadVideos() {
    std::vector<std::tuple<std::string, std::string, std::string>> videos;
    std::ifstream infile("videos.txt");
    std::string line;
    while (std::getline(infile, line)) {
        std::istringstream ss(line);
        std::string videoId, videoName, directorName;
        std::getline(ss, videoId, ',');
        std::getline(ss, videoName, ',');
        std::getline(ss, directorName, ',');

        videos.push_back(std::make_tuple(videoId, videoName, directorName));
    }
    return videos;
}

