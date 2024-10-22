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
#include <regex>
#include <limits>

#undef max // 'max' ��ũ�� ���� ����

User* currentUser = nullptr;

void signUp() {
    std::string userId, password, name, birthDate, phoneNumber;

    std::regex phoneRegex("^(010-[0-9]{4}-[0-9]{4}|02-[0-9]{3,4}-[0-9]{4}|[0-6]{3}-[0-9]{3,4}-[0-9]{4})$"); // '-'�� ���Ե� ��ȭ��ȣ�� ���� ǥ����
    std::regex phoneRegexNoDash("^(010[0-9]{8}|02[0-9]{7,8}|[0-6]{3}[0-9]{7,8})$"); // '-'�� �����Ե� ��ȭ��ȣ�� ���� ǥ����
    std::regex nameRegex("^[^0-9]+$"); // ���ڰ� ���Ե��� ���� �̸��� ���� ǥ����
    std::regex passwordRegex("^[^\uAC00-\uD7A3]+$"); // �ѱ��� ���Ե��� ���� ��й�ȣ�� ���� ǥ����
    std::regex birthDateRegex("^[0-9-]+$"); // �ѱ۰� ��� ���Ե��� ���� ��������� ���� ǥ����

    clearScreen();

    std::vector<User> users = loadUsers();

    std::cout << "ȸ�������� �����մϴ�." << std::endl;
    std::cout << "����� ID: ";
    std::cin >> userId;
    std::cin.ignore(); // ���� ����

    if (!isUserIdUnique(userId, users)) {
        std::cout << "�̹� �����ϴ� ����� ID�Դϴ�. �ٽ� �õ��Ͻʽÿ�." << std::endl;
        return;
    }

    while (true) {
        std::cout << "��й�ȣ: ";
        std::getline(std::cin, password);

        if (!std::regex_match(password, passwordRegex)) { // ��й�ȣ�� �ѱ��� ���Ե� ���
            std::cout << "��й�ȣ�� �ѱ��� ���Ե� �� �����ϴ�. �ٽ� �Է��ϼ���." << std::endl;
        }
        else {
            break;
        }
    }

    while (true) {
        std::cout << "�̸�: ";
        std::getline(std::cin, name);

        if (name.empty()) { // �̸��� ������ ���
            std::cout << "�̸��� ��� �ֽ��ϴ�. �ٽ� �Է��ϼ���." << std::endl;
        }
        else if (!std::regex_match(name, nameRegex)) { // �̸��� ���ڰ� ���Ե� ���
            std::cout << "�̸��� ���ڰ� ���Ե� �� �����ϴ�. �ٽ� �Է��ϼ���." << std::endl;
        }
        else {
            break;
        }
    }

    while (true) {
        std::cout << "������� (YYYY-MM-DD): ";
        std::getline(std::cin, birthDate);

        if (!std::regex_match(birthDate, birthDateRegex)) { // ������Ͽ� �ѱ۰� ��� ���Ե� ���
            std::cout << "������Ͽ� �ѱ۰� ��� ���Ե� �� �����ϴ�. �ٽ� �Է��ϼ���." << std::endl;
        }
        else {
            break;
        }
    }

    while (true) {
        std::cout << "��ȭ��ȣ: ";
        std::getline(std::cin, phoneNumber);

        if (phoneNumber.empty()) {
            std::cout << "��ȭ��ȣ�� ��� �ֽ��ϴ�. �ٽ� �Է��� �ּ���." << std::endl;
        }
        else if (std::regex_match(phoneNumber, phoneRegexNoDash)) { // - �߰�
            if (phoneNumber.substr(0, 2) == "02" && phoneNumber.length() == 9) { // ����������ȣ 2�ڸ�-3�ڸ�-4�ڸ�
                phoneNumber = phoneNumber.substr(0, 2) + "-" + phoneNumber.substr(2, 3) + "-" + phoneNumber.substr(5, 4);
            }
            else if (phoneNumber.substr(0, 2) == "02" && phoneNumber.length() == 10) { // ����������ȣ 2�ڸ�-4�ڸ�-4�ڸ�
                phoneNumber = phoneNumber.substr(0, 2) + "-" + phoneNumber.substr(2, 4) + "-" + phoneNumber.substr(6, 4);
            }
            else if ((phoneNumber.substr(0, 3) == "031" || phoneNumber.substr(0, 3) == "032" || phoneNumber.substr(0, 3) == "042" ||
                phoneNumber.substr(0, 3) == "051" || phoneNumber.substr(0, 3) == "052" || phoneNumber.substr(0, 3) == "053" ||
                phoneNumber.substr(0, 3) == "062" || phoneNumber.substr(0, 3) == "064" || phoneNumber.substr(0, 3) == "033" ||
                phoneNumber.substr(0, 3) == "041" || phoneNumber.substr(0, 3) == "043" || phoneNumber.substr(0, 3) == "054" ||
                phoneNumber.substr(0, 3) == "055" || phoneNumber.substr(0, 3) == "061" || phoneNumber.substr(0, 3) == "063") &&
                phoneNumber.length() == 10) { // ������ȣ 3�ڸ�-3�ڸ�-4�ڸ�
                phoneNumber = phoneNumber.substr(0, 3) + "-" + phoneNumber.substr(3, 3) + "-" + phoneNumber.substr(6, 4);
            }
            else if ((phoneNumber.substr(0, 3) == "031" || phoneNumber.substr(0, 3) == "032" || phoneNumber.substr(0, 3) == "042" ||
                phoneNumber.substr(0, 3) == "051" || phoneNumber.substr(0, 3) == "052" || phoneNumber.substr(0, 3) == "053" ||
                phoneNumber.substr(0, 3) == "062" || phoneNumber.substr(0, 3) == "064" || phoneNumber.substr(0, 3) == "033" ||
                phoneNumber.substr(0, 3) == "041" || phoneNumber.substr(0, 3) == "043" || phoneNumber.substr(0, 3) == "054" ||
                phoneNumber.substr(0, 3) == "055" || phoneNumber.substr(0, 3) == "061" || phoneNumber.substr(0, 3) == "063") &&
                phoneNumber.length() == 11) { // ������ȣ 3�ڸ�-4�ڸ�-4�ڸ�
                phoneNumber = phoneNumber.substr(0, 3) + "-" + phoneNumber.substr(3, 4) + "-" + phoneNumber.substr(7, 4);
            }
            else if (phoneNumber.substr(0, 3) == "010" && phoneNumber.length() == 11) {
                phoneNumber = phoneNumber.substr(0, 3) + "-" + phoneNumber.substr(3, 4) + "-" + phoneNumber.substr(7, 4); // �޴�����ȣ 010-4�ڸ�-4�ڸ�
            }
            else {
                std::cout << "�߸��� ��ȭ��ȣ �����Դϴ�. �ٽ� �Է��� �ּ���." << std::endl;
                continue;
            }
            break;
        }
        else if (std::regex_match(phoneNumber, phoneRegex)) { // - �ִ� ��� �н�
            break;
        }
        else {
            std::cout << "�߸��� ��ȭ��ȣ �����Դϴ�. ��ȭ��ȣ�� 010-xxxx-xxxx �Ǵ� 010xxxxxxxx �̰ų� ������ȭ�� ��� (������ȣ)-(x)xxx-xxxx, (������ȣ)(x)xxxxxxx �����̾�� �մϴ�." << std::endl;
        }
    }

    if (!isPhoneNumberUnique(phoneNumber, users)) {
        std::cout << "�̹� �����ϴ� ����� ��ȭ��ȣ �Դϴ�. �ٽ� �õ��Ͻʽÿ�." << std::endl;
        return;
    }

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

        // �뿩 ���� ������ �ε��Ͽ� ��ü ���� Ȯ��
        std::vector<std::tuple<std::string, std::string, std::time_t>> rentals = loadRentals();
        if (hasOverdueVideos(*user, rentals)) {
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

bool isUserIdUnique(const std::string& userId, const std::vector<User>& users) { // ID �ߺ� ��ȸ
    for (const auto& user : users) {
        if (user.userId == userId) {
            return false;
        }
    }
    return true;
}

bool isPhoneNumberUnique(const std::string& phoneNumber, const std::vector<User>& users) { // ��ȭ��ȣ �ߺ� ��ȸ
    for (const auto& user : users) {
        if (user.phoneNumber == phoneNumber) {
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

bool hasOverdueVideos(const User& user, const std::vector<std::tuple<std::string, std::string, std::time_t>>& rentals) {
    std::time_t now = std::time(nullptr);
    const int rentalPeriod = 7 * 24 * 60 * 60;

    for (const auto& rental : rentals) {
        if (std::get<0>(rental) == user.userId) {
            std::time_t rentalDate = std::get<2>(rental);
            if (now - rentalDate > rentalPeriod) {
                return true;
            }
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

        if (std::cin.fail()) { // ���ڰ� ���ð�� ����(�������Է¿� ������ ���)
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // �޴����� ���� �Է� ����
            continue;
        }

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