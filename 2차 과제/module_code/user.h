#ifndef USER_H
#define USER_H

#include <string>
#include <vector>
#include <tuple>
#include <ctime>
#include <limits>

struct User {
    std::string userId;
    std::string password;
    std::string name;
    std::string birthDate;
    std::string phoneNumber;
    bool isAdmin = false;
    int coins = 0;
    std::vector<std::tuple<std::string, std::time_t>> rentedVideos;
};

extern User* currentUser;

void signUp();
void login();
void userMenu();
bool isUserIdUnique(const std::string& userId, const std::vector<User>& users);
bool isPhoneNumberUnique(const std::string& phoneNumber, const std::vector<User>& users);
User* authenticateUser(const std::string& userId, const std::string& password, std::vector<User>& users);
bool hasOverdueVideos(const User& user, const std::vector<std::tuple<std::string, std::string, std::time_t>>& rentals);
void allVideo(); 

#endif
