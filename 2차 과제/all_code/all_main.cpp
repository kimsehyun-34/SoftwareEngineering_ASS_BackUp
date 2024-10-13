#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ctime> // ���� ��¥�� �������� ����
#include <tuple> // std::make_tuple�� ����ϱ� ���� <tuple> ����� �߰��մϴ�.
#include <algorithm>  // std::replace�� ����ϱ� ���� �߰�
#include <sstream> // <sstream> ����� �߰��Ͽ� std::istringstream�� ����� �� �ֵ��� �մϴ�.
#include <windows.h>
#include <iomanip>

struct User {
    std::string userId;
    std::string password;
    std::string name;
    std::string birthDate;
    std::string phoneNumber;
    bool isAdmin; // ���� ���θ� ��Ÿ���� �ʵ� �߰�
    int coins; // ����ڰ� ������ �ִ� ���� ��
    std::vector<std::tuple<std::string, std::time_t>> rentedVideos; // �뿩�� ������ �뿩 ��¥�� �����ϴ� �ʵ� �߰�
};

void signUp();
void login();
void clearScreen();
std::vector<User> loadUsers();
bool isUserIdUnique(const std::string& userId, const std::vector<User>& users);
User* authenticateUser(const std::string& userId, const std::string& password, std::vector<User>& users);
void adminMenu();
void userMenu();
void allVideo();
void checkVideoRentalStatus();
void returnVideo();
void rentVideo();
void checkRemainingDays();
void addVideo();
void addadmin();
void delVideo();
bool hasOverdueVideos(const User& user);

int main() {
    int choice;

    while (true) {
        clearScreen();

        std::cout << "�޴��� �����ϼ���:" << std::endl;
        std::cout << "1. �α���" << std::endl;
        std::cout << "2. ȸ������" << std::endl;
        std::cout << "3. ����" << std::endl;
        std::cout << "����: ";
        std::cin >> choice;

        switch (choice) {
        case 1:
            login();
            break;
        case 2:
            signUp();
            break;
        case 3:
            std::cout << "���α׷��� �����մϴ�." << std::endl;
            return 0;
        default:
            std::cout << "�߸��� �����Դϴ�." << std::endl;
            break;
        }
        std::cout << "�޴��� �̵��Ϸ��� ���� Ű�� ��������...";
        std::cin.ignore();
        std::cin.get();
    }

    return 0;
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

        // ��¥ ���ڿ��� std::time_t�� ��ȯ
        std::tm tm = {};
        std::istringstream dateStream(dateStr);
        dateStream >> std::get_time(&tm, "%Y-%m-%d");
        std::time_t rentalDate = std::mktime(&tm);

        rentals.push_back(std::make_tuple(userId, videoId, rentalDate));
    }
    return rentals;
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

    // rentals.txt���� �뿩 ������ �о�ͼ� ����� ��ü�� �߰�
    std::vector<std::tuple<std::string, std::string, std::time_t>> rentals = loadRentals();
    for (auto& rental : rentals) {
        std::string userId = std::get<0>(rental);
        std::string videoId = std::get<1>(rental);
        std::time_t rentalDate = std::get<2>(rental);

        auto it = std::find_if(users.begin(), users.end(), [&userId](const User& user) {
            return user.userId == userId;
            });

        if (it != users.end()) {
            it->rentedVideos.push_back(std::make_tuple(videoId, rentalDate));
        }
    }

    return users;
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

