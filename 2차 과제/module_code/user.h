#ifndef USER_H
#define USER_H

#include <string>
#include <vector>
#include <tuple>
#include <ctime>

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

extern User* currentUser; // currentUser ���� ����

void signUp();
void login();
void userMenu();
bool isUserIdUnique(const std::string& userId, const std::vector<User>& users);
User* authenticateUser(const std::string& userId, const std::string& password, std::vector<User>& users);
bool hasOverdueVideos(const User& user);
void allVideo(); // �Լ� ���� �߰�

#endif
