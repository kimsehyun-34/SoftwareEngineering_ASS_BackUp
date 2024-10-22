#include "admin.h"
#include "utils.h"
#include "user.h"
#include "video.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <limits>

// ����: ctime_s�� ���� �����÷ο츦 �����ϴ� ������ �Լ��Դϴ�.
// ȣȯ�� : ���� �ڵ�� ���� ������ �� �ֽ��ϴ�.
// ������ : ������ �����ϰ� �����ϱ� �����ϴ�.

void adminMenu() {
    int choice;

    while (true) {
        clearScreen();

        std::cout << "===== ������ �޴� =====" << std::endl;
        std::cout << "1. ���� �߰�" << std::endl;
        std::cout << "2. ���� �ݳ�" << std::endl;
        std::cout << "3. ����ڿ��� ���� �߰�" << std::endl;
        std::cout << "4. ���� ����" << std::endl;
        std::cout << "5. �뿩 ���� Ȯ��" << std::endl;
        std::cout << "6. ��� ����� ���" << std::endl; // ���ο� �޴� �׸� �߰�
        std::cout << "7. ������ �߰�" << std::endl;
        std::cout << "8. �α׾ƿ�" << std::endl;
        std::cout << "����: ";
        std::cin >> choice;

        if (std::cin.fail()) { // ���ڰ� ���ð�� ����(�������Է¿� ������ ���)
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // �޴����� ���� �Է� ����
            continue;
        }

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
            printAllUsers();
            break;
        case 7:
            addadmin();
            break;
        case 8:
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

    // ����� ��� �ε�
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

    // ����� ������ ���Ͽ� ����
    saveUsers(users);

    std::cout << "������ �߰��Ǿ����ϴ�." << std::endl;
}


void addVideo() { // ���� �߰� ���
    std::string videoName, directorName;
    clearScreen();

    std::cout << "���� �̸�: ";
    std::cin.ignore();
    std::getline(std::cin, videoName);

    std::cout << "���� �̸�: ";
    std::cin.ignore();
    std::getline(std::cin, directorName);

    // ���� ��� �ε�
    std::vector<std::tuple<std::string, std::string, std::string>> videos = loadVideos();

    // ���� ������ ������ Ȯ���Ͽ� ������ ����
    size_t videoCount = videos.size();

    // ���ο� ���� �߰�
    videos.push_back(std::make_tuple(std::to_string(videoCount + 1), videoName, directorName));

    // ���� ������ ���Ͽ� ����
    saveVideos(videos);

    std::cout << "���� �߰��� �Ϸ�Ǿ����ϴ�." << std::endl;
}


void delVideo() {
    std::string videoName;
    clearScreen();

    std::cout << "���� ������ �����մϴ�." << std::endl;
    std::cout << "���� �̸�: ";
    std::cin.ignore();
    std::getline(std::cin, videoName);

    // ���� ��� �ε�
    std::vector<std::tuple<std::string, std::string, std::string>> videos = loadVideos();

    std::vector<int> indices;
    for (size_t i = 0; i < videos.size(); ++i) {
        if (std::get<1>(videos[i]).find(videoName) != std::string::npos) {
            indices.push_back(static_cast<int>(i));
        }
    }

    if (indices.empty()) {
        std::cout << "�ش� �̸��� ������ ã�� �� �����ϴ�." << std::endl;
        return;
    }

    std::cout << "������ ������ �����Ͻʽÿ�" << std::endl;
    std::cout << "------------------------------------" << std::endl;
    for (size_t i = 0; i < indices.size(); ++i) {
        std::cout << i + 1 << ". " << std::get<1>(videos[indices[i]]) << std::endl;
    }

    int choice;
    std::cout << "����: ";
    std::cin >> choice;

    if (choice < 1 || choice > static_cast<int>(indices.size())) {
        std::cout << "�߸��� �����Դϴ�." << std::endl;
        return;
    }

    // ������ ���� ����
    videos.erase(videos.begin() + indices[choice - 1]);

    // ���� ������ ���Ͽ� ����
    saveVideos(videos);

    std::cout << "������ �����Ǿ����ϴ�." << std::endl;
}


void addadmin() {
    std::string userId;
    clearScreen();

    std::cout << "������ �߰��� �����մϴ�." << std::endl;
    std::cout << "�߰��� ������ ID: ";
    std::cin >> userId;

    // ����� ��� �ε�
    std::vector<User> users = loadUsers();

    auto it = std::find_if(users.begin(), users.end(), [&userId](const User& user) {
        return user.userId == userId;
        });

    if (it == users.end()) {
        std::cout << "����ڸ� ã�� �� �����ϴ�." << std::endl;
        return;
    }

    it->isAdmin = true;

    // ����� ������ ���Ͽ� ����
    saveUsers(users);

    std::cout << "�����ڰ� �߰��Ǿ����ϴ�." << std::endl;
}


void printAllUsers() {
    clearScreen();

    // ����� ��� �ε�
    std::vector<User> users = loadUsers();

    std::cout << "===== ��� ����� ��� =====" << std::endl;
    for (const auto& user : users) {
        std::cout << "ID: " << user.userId << std::endl;
        std::cout << "�̸�: " << user.name << std::endl;
        std::cout << "�������: " << user.birthDate << std::endl;
        std::cout << "��ȭ��ȣ: " << user.phoneNumber << std::endl;
        std::cout << "������ ����: " << (user.isAdmin ? "��" : "�ƴϿ�") << std::endl;
        std::cout << "����: " << user.coins << std::endl;

        std::cout << "--------------------------" << std::endl;
    }
}
