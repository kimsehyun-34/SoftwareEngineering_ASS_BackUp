#include "admin.h"
#include "utils.h"
#include "user.h"
#include "video.h"
#include <iostream>
#include <fstream>
#include <algorithm>

void adminMenu() {
    int choice;

    while (true) {
        clearScreen();

        std::cout << "===== ������ �޴� =====" << std::endl;
        std::cout << "1. ���� �߰�" << std::endl;
        std::cout << "2. ���� ����" << std::endl;
        std::cout << "3. ����ڿ��� ���� �߰�" << std::endl;
        std::cout << "4. ���� ����" << std::endl;
        std::cout << "5. �뿩 ���� Ȯ��" << std::endl;
        std::cout << "6. �α׾ƿ�" << std::endl;
        std::cout << "����: ";
        std::cin >> choice;

        switch (choice) {
        case 1:
            addVideo();
            break;
        case 2:
            returnVideo();
            break;
        case 3:
            addCoinsToUser();
            break;
        case 4:
            delVideo();
            break;
        case 5:
            checkVideoRentalStatus();
            break;
        case 6:
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

void addCoinsToUser() {
    std::string userId;
    int coinsToAdd;
    clearScreen();

    std::vector<User> users = loadUsers();

    std::cout << "������ �߰��� ����� ID: ";
    std::cin >> userId;

    auto it = std::find_if(users.begin(), users.end(), [&userId](const User& user) {
        return user.userId == userId;
        });

    if (it == users.end()) {
        std::cout << "����ڸ� ã�� �� �����ϴ�." << std::endl;
        return;
    }

    std::cout << "�߰��� ���� ��: ";
    std::cin >> coinsToAdd;

    it->coins += coinsToAdd;

    std::ofstream userFile("users.txt");
    for (const auto& user : users) {
        userFile << user.userId << "," << user.password << "," << user.name << "," << user.birthDate << "," << user.phoneNumber << "," << user.isAdmin << "," << user.coins << std::endl;
    }

    std::cout << "������ �߰��Ǿ����ϴ�." << std::endl;
}

void addVideo() { // ���� �߰� ���
    std::string videoName;
    clearScreen();

    std::cout << "���� �߰��� �����մϴ�." << std::endl;
    std::cout << "���� �̸�: ";
    std::cin.ignore(); // ���� �Է��� ���� ���ڸ� ����
    std::getline(std::cin, videoName);

    // ���� ������ ������ Ȯ���Ͽ� ������ ����
    std::ifstream infile("videos.txt");
    int videoCount = 0;
    std::string line;
    while (std::getline(infile, line)) {
        videoCount++;
    }
    infile.close();

    // ���� ������ ���Ͽ� ����
    std::ofstream outfile("videos.txt", std::ios_base::app);
    outfile << videoCount + 1 << ". " << videoName << std::endl;

    std::cout << "���� �߰��� �Ϸ�Ǿ����ϴ�." << std::endl;
}

void delVideo() {
    std::string videoName;
    clearScreen();

    std::cout << "���� ������ �����մϴ�." << std::endl;
    std::cout << "���� �̸�: ";
    std::cin.ignore();
    std::getline(std::cin, videoName);

    std::ifstream infile("videos.txt");
    std::vector<std::string> videoList;
    std::string line;
    while (std::getline(infile, line)) {
        videoList.push_back(line);
    }
    infile.close();

    std::vector<int> indices;
    for (size_t i = 0; i < videoList.size(); ++i) {
        if (videoList[i].find(videoName) != std::string::npos) {
            indices.push_back(i);
        }
    }

    if (indices.empty()) {
        std::cout << "�ش� �̸��� ������ ã�� �� �����ϴ�." << std::endl;
        return;
    }

    std::cout << "������ ������ �����Ͻʽÿ�" << std::endl;
    std::cout << "------------------------------------" << std::endl;
    for (size_t i = 0; i < indices.size(); ++i) {
        std::cout << i + 1 << ". " << videoList[indices[i]] << std::endl;
    }

    int choice;
    std::cout << "����: ";
    std::cin >> choice;

    if (choice < 1 || choice > indices.size()) {
        std::cout << "�߸��� �����Դϴ�. �۾��� ��ҵǾ����ϴ�." << std::endl;
        return;
    }

    videoList.erase(videoList.begin() + indices[choice - 1]);
    std::cout << "���� �Ϸ�." << std::endl;

    std::ofstream outfile("videos.txt");
    for (const auto& video : videoList) {
        outfile << video << std::endl;
    }
    outfile.close();
}

void addadmin() {
    std::string userId, password, name, birthDate, phoneNumber;
    clearScreen();

    std::vector<User> users = loadUsers();

    std::cout << "������ �߰��� �����մϴ�." << std::endl;
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
    outfile << userId << "," << password << "," << name << "," << birthDate << "," << phoneNumber << ",1,0" << std::endl;

    std::cout << "�����ڰ� �߰��Ǿ����ϴ�." << std::endl;
}