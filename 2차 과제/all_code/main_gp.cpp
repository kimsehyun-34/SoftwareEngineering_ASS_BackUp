//#include <iostream>
//#include <vector>
//#include <fstream>
//#include <string>
//#include <ctime>
//
//using namespace std;
//
//class Video {
//public:
//    int id;
//    string title;
//    bool isRented;
//
//    Video(int id, string title) : id(id), title(title), isRented(false) {}
//};
//
//class User {
//public:
//    int id;
//    string name;
//    vector<int> rentedVideos;
//
//    User(int id, string name) : id(id), name(name) {}
//};
//
//vector<Video> videos;
//vector<User> users;
//
//void loadVideos() {
//    ifstream file("videos.txt");
//    if (file.is_open()) {
//        int id;
//        string title;
//        while (file >> id >> title) {
//            videos.push_back(Video(id, title));
//        }
//        file.close();
//    }
//}
//
//void saveVideos() {
//    ofstream file("videos.txt");
//    if (file.is_open()) {
//        for (const auto& video : videos) {
//            file << video.id << " " << video.title << endl;
//        }
//        file.close();
//    }
//}
//
//void loadUsers() {
//    ifstream file("users.txt");
//    if (file.is_open()) {
//        int id;
//        string name;
//        while (file >> id >> name) {
//            users.push_back(User(id, name));
//        }
//        file.close();
//    }
//}
//
//void saveUsers() {
//    ofstream file("users.txt");
//    if (file.is_open()) {
//        for (const auto& user : users) {
//            file << user.id << " " << user.name << endl;
//        }
//        file.close();
//    }
//}
//
//void rentVideo(User& user) {
//    int videoId;
//    cout << "�뿩�� ���� ID�� �Է��ϼ���: ";
//    cin >> videoId;
//    for (auto& video : videos) {
//        if (video.id == videoId && !video.isRented) {
//            video.isRented = true;
//            user.rentedVideos.push_back(videoId);
//            cout << "������ ���������� �뿩�Ǿ����ϴ�." << endl;
//            return;
//        }
//    }
//    cout << "������ �뿩�� �� �����ϴ�." << endl;
//}
//
//void searchVideo() {
//    string title;
//    cout << "�˻��� ���� ������ �Է��ϼ���: ";
//    cin >> title;
//    for (const auto& video : videos) {
//        if (video.title == title) {
//            cout << "���� ID: " << video.id << ", ����: " << video.title << ", �뿩 ����: " << (video.isRented ? "�뿩��" : "�뿩 ����") << endl;
//        }
//    }
//}
//
//void checkRentalDays(User& user) {
//    cout << "�뿩�� ���� ���:" << endl;
//    for (const auto& videoId : user.rentedVideos) {
//        for (const auto& video : videos) {
//            if (video.id == videoId) {
//                cout << "���� ID: " << video.id << ", ����: " << video.title << endl;
//            }
//        }
//    }
//}
//
//void returnVideo() {
//    int videoId;
//    cout << "�ݳ��� ���� ID�� �Է��ϼ���: ";
//    cin >> videoId;
//    for (auto& video : videos) {
//        if (video.id == videoId && video.isRented) {
//            video.isRented = false;
//            cout << "������ ���������� �ݳ��Ǿ����ϴ�." << endl;
//            return;
//        }
//    }
//    cout << "������ �ݳ��� �� �����ϴ�." << endl;
//}
//
//void userMenu(User& user) {
//    int choice;
//    do {
//        cout << "1. ���� �뿩\n2. ���� �˻�\n3. �뿩 �ܿ��� Ȯ��\n4. �α׾ƿ�\n����: ";
//        cin >> choice;
//        switch (choice) {
//        case 1:
//            rentVideo(user);
//            break;
//        case 2:
//            searchVideo();
//            break;
//        case 3:
//            checkRentalDays(user);
//            break;
//        case 4:
//            return;
//        default:
//            cout << "�߸��� �����Դϴ�." << endl;
//        }
//    } while (choice != 4);
//}
//
//void adminMenu() {
//    int choice;
//    do {
//        cout << "1. �뿩 ���� ��ȸ\n2. ���� �ݳ�\n3. ���� �˻�\n4. �α׾ƿ�\n����: ";
//        cin >> choice;
//        switch (choice) {
//        case 1:
//            for (const auto& video : videos) {
//                if (video.isRented) {
//                    cout << "���� ID: " << video.id << ", ����: " << video.title << endl;
//                }
//            }
//            break;
//        case 2:
//            returnVideo();
//            break;
//        case 3:
//            searchVideo();
//            break;
//        case 4:
//            return;
//        default:
//            cout << "�߸��� �����Դϴ�." << endl;
//        }
//    } while (choice != 4);
//}
//
//void registerUser() {
//    int id;
//    string name;
//    cout << "�� ����� ID�� �Է��ϼ���: ";
//    cin >> id;
//    for (const auto& user : users) {
//        if (user.id == id) {
//            cout << "�̹� �����ϴ� ����� ID�Դϴ�." << endl;
//            return;
//        }
//    }
//    cout << "�� ����� �̸��� �Է��ϼ���: ";
//    cin >> name;
//    users.push_back(User(id, name));
//    saveUsers();
//    cout << "ȸ�������� �Ϸ�Ǿ����ϴ�." << endl;
//}
//
//int main() {
//    loadVideos();
//    loadUsers();
//
//    int userType;
//    cout << "1. ����� �α���\n2. ������ �α���\n3. ȸ������\n����: ";
//    cin >> userType;
//
//    if (userType == 1) {
//        int userId;
//        cout << "����� ID�� �Է��ϼ���: ";
//        cin >> userId;
//        for (auto& user : users) {
//            if (user.id == userId) {
//                userMenu(user);
//                saveVideos();
//                saveUsers();
//                return 0;
//            }
//        }
//        cout << "����ڸ� ã�� �� �����ϴ�." << endl;
//    }
//    else if (userType == 2) {
//        adminMenu();
//        saveVideos();
//        saveUsers();
//    }
//    else if (userType == 3) {
//        registerUser();
//    }
//    else {
//        cout << "�߸��� �����Դϴ�." << endl;
//    }
//
//    return 0;
//}
