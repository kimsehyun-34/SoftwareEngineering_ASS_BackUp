#ifndef UTILS_H
#define UTILS_H

#include <vector>
#include <string>
#include <tuple>
#include <ctime>
#include "user.h"

void clearScreen();
std::vector<User> loadUsers();
std::vector<std::tuple<std::string, std::string, std::time_t>> loadRentals();
std::vector<std::tuple<std::string, std::string, std::string>> loadVideos();

void saveUsers(const std::vector<User>& users);
void saveRentals(const std::vector<std::tuple<std::string, std::string, std::time_t>>& rentals);
void saveVideos(const std::vector<std::tuple<std::string, std::string, std::string>>& videos);

#endif
