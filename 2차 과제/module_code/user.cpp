#include "user.h"
#include "utils.h"
#include "admin.h"
#include "video.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <ctime>
#include <windows.h>

User* currentUser = nullptr;

void signUp() {
    std::string userId, password, name, birthDate, phoneNumber;
    clearScreen();

    std::vector<User> users = loadUsers();

    std::cout << "ȸ�������� �����մϴ�." << std::endl;
    std::cout << "����� ID: ";
    std::cin >> userId;

    if (!isUserIdUnique(userId, users)) {
        std::cout << "�̹� �����ϴ� ����� ID�Դϴ�. �ٽ� �õ��Ͻʽÿ�." << std::endl;
        return;
    }

    std::cout << "��й�ȣ: ";
    std::cin >> password;
    std::cout << "�̸�: ";
    std::cin >> name;
    std::cout << "������� (YYYY-MM-DD): ";
    std::cin >> birthDate;
    std::cout << "��ȭ��ȣ: ";
    std::cin >> phoneNumber;

    std::ofstream outfile("users.txt", std::ios_base::app);
    outfile << userId << "," << password << "," << name << "," << birthDate << "," << phoneNumber << ",0,0" << std::endl;

    std::cout << "ȸ�������� �Ϸ�Ǿ����ϴ�." << std::endl;
}

void login() {
    std::string userId, password;
    clearScreen();

    std::vector<User> users = loadUsers();

    std::cout << "�α����� �����մϴ�." << std::endl;
    std::cout << "����� ID: ";
    std::cin >> userId;
    std::cout << "��й�ȣ: ";
    std::cin >> password;

    clearScreen();
    User* user = authenticateUser(userId, password, users);
    if (user) {
        currentUser = user;
        if (hasOverdueVideos(*user)) {
            std::cout << "***���***  !!��ü�� ������ �ֽ��ϴ�!! ***���***" << std::endl;
            Sleep(4000);
        }
        if (user->isAdmin) {
            adminMenu();
        }
        else {
            userMenu();
        }
    }
    else {
        std::cout << "�α��� ����. ����� ID �Ǵ� ��й�ȣ�� �߸��Ǿ����ϴ�." << std::endl;
    }
}

bool isUserIdUnique(const std::string& userId, const std::vector<User>& users) {
    for (const auto& user : users) {
        if (user.userId == userId) {
            return false;
        }
    }
    return true;
}

User* authenticateUser(const std::string& userId, const std::string& password, std::vector<User>& users) {
    for (auto& user : users) {
        if (user.userId == userId && user.password == password) {
            return &user;
        }
    }
    return nullptr;
}

bool hasOverdueVideos(const User& user) {
    std::time_t now = std::time(nullptr);
    const int rentalPeriod = 7 * 24 * 60 * 60;

    for (const auto& rental : user.rentedVideos) {
        std::time_t rentalDate = std::get<1>(rental);
        if (now - rentalDate > rentalPeriod) {
            return true;
        }
    }
    return false;
}

void userMenu() {
    int choice;
    while (true) {
        clearScreen();

        std::cout << "===== ����� �޴� =====" << std::endl;
        std::cout << "���� ���� ��: " << currentUser->coins << std::endl;
        std::cout << "========================" << std::endl;

        std::cout << "1. ��ü ���� ���" << std::endl;
        std::cout << "2. ���� �뿩" << std::endl;
        std::cout << "3. �뿩 �Ⱓ Ȯ��" << std::endl;
        std::cout << "4. �α׾ƿ�" << std::endl;
        std::cout << "����: ";
        std::cin >> choice;

        switch (choice) {
        case 1:
            allVideo();
            break;
        case 2:
            rentVideo();
            break;
        case 3:
            checkRemainingDays();
            break;
        case 4:
            return;
        default:
            std::cout << "�߸��� �����Դϴ�." << std::endl;
            break;
        }
        std::cout << "�޴��� �̵��Ϸ��� �ƹ� Ű�� �����ʽÿ�...";
        std::cin.ignore();
        std::cin.get();
    }
}