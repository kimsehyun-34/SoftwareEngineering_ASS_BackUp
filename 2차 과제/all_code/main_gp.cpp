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
//    cout << "대여할 비디오 ID를 입력하세요: ";
//    cin >> videoId;
//    for (auto& video : videos) {
//        if (video.id == videoId && !video.isRented) {
//            video.isRented = true;
//            user.rentedVideos.push_back(videoId);
//            cout << "비디오가 성공적으로 대여되었습니다." << endl;
//            return;
//        }
//    }
//    cout << "비디오를 대여할 수 없습니다." << endl;
//}
//
//void searchVideo() {
//    string title;
//    cout << "검색할 비디오 제목을 입력하세요: ";
//    cin >> title;
//    for (const auto& video : videos) {
//        if (video.title == title) {
//            cout << "비디오 ID: " << video.id << ", 제목: " << video.title << ", 대여 상태: " << (video.isRented ? "대여중" : "대여 가능") << endl;
//        }
//    }
//}
//
//void checkRentalDays(User& user) {
//    cout << "대여한 비디오 목록:" << endl;
//    for (const auto& videoId : user.rentedVideos) {
//        for (const auto& video : videos) {
//            if (video.id == videoId) {
//                cout << "비디오 ID: " << video.id << ", 제목: " << video.title << endl;
//            }
//        }
//    }
//}
//
//void returnVideo() {
//    int videoId;
//    cout << "반납할 비디오 ID를 입력하세요: ";
//    cin >> videoId;
//    for (auto& video : videos) {
//        if (video.id == videoId && video.isRented) {
//            video.isRented = false;
//            cout << "비디오가 성공적으로 반납되었습니다." << endl;
//            return;
//        }
//    }
//    cout << "비디오를 반납할 수 없습니다." << endl;
//}
//
//void userMenu(User& user) {
//    int choice;
//    do {
//        cout << "1. 비디오 대여\n2. 비디오 검색\n3. 대여 잔여일 확인\n4. 로그아웃\n선택: ";
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
//            cout << "잘못된 선택입니다." << endl;
//        }
//    } while (choice != 4);
//}
//
//void adminMenu() {
//    int choice;
//    do {
//        cout << "1. 대여 비디오 조회\n2. 비디오 반납\n3. 비디오 검색\n4. 로그아웃\n선택: ";
//        cin >> choice;
//        switch (choice) {
//        case 1:
//            for (const auto& video : videos) {
//                if (video.isRented) {
//                    cout << "비디오 ID: " << video.id << ", 제목: " << video.title << endl;
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
//            cout << "잘못된 선택입니다." << endl;
//        }
//    } while (choice != 4);
//}
//
//void registerUser() {
//    int id;
//    string name;
//    cout << "새 사용자 ID를 입력하세요: ";
//    cin >> id;
//    for (const auto& user : users) {
//        if (user.id == id) {
//            cout << "이미 존재하는 사용자 ID입니다." << endl;
//            return;
//        }
//    }
//    cout << "새 사용자 이름을 입력하세요: ";
//    cin >> name;
//    users.push_back(User(id, name));
//    saveUsers();
//    cout << "회원가입이 완료되었습니다." << endl;
//}
//
//int main() {
//    loadVideos();
//    loadUsers();
//
//    int userType;
//    cout << "1. 사용자 로그인\n2. 관리자 로그인\n3. 회원가입\n선택: ";
//    cin >> userType;
//
//    if (userType == 1) {
//        int userId;
//        cout << "사용자 ID를 입력하세요: ";
//        cin >> userId;
//        for (auto& user : users) {
//            if (user.id == userId) {
//                userMenu(user);
//                saveVideos();
//                saveUsers();
//                return 0;
//            }
//        }
//        cout << "사용자를 찾을 수 없습니다." << endl;
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
//        cout << "잘못된 선택입니다." << endl;
//    }
//
//    return 0;
//}
