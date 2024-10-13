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
        User user;
        size_t pos = 0;
        pos = line.find(',');
        user.userId = line.substr(0, pos);
        line.erase(0, pos + 1);

        pos = line.find(',');
        user.password = line.substr(0, pos);
        line.erase(0, pos + 1);

        pos = line.find(',');
        user.name = line.substr(0, pos);
        line.erase(0, pos + 1);

        pos = line.find(',');
        user.birthDate = line.substr(0, pos);
        line.erase(0, pos + 1);

        pos = line.find(',');
        user.phoneNumber = line.substr(0, pos);
        line.erase(0, pos + 1);

        pos = line.find(',');
        user.isAdmin = (line.substr(0, pos) == "1");
        line.erase(0, pos + 1);

        pos = line.find(',');
        user.coins = std::stoi(line.substr(0, pos));
        line.erase(0, pos + 1);

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