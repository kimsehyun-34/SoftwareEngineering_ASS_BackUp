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

#endif