void signUp() {
    std::string userId, password, name, birthDate, phoneNumber;
    clearScreen();

    std::vector<User> users = loadUsers();

    std::cout << "ȸ�������� �����մϴ�." << std::endl;
    std::cout << "���� ID: ";
    std::cin >> userId;

    if (!isUserIdUnique(userId, users)) {
        std::cout << "�̹� �����ϴ� ���� ID�Դϴ�. �ٽ� �õ����ּ���." << std::endl;
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

User* currentUser = nullptr;

void login() {
    std::string userId, password;
    clearScreen();

    std::vector<User> users = loadUsers();

    std::cout << "�α����� �����մϴ�." << std::endl;
    std::cout << "���� ID: ";
    std::cin >> userId;
    std::cout << "��й�ȣ: ";
    std::cin >> password;

    clearScreen();
    User* user = authenticateUser(userId, password, users);
    if (user) {
        currentUser = user;
        if (hasOverdueVideos(*user)) {
            std::cout << "***����***  !!���� ��ü�� ������ �ֽ��ϴ�!! ***����***" << std::endl;
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
        std::cout << "�α��� ����. ���� ID �Ǵ� ��й�ȣ�� �߸��Ǿ����ϴ�." << std::endl;
    }
}

bool hasOverdueVideos(const User& user) {
    std::time_t now = std::time(nullptr); // ���� �ð��� �����ɴϴ�.
    const int rentalPeriod = 7 * 24 * 60 * 60; // �뿩 �Ⱓ�� 7��(�� ����)�� �����մϴ�.

    for (const auto& rental : user.rentedVideos) {
        std::time_t rentalDate = std::get<1>(rental);
        if (now - rentalDate > rentalPeriod) {
            return true; // ��ü�� ������ ������ true�� ��ȯ�մϴ�.
        }
    }
    return false; // ��ü�� ������ ������ false�� ��ȯ�մϴ�.
}



void addCoinsToUser() {
    std::string userId;
    int coinsToAdd;
    clearScreen();

    std::vector<User> users = loadUsers();

    std::cout << "������ �߰��� ���� ID: ";
    std::cin >> userId;

    auto it = std::find_if(users.begin(), users.end(), [&userId](const User& user) {
        return user.userId == userId;
        });

    if (it == users.end()) {
        std::cout << "������ ã�� �� �����ϴ�." << std::endl;
        return;
    }

    std::cout << "�߰��� ���� ��: ";
    std::cin >> coinsToAdd;

    it->coins += coinsToAdd;

    // ����� ���� ������Ʈ
    std::ofstream userFile("users.txt");
    for (const auto& user : users) {
        userFile << user.userId << "," << user.password << "," << user.name << "," << user.birthDate << "," << user.phoneNumber << "," << (user.isAdmin ? "1" : "0") << "," << user.coins << std::endl;
    }

    std::cout << "������ �߰��Ǿ����ϴ�." << std::endl;
}

void adminMenu() {
    int choice;

    while (true) {
        clearScreen();

        std::cout << "===== ������ �޴� =====" << std::endl;
        std::cout << "1. ���� �߰�" << std::endl;
        std::cout << "2. ���� �ݳ�" << std::endl;
        std::cout << "3. �������� ���� �߰�" << std::endl;
        std::cout << "4. ���� ����" << std::endl;
        std::cout << "5. �뿩 ���� ��ȸ" << std::endl;
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
        std::cout << "�޴��� �̵��Ϸ��� ���� Ű�� ��������...";
        std::cin.ignore();
        std::cin.get();
    }
}

void userMenu() {
    int choice;
    while (true) {
        clearScreen();

        std::cout << "===== ����� �޴� =====" << std::endl;
        std::cout << "���� ���� ����: " << currentUser->coins << std::endl; // ���� ���� ���� �� ���
        std::cout << "========================" << std::endl;

        std::cout << "1. ��ü ���� ����Ʈ" << std::endl;
        std::cout << "2. ���� �뿩" << std::endl;
        std::cout << "3. �뿩 ���� �ܿ��� Ȯ��" << std::endl;
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
        std::cout << "�޴��� �̵��Ϸ��� ���� Ű�� ��������...";
        std::cin.ignore();
        std::cin.get();
    }
}


void allVideo() {
    clearScreen();

    std::ifstream videoFile("videos.txt");
    std::ifstream rentalFile("rentals.txt");
    std::string line;
    std::vector<std::string> videoList;
    std::vector<std::string> rentedVideos;

    // �뿩 ���� ���� ����� �����ɴϴ�.
    while (std::getline(rentalFile, line)) {
        size_t pos1 = line.find(',');
        size_t pos2 = line.find(',', pos1 + 1);
        std::string videoId = line.substr(pos1 + 1, pos2 - pos1 - 1);
        rentedVideos.push_back(videoId);
    }

    // ���� ����� �����ɴϴ�.
    while (std::getline(videoFile, line)) {
        videoList.push_back(line);
    }

    // ���� �̸��� ������������ �����մϴ�.
    std::sort(videoList.begin(), videoList.end());

    std::cout << "��ü ���� ���:" << std::endl;
    for (const auto& video : videoList) {
        std::string videoId = video.substr(0, video.find(". "));
        bool isRented = std::find(rentedVideos.begin(), rentedVideos.end(), videoId) != rentedVideos.end();
        std::cout << video << (isRented ? " (�뿩��)" : "") << std::endl;
    }

    videoFile.close();
    rentalFile.close();
}



void checkVideoRentalStatus() {
    clearScreen();

    std::ifstream rentalFile("rentals.txt");
    std::string line;
    std::vector<std::tuple<std::string, std::string, std::string>> rentalList; // <UserId, VideoId, RentalDate>

    while (std::getline(rentalFile, line)) {
        size_t pos1 = line.find(',');
        size_t pos2 = line.find(',', pos1 + 1);
        std::string rentalUserId = line.substr(0, pos1);
        std::string videoId = line.substr(pos1 + 1, pos2 - pos1 - 1);
        std::string rentalDate = line.substr(pos2 + 1);

        rentalList.push_back(std::make_tuple(rentalUserId, videoId, rentalDate));
    }
    rentalFile.close();

    if (rentalList.empty()) {
        std::cout << "���� �뿩 ���� ������ �����ϴ�." << std::endl;
        return;
    }

    std::cout << "���� �뿩 ���� ���� ���:" << std::endl;
    for (const auto& rental : rentalList) {
        std::string rentalUserId = std::get<0>(rental);
        std::string videoId = std::get<1>(rental);
        std::string rentalDate = std::get<2>(rental);

        // ���� �̸� ��������
        std::ifstream videoFile("videos.txt");
        std::string videoName;
        while (std::getline(videoFile, line)) {
            if (line.find(videoId + ". ") == 0) {
                videoName = line.substr(line.find(". ") + 2);
                break;
            }
        }
        videoFile.close();

        std::cout << "���� ID: " << rentalUserId << ", ���� ID: " << videoId << ", �̸�: " << videoName << ", �뿩 ��¥: " << rentalDate << std::endl;
    }

    std::cout << "�޴��� ���ư����� ���� Ű�� ��������...";
    std::cin.ignore();
    std::cin.get();
}


void returnVideo() {
    std::string userId;
    clearScreen();

    std::vector<User> users = loadUsers();

    std::cout << "������ �ݳ��� ���� ID: ";
    std::cin >> userId;

    auto it = std::find_if(users.begin(), users.end(), [&userId](const User& user) {
        return user.userId == userId;
        });

    if (it == users.end()) {
        std::cout << "������ ã�� �� �����ϴ�." << std::endl;
        return;
    }

    std::ifstream rentalFile("rentals.txt");
    std::string line;
    std::vector<std::tuple<std::string, std::string, std::string>> rentalList; // <UserId, VideoId, RentalDate>

    while (std::getline(rentalFile, line)) {
        size_t pos1 = line.find(',');
        size_t pos2 = line.find(',', pos1 + 1);
        std::string rentalUserId = line.substr(0, pos1);
        std::string videoId = line.substr(pos1 + 1, pos2 - pos1 - 1);
        std::string rentalDate = line.substr(pos2 + 1);

        if (rentalUserId == userId) {
            rentalList.push_back(std::make_tuple(rentalUserId, videoId, rentalDate));
        }
    }
    rentalFile.close();

    if (rentalList.empty()) {
        std::cout << "���� �뿩 ���� ������ �����ϴ�." << std::endl;
        return;
    }

    std::cout << "���� �뿩 ���� ���� ���:" << std::endl;
    for (size_t i = 0; i < rentalList.size(); ++i) {
        std::string videoId = std::get<1>(rentalList[i]);
        std::string rentalDate = std::get<2>(rentalList[i]);

        // ���� �̸� ��������
        std::ifstream videoFile("videos.txt");
        std::string videoName;
        while (std::getline(videoFile, line)) {
            if (line.find(videoId + ". ") == 0) {
                videoName = line.substr(line.find(". ") + 2);
                break;
            }
        }
        videoFile.close();

        std::cout << i + 1 << ". ���� ID: " << videoId << ", �̸�: " << videoName << ", �뿩 ��¥: " << rentalDate << std::endl;
    }

    int choice;
    std::cout << "�ݳ��� ���� ��ȣ�� �����ϼ���: ";
    std::cin >> choice;

    if (choice < 1 || choice > rentalList.size()) {
        std::cout << "�߸��� �����Դϴ�." << std::endl;
        return;
    }

    std::string videoIdToReturn = std::get<1>(rentalList[choice - 1]);

    // rentals.txt ���Ͽ��� �ش� ���� �뿩 ��� ����
    std::ifstream inFile("rentals.txt");
    std::vector<std::string> lines;
    while (std::getline(inFile, line)) {
        if (line.find(userId + "," + videoIdToReturn + ",") != 0) {
            lines.push_back(line);
        }
    }
    inFile.close();

    std::ofstream outFile("rentals.txt");
    for (const auto& l : lines) {
        outFile << l << std::endl;
    }
    outFile.close();

    std::cout << "������ �ݳ��Ǿ����ϴ�." << std::endl;
}


void checkRemainingDays() {
    if (currentUser == nullptr) {
        std::cout << "�α����� �ʿ��մϴ�." << std::endl;
        return;
    }

    std::ifstream rentalFile("rentals.txt");
    std::string line;
    std::vector<std::tuple<std::string, std::string, std::string>> rentalList; // <UserId, VideoId, RentalDate>

    while (std::getline(rentalFile, line)) {
        size_t pos1 = line.find(',');
        size_t pos2 = line.find(',', pos1 + 1);
        std::string userId = line.substr(0, pos1);
        std::string videoId = line.substr(pos1 + 1, pos2 - pos1 - 1);
        std::string rentalDate = line.substr(pos2 + 1);

        if (userId == currentUser->userId) {
            rentalList.push_back(std::make_tuple(userId, videoId, rentalDate));
        }
    }
    rentalFile.close();

    if (rentalList.empty()) {
        std::cout << "���� �뿩 ���� ������ �����ϴ�." << std::endl;
        return;
    }

    std::cout << "���� �뿩 ���� ���� ���:" << std::endl;
    for (const auto& rental : rentalList) {
        std::string videoId = std::get<1>(rental);
        std::string rentalDate = std::get<2>(rental);

        // �뿩 ��¥�� �Ľ�
        std::tm rentalTm = {};
        std::string year, month, day;
        std::replace(rentalDate.begin(), rentalDate.end(), '-', ' ');
        std::istringstream ss(rentalDate);
        ss >> year >> month >> day;
        rentalTm.tm_year = std::stoi(year) - 1900;
        rentalTm.tm_mon = std::stoi(month) - 1;
        rentalTm.tm_mday = std::stoi(day);

        // ���� ��¥�� ��������
        std::time_t t = std::time(nullptr); // ���� �ð��� time_t Ÿ������ ��������
        std::tm now; 
        localtime_s(&now, &t);  

        // ���� ���� ���
        std::time_t rentalTime = std::mktime(&rentalTm);
        std::time_t nowTime = std::mktime(&now);
        double seconds = std::difftime(nowTime, rentalTime);
        int days = static_cast<int>(seconds / (60 * 60 * 24));

        // ���� �̸� ��������
        std::ifstream videoFile("videos.txt");
        std::string videoName;
        while (std::getline(videoFile, line)) {
            if (line.find(videoId + ". ") == 0) {
                videoName = line.substr(line.find(". ") + 2);
                break;
            }
        }
        videoFile.close();

        clearScreen();

        std::cout << "�뿩 ���� ����Ʈ" << std::endl;

        std::cout << "���� ID: " << videoId << ", �̸�: " << videoName << ", ���� ����: " << (7 - days) << "��" << std::endl;
    }
}

void delVideo() {
    std::string videoName;
    clearScreen();

    std::cout << "���� ������ �����մϴ�." << std::endl;
    std::cout << "���� �̸�: ";
    std::cin.ignore(); // ���� �Է��� ���� ���ڸ� ����
    std::getline(std::cin, videoName);

    // ���� ����� �о��
    std::ifstream infile("videos.txt");
    std::vector<std::string> videoList;
    std::string line;
    while (std::getline(infile, line)) {
        videoList.push_back(line);
    }
    infile.close();

    // �Էµ� �̸��� ��ġ�ϴ� ������ ã��
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

    std::cout << "������ ������ �����ϼ���" << std::endl;
    std::cout << "------------------------------------" << std::endl;
    for (size_t i = 0; i < indices.size(); ++i) {
        std::cout << "------------------------------------" << std::endl;
        std::cout << i + 1 << ". ���� id: " << indices[i] << ", ���� �̸�: " << videoList[indices[i]] << std::endl;
    }

    int choice;
    std::cout << "����: ";
    std::cin >> choice;

    if (choice < 1 || choice > indices.size()) {
        std::cout << "�߸��� �����Դϴ�. ������ ��ҵǾ����ϴ�." << std::endl;
        return;
    }

    // ���õ� ������ ����
    videoList.erase(videoList.begin() + indices[choice - 1]);
    std::cout << "���� �Ϸ�." << std::endl;

    // ����� ���� ����� ���Ͽ� ����
    std::ofstream outfile("videos.txt");
    for (const auto& video : videoList) {
        outfile << video << std::endl;
    }
    outfile.close();
}




void rentVideo() {
    if (currentUser == nullptr) {
        std::cout << "�α����� �ʿ��մϴ�." << std::endl;
        return;
    }

    // ��ü ���� Ȯ��
    if (hasOverdueVideos(*currentUser)) {
        std::cout << "��ü ���� ������ �־� �뿩�� �� �����ϴ�." << std::endl;
        return;
    }

    const int rentalCost = 1; // ���� �뿩 ���

    if (currentUser->coins < rentalCost) {
        std::cout << "������ �����մϴ�. �����ڿ��� �����ϼ���." << std::endl;
        return;
    }

    std::string videoName;
    clearScreen();

    std::cout << "���� �뿩�� �����մϴ�." << std::endl;
    std::cout << "���� �̸�(�Ϻ� �Է� ����): ";
    std::cin.ignore(); // ���� �Է��� ���� ���ڸ� ����
    std::getline(std::cin, videoName);

    // ���� ID�� ã�� ���� ������ ����
    std::ifstream infile("videos.txt");
    std::string line;
    std::vector<std::pair<std::string, std::string>> videoList; // <ID, Name>
    while (std::getline(infile, line)) {
        size_t pos = line.find(". ");
        if (pos != std::string::npos) {
            std::string name = line.substr(pos + 2);
            if (name.find(videoName) != std::string::npos) {
                videoList.push_back({ line.substr(0, pos), name });
            }
        }
    }
    infile.close();

    if (videoList.empty()) {
        std::cout << "������ ã�� �� �����ϴ�." << std::endl;
        return;
    }

    // �뿩 ������ ���� ID�� ã�� ���� ������ ����
    std::ifstream rentalFile("rentals.txt");
    std::vector<std::string> rentedVideoIds;
    while (std::getline(rentalFile, line)) {
        size_t pos = line.find(',');
        std::string rentedVideoId = line.substr(pos + 1, line.find(',', pos + 1) - pos - 1);
        rentedVideoIds.push_back(rentedVideoId);
    }
    rentalFile.close();

    std::cout << "�˻��� ���� ���:" << std::endl;
    for (size_t i = 0; i < videoList.size(); ++i) {
        std::string videoId = videoList[i].first;
        std::string videoDisplayName = videoList[i].second;

        if (std::count(rentedVideoIds.begin(), rentedVideoIds.end(), videoId) > 0) {
            videoDisplayName += " (�뿩�Ұ�)";
        }

        std::cout << i + 1 << ". " << videoDisplayName << std::endl;
    }

    int choice;
    std::cout << "�뿩�� ���� ��ȣ�� �����ϼ���: ";
    std::cin >> choice;

    if (choice < 1 || choice > videoList.size()) {
        std::cout << "�߸��� �����Դϴ�." << std::endl;
        return;
    }

    std::string selectedVideoId = videoList[choice - 1].first;

    if (std::count(rentedVideoIds.begin(), rentedVideoIds.end(), selectedVideoId) > 0) {
        std::cout << "������ ������ �̹� �뿩 ���Դϴ�." << std::endl;
        return;
    }

    // ���� ��¥�� ��������
    std::time_t t = std::time(nullptr); // ���� �ð��� time_t Ÿ������ ��������
    std::tm now;   // std::tm ����ü�� ���� ����
    localtime_s(&now, &t);   // localtime_s�� ����Ͽ� �����ϰ� tm ����ü�� �ʱ�ȭ
    char dateStr[11]; // ��¥�� ������ ���ڿ� ����
    std::strftime(dateStr, sizeof(dateStr), "%Y-%m-%d", &now); // ���˿� �°� ��¥ ���ڿ��� ��ȯ

    // �뿩 ������ ���Ͽ� ����
    std::ofstream outfile("rentals.txt", std::ios_base::app);
    outfile << currentUser->userId << "," << selectedVideoId << "," << dateStr << std::endl;

    // ���� ����
    currentUser->coins -= rentalCost;

    // ����� ���� ������Ʈ (���� ������)
    std::vector<User> users = loadUsers();
    std::ofstream userFile("users.txt");
    for (auto& user : users) {
        if (user.userId == currentUser->userId) {
            user.coins = currentUser->coins;
        }
        userFile << user.userId << "," << user.password << "," << user.name << "," << user.birthDate << "," << user.phoneNumber << "," << (user.isAdmin ? "1" : "0") << "," << user.coins << std::endl;
    }

    std::cout << "���� �뿩�� �Ϸ�Ǿ����ϴ�." << std::endl;
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

void addadmin() {
    // ���� �߰� ���
    std::string userId, password, name, birthDate, phoneNumber;
    clearScreen();

    std::vector<User> users = loadUsers();

    std::cout << "���� �߰��� �����մϴ�." << std::endl;
    std::cout << "���� ID: ";
    std::cin >> userId;

    if (!isUserIdUnique(userId, users)) {
        std::cout << "�̹� �����ϴ� ���� ID�Դϴ�. �ٽ� �õ����ּ���." << std::endl;
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
    outfile << userId << "," << password << "," << name << "," << birthDate << "," << phoneNumber << ",1" << std::endl;

    std::cout << "���� �߰��� �Ϸ�Ǿ����ϴ�." << std::endl;
}

// ���â �ʱ�ȭ
void clearScreen() {
    system("cls");  // ���н� OS�� ��� clear
}
