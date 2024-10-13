//#include <iostream>
//#include <fstream>
//#include <string>
//#include <vector>
//#include <ctime> // 현재 날짜를 가져오기 위해
//#include <tuple> // std::make_tuple을 사용하기 위해 <tuple> 헤더를 추가합니다.
//#include <algorithm>  // std::replace를 사용하기 위해 추가
//#include <sstream> // <sstream> 헤더를 추가하여 std::istringstream을 사용할 수 있도록 합니다.
//
//struct User {
//    std::string userId;
//    std::string password;
//    std::string name;
//    std::string birthDate;
//    std::string phoneNumber;
//    bool isAdmin; // 어드민 여부를 나타내는 필드 추가
//    int coins; // 사용자가 가지고 있는 코인 수
//};
//
//
//void signUp();
//void login();
//void clearScreen();
//std::vector<User> loadUsers();
//bool isUserIdUnique(const std::string& userId, const std::vector<User>& users);
//User* authenticateUser(const std::string& userId, const std::string& password, std::vector<User>& users);
//void adminMenu();
//void userMenu();
//void allVideo();
//void checkVideoRentalStatus();
//void returnVideo();
//void rentVideo();
//void checkRemainingDays();
//void addVideo();
//void addadmin();
//void delVideo();
//
//int main() {
//    int choice;
//
//    while (true) {
//        clearScreen();
//
//        std::cout << "메뉴를 선택하세요:" << std::endl;
//        std::cout << "1. 로그인" << std::endl;
//        std::cout << "2. 회원가입" << std::endl;
//        std::cout << "3. 종료" << std::endl;
//        std::cout << "선택: ";
//        std::cin >> choice;
//
//        switch (choice) {
//        case 1:
//            login();
//            break;
//        case 2:
//            signUp();
//            break;
//        case 3:
//            std::cout << "프로그램을 종료합니다." << std::endl;
//            return 0;
//        default:
//            std::cout << "잘못된 선택입니다." << std::endl;
//            break;
//        }
//        std::cout << "메뉴로 이동하려면 엔터 키를 누르세요...";
//        std::cin.ignore();
//        std::cin.get();
//    }
//
//    return 0;
//}
//
//std::vector<User> loadUsers() {
//    std::vector<User> users;
//    std::ifstream infile("users.txt");
//    std::string line;
//    while (std::getline(infile, line)) {
//        User user;
//        size_t pos = 0;
//        pos = line.find(',');
//        user.userId = line.substr(0, pos);
//        line.erase(0, pos + 1);
//
//        pos = line.find(',');
//        user.password = line.substr(0, pos);
//        line.erase(0, pos + 1);
//
//        pos = line.find(',');
//        user.name = line.substr(0, pos);
//        line.erase(0, pos + 1);
//
//        pos = line.find(',');
//        user.birthDate = line.substr(0, pos);
//        line.erase(0, pos + 1);
//
//        pos = line.find(',');
//        user.phoneNumber = line.substr(0, pos);
//        line.erase(0, pos + 1);
//
//        pos = line.find(',');
//        user.isAdmin = (line.substr(0, pos) == "1");
//        line.erase(0, pos + 1);
//
//        user.coins = std::stoi(line);
//
//        users.push_back(user);
//    }
//    return users;
//}
//
//
//bool isUserIdUnique(const std::string& userId, const std::vector<User>& users) {
//    for (const auto& user : users) {
//        if (user.userId == userId) {
//            return false;
//        }
//    }
//    return true;
//}
//
//User* authenticateUser(const std::string& userId, const std::string& password, std::vector<User>& users) {
//    for (auto& user : users) {
//        if (user.userId == userId && user.password == password) {
//            return &user;
//        }
//    }
//    return nullptr;
//}
//
//void signUp() {
//    std::string userId, password, name, birthDate, phoneNumber;
//    clearScreen();
//
//    std::vector<User> users = loadUsers();
//
//    std::cout << "회원가입을 시작합니다." << std::endl;
//    std::cout << "유저 ID: ";
//    std::cin >> userId;
//
//    if (!isUserIdUnique(userId, users)) {
//        std::cout << "이미 존재하는 유저 ID입니다. 다시 시도해주세요." << std::endl;
//        return;
//    }
//
//    std::cout << "비밀번호: ";
//    std::cin >> password;
//    std::cout << "이름: ";
//    std::cin >> name;
//    std::cout << "생년월일 (YYYY-MM-DD): ";
//    std::cin >> birthDate;
//    std::cout << "전화번호: ";
//    std::cin >> phoneNumber;
//
//    std::ofstream outfile("users.txt", std::ios_base::app);
//    outfile << userId << "," << password << "," << name << "," << birthDate << "," << phoneNumber << ",0,0" << std::endl;
//
//    std::cout << "회원가입이 완료되었습니다." << std::endl;
//}
//
//
//User* currentUser = nullptr;
//
//void login() {
//    std::string userId, password;
//    clearScreen();
//
//    std::vector<User> users = loadUsers();
//
//    std::cout << "로그인을 시작합니다." << std::endl;
//    std::cout << "유저 ID: ";
//    std::cin >> userId;
//    std::cout << "비밀번호: ";
//    std::cin >> password;
//
//    User* user = authenticateUser(userId, password, users);
//    if (user) {
//        std::cout << "로그인 성공!" << std::endl;
//        currentUser = user;
//        if (user->isAdmin) {
//            adminMenu();
//        }
//        else {
//            userMenu();
//        }
//    }
//    else {
//        std::cout << "로그인 실패. 유저 ID 또는 비밀번호가 잘못되었습니다." << std::endl;
//    }
//}
//
//void addCoinsToUser() {
//    std::string userId;
//    int coinsToAdd;
//    clearScreen();
//
//    std::vector<User> users = loadUsers();
//
//    std::cout << "코인을 추가할 유저 ID: ";
//    std::cin >> userId;
//
//    auto it = std::find_if(users.begin(), users.end(), [&userId](const User& user) {
//        return user.userId == userId;
//        });
//
//    if (it == users.end()) {
//        std::cout << "유저를 찾을 수 없습니다." << std::endl;
//        return;
//    }
//
//    std::cout << "추가할 코인 수: ";
//    std::cin >> coinsToAdd;
//
//    it->coins += coinsToAdd;
//
//    // 사용자 정보 업데이트
//    std::ofstream userFile("users.txt");
//    for (const auto& user : users) {
//        userFile << user.userId << "," << user.password << "," << user.name << "," << user.birthDate << "," << user.phoneNumber << "," << (user.isAdmin ? "1" : "0") << "," << user.coins << std::endl;
//    }
//
//    std::cout << "코인이 추가되었습니다." << std::endl;
//}
//
//void adminMenu() {
//    int choice;
//
//    while (true) {
//        clearScreen();
//
//        std::cout << "===== 관리자 메뉴 =====" << std::endl;
//        std::cout << "1. 비디오 추가" << std::endl;
//        std::cout << "2. 비디오 반납" << std::endl;
//        std::cout << "3. 유저에게 코인 추가" << std::endl;
//        std::cout << "4. 비디오 제거" << std::endl;
//        std::cout << "5. 대여 비디오 조회" << std::endl;
//        std::cout << "6. 로그아웃" << std::endl;
//        std::cout << "선택: ";
//        std::cin >> choice;
//
//        switch (choice) {
//        case 1:
//            addVideo();
//            break;
//        case 2:
//            returnVideo();
//            break;
//        case 3:
//            addCoinsToUser();
//            break;
//        case 4:
//            delVideo();
//            break;
//        case 5:
//            checkVideoRentalStatus();
//            break;
//        case 6:
//            return;
//        default:
//            std::cout << "잘못된 선택입니다." << std::endl;
//            break;
//        }
//        std::cout << "메뉴로 이동하려면 엔터 키를 누르세요...";
//        std::cin.ignore();
//        std::cin.get();
//    }
//}
//
//void userMenu() {
//    int choice;
//    while (true) {
//        clearScreen();
//        std::cout << "===== 사용자 메뉴 =====" << std::endl;
//        std::cout << "현재 소지 코인: " << currentUser->coins << std::endl; // 현재 소지 코인 수 출력
//        std::cout << "========================" << std::endl;
//
//        std::cout << "1. 전체 비디오 리스트" << std::endl;
//        std::cout << "2. 비디오 대여" << std::endl;
//        std::cout << "3. 대여 비디오 잔여일 확인" << std::endl;
//        std::cout << "4. 로그아웃" << std::endl;
//        std::cout << "선택: ";
//        std::cin >> choice;
//
//        switch (choice) {
//        case 1:
//            allVideo();
//            break;
//        case 2:
//            rentVideo();
//            break;
//        case 3:
//            checkRemainingDays();
//            break;
//        case 4:
//            return;
//        default:
//            std::cout << "잘못된 선택입니다." << std::endl;
//            break;
//        }
//        std::cout << "메뉴로 이동하려면 엔터 키를 누르세요...";
//        std::cin.ignore();
//        std::cin.get();
//    }
//}
//
//
//void allVideo() {
//    clearScreen();
//
//    std::ifstream videoFile("videos.txt");
//    std::ifstream rentalFile("rentals.txt");
//    std::string line;
//    std::vector<std::string> videoList;
//    std::vector<std::string> rentedVideos;
//
//    // 대여 중인 비디오 목록을 가져옵니다.
//    while (std::getline(rentalFile, line)) {
//        size_t pos1 = line.find(',');
//        size_t pos2 = line.find(',', pos1 + 1);
//        std::string videoId = line.substr(pos1 + 1, pos2 - pos1 - 1);
//        rentedVideos.push_back(videoId);
//    }
//
//    // 비디오 목록을 가져옵니다.
//    while (std::getline(videoFile, line)) {
//        videoList.push_back(line);
//    }
//
//    // 비디오 이름을 오름차순으로 정렬합니다.
//    std::sort(videoList.begin(), videoList.end());
//
//    std::cout << "전체 비디오 목록:" << std::endl;
//    for (const auto& video : videoList) {
//        std::string videoId = video.substr(0, video.find(". "));
//        bool isRented = std::find(rentedVideos.begin(), rentedVideos.end(), videoId) != rentedVideos.end();
//        std::cout << video << (isRented ? " (대여중)" : "") << std::endl;
//    }
//
//    videoFile.close();
//    rentalFile.close();
//}
//
//
//
//void checkVideoRentalStatus() {
//    clearScreen();
//
//    std::ifstream rentalFile("rentals.txt");
//    std::string line;
//    std::vector<std::tuple<std::string, std::string, std::string>> rentalList; // <UserId, VideoId, RentalDate>
//
//    while (std::getline(rentalFile, line)) {
//        size_t pos1 = line.find(',');
//        size_t pos2 = line.find(',', pos1 + 1);
//        std::string rentalUserId = line.substr(0, pos1);
//        std::string videoId = line.substr(pos1 + 1, pos2 - pos1 - 1);
//        std::string rentalDate = line.substr(pos2 + 1);
//
//        rentalList.push_back(std::make_tuple(rentalUserId, videoId, rentalDate));
//    }
//    rentalFile.close();
//
//    if (rentalList.empty()) {
//        std::cout << "현재 대여 중인 비디오가 없습니다." << std::endl;
//        return;
//    }
//
//    std::cout << "현재 대여 중인 비디오 목록:" << std::endl;
//    for (const auto& rental : rentalList) {
//        std::string rentalUserId = std::get<0>(rental);
//        std::string videoId = std::get<1>(rental);
//        std::string rentalDate = std::get<2>(rental);
//
//        // 비디오 이름 가져오기
//        std::ifstream videoFile("videos.txt");
//        std::string videoName;
//        while (std::getline(videoFile, line)) {
//            if (line.find(videoId + ". ") == 0) {
//                videoName = line.substr(line.find(". ") + 2);
//                break;
//            }
//        }
//        videoFile.close();
//
//        std::cout << "유저 ID: " << rentalUserId << ", 비디오 ID: " << videoId << ", 이름: " << videoName << ", 대여 날짜: " << rentalDate << std::endl;
//    }
//
//    std::cout << "메뉴로 돌아가려면 엔터 키를 누르세요...";
//    std::cin.ignore();
//    std::cin.get();
//}
//
//
//void returnVideo() {
//    std::string userId;
//    clearScreen();
//
//    std::vector<User> users = loadUsers();
//
//    std::cout << "비디오를 반납할 유저 ID: ";
//    std::cin >> userId;
//
//    auto it = std::find_if(users.begin(), users.end(), [&userId](const User& user) {
//        return user.userId == userId;
//        });
//
//    if (it == users.end()) {
//        std::cout << "유저를 찾을 수 없습니다." << std::endl;
//        return;
//    }
//
//    std::ifstream rentalFile("rentals.txt");
//    std::string line;
//    std::vector<std::tuple<std::string, std::string, std::string>> rentalList; // <UserId, VideoId, RentalDate>
//
//    while (std::getline(rentalFile, line)) {
//        size_t pos1 = line.find(',');
//        size_t pos2 = line.find(',', pos1 + 1);
//        std::string rentalUserId = line.substr(0, pos1);
//        std::string videoId = line.substr(pos1 + 1, pos2 - pos1 - 1);
//        std::string rentalDate = line.substr(pos2 + 1);
//
//        if (rentalUserId == userId) {
//            rentalList.push_back(std::make_tuple(rentalUserId, videoId, rentalDate));
//        }
//    }
//    rentalFile.close();
//
//    if (rentalList.empty()) {
//        std::cout << "현재 대여 중인 비디오가 없습니다." << std::endl;
//        return;
//    }
//
//    std::cout << "현재 대여 중인 비디오 목록:" << std::endl;
//    for (size_t i = 0; i < rentalList.size(); ++i) {
//        std::string videoId = std::get<1>(rentalList[i]);
//        std::string rentalDate = std::get<2>(rentalList[i]);
//
//        // 비디오 이름 가져오기
//        std::ifstream videoFile("videos.txt");
//        std::string videoName;
//        while (std::getline(videoFile, line)) {
//            if (line.find(videoId + ". ") == 0) {
//                videoName = line.substr(line.find(". ") + 2);
//                break;
//            }
//        }
//        videoFile.close();
//
//        std::cout << i + 1 << ". 비디오 ID: " << videoId << ", 이름: " << videoName << ", 대여 날짜: " << rentalDate << std::endl;
//    }
//
//    int choice;
//    std::cout << "반납할 비디오 번호를 선택하세요: ";
//    std::cin >> choice;
//
//    if (choice < 1 || choice > rentalList.size()) {
//        std::cout << "잘못된 선택입니다." << std::endl;
//        return;
//    }
//
//    std::string videoIdToReturn = std::get<1>(rentalList[choice - 1]);
//
//    // rentals.txt 파일에서 해당 비디오 대여 기록 제거
//    std::ifstream inFile("rentals.txt");
//    std::vector<std::string> lines;
//    while (std::getline(inFile, line)) {
//        if (line.find(userId + "," + videoIdToReturn + ",") != 0) {
//            lines.push_back(line);
//        }
//    }
//    inFile.close();
//
//    std::ofstream outFile("rentals.txt");
//    for (const auto& l : lines) {
//        outFile << l << std::endl;
//    }
//    outFile.close();
//
//    std::cout << "비디오가 반납되었습니다." << std::endl;
//}
//
//
//void checkRemainingDays() {
//    if (currentUser == nullptr) {
//        std::cout << "로그인이 필요합니다." << std::endl;
//        return;
//    }
//
//    std::ifstream rentalFile("rentals.txt");
//    std::string line;
//    std::vector<std::tuple<std::string, std::string, std::string>> rentalList; // <UserId, VideoId, RentalDate>
//
//    while (std::getline(rentalFile, line)) {
//        size_t pos1 = line.find(',');
//        size_t pos2 = line.find(',', pos1 + 1);
//        std::string userId = line.substr(0, pos1);
//        std::string videoId = line.substr(pos1 + 1, pos2 - pos1 - 1);
//        std::string rentalDate = line.substr(pos2 + 1);
//
//        if (userId == currentUser->userId) {
//            rentalList.push_back(std::make_tuple(userId, videoId, rentalDate));
//        }
//    }
//    rentalFile.close();
//
//    if (rentalList.empty()) {
//        std::cout << "현재 대여 중인 비디오가 없습니다." << std::endl;
//        return;
//    }
//
//    std::cout << "현재 대여 중인 비디오 목록:" << std::endl;
//    for (const auto& rental : rentalList) {
//        std::string videoId = std::get<1>(rental);
//        std::string rentalDate = std::get<2>(rental);
//
//        // 대여 날짜를 파싱
//        std::tm rentalTm = {};
//        std::string year, month, day;
//        std::replace(rentalDate.begin(), rentalDate.end(), '-', ' ');
//        std::istringstream ss(rentalDate);
//        ss >> year >> month >> day;
//        rentalTm.tm_year = std::stoi(year) - 1900;
//        rentalTm.tm_mon = std::stoi(month) - 1;
//        rentalTm.tm_mday = std::stoi(day);
//
//        // 현재 날짜를 가져오기
//        std::tm now;
//        std::time_t t = std::time(nullptr);
//        localtime_s(&now, &t);
//
//        // 남은 기한 계산
//        std::time_t rentalTime = std::mktime(&rentalTm);
//        std::time_t nowTime = std::mktime(&now);
//        double seconds = std::difftime(nowTime, rentalTime);
//        int days = static_cast<int>(seconds / (60 * 60 * 24));
//
//        // 비디오 이름 가져오기
//        std::ifstream videoFile("videos.txt");
//        std::string videoName;
//        while (std::getline(videoFile, line)) {
//            if (line.find(videoId + ". ") == 0) {
//                videoName = line.substr(line.find(". ") + 2);
//                break;
//            }
//        }
//        videoFile.close();
//
//        std::cout << "비디오 ID: " << videoId << ", 이름: " << videoName << ", 남은 기한: " << (7 - days) << "일" << std::endl;
//    }
//}
//
//
//
//void delVideo() {
//    std::string videoName;
//    clearScreen();
//
//    std::cout << "비디오 삭제를 시작합니다." << std::endl;
//    std::cout << "비디오 이름: ";
//    std::cin.ignore(); // 이전 입력의 개행 문자를 무시
//    std::getline(std::cin, videoName);
//
//    // 비디오 목록을 읽어옴
//    std::ifstream infile("videos.txt");
//    std::vector<std::string> videoList;
//    std::string line;
//    while (std::getline(infile, line)) {
//        videoList.push_back(line);
//    }
//    infile.close();
//
//    // 입력된 이름과 일치하는 비디오를 찾음
//    std::vector<int> indices;
//    for (size_t i = 0; i < videoList.size(); ++i) {
//        if (videoList[i].find(videoName) != std::string::npos) {
//            indices.push_back(i);
//        }
//    }
//
//    if (indices.empty()) {
//        std::cout << "해당 이름의 비디오를 찾을 수 없습니다." << std::endl;
//        return;
//    }
//
//    std::cout << "삭제할 비디오를 선택하세요" << std::endl;
//    std::cout << "------------------------------------" << std::endl;
//    for (size_t i = 0; i < indices.size(); ++i) {
//        std::cout << "------------------------------------" << std::endl;
//        std::cout << i + 1 << ". 비디오 id: " << indices[i] << ", 비디오 이름: " << videoList[indices[i]] << std::endl;
//    }
//
//    int choice;
//    std::cout << "선택: ";
//    std::cin >> choice;
//
//    if (choice < 1 || choice > indices.size()) {
//        std::cout << "잘못된 선택입니다. 삭제가 취소되었습니다." << std::endl;
//        return;
//    }
//
//    // 선택된 비디오를 삭제
//    videoList.erase(videoList.begin() + indices[choice - 1]);
//    std::cout << "삭제 완료." << std::endl;
//
//    // 변경된 비디오 목록을 파일에 저장
//    std::ofstream outfile("videos.txt");
//    for (const auto& video : videoList) {
//        outfile << video << std::endl;
//    }
//    outfile.close();
//}
//
//
//
//
//void rentVideo() {
//    if (currentUser == nullptr) {
//        std::cout << "로그인이 필요합니다." << std::endl;
//        return;
//    }
//
//    const int rentalCost = 1; // 비디오 대여 비용
//
//    if (currentUser->coins < rentalCost) {
//        std::cout << "코인이 부족합니다. 관리자에게 문의하세요." << std::endl;
//        return;
//    }
//
//    std::string videoName;
//    clearScreen();
//
//    std::cout << "비디오 대여를 시작합니다." << std::endl;
//    std::cout << "비디오 이름(일부 입력 가능): ";
//    std::cin.ignore(); // 이전 입력의 개행 문자를 무시
//    std::getline(std::cin, videoName);
//
//    // 비디오 ID를 찾기 위해 파일을 읽음
//    std::ifstream infile("videos.txt");
//    std::string line;
//    std::vector<std::pair<std::string, std::string>> videoList; // <ID, Name>
//    while (std::getline(infile, line)) {
//        size_t pos = line.find(". ");
//        if (pos != std::string::npos) {
//            std::string name = line.substr(pos + 2);
//            if (name.find(videoName) != std::string::npos) {
//                videoList.push_back({ line.substr(0, pos), name });
//            }
//        }
//    }
//    infile.close();
//
//    if (videoList.empty()) {
//        std::cout << "비디오를 찾을 수 없습니다." << std::endl;
//        return;
//    }
//
//    // 대여 가능한 비디오 ID를 찾기 위해 파일을 읽음
//    std::ifstream rentalFile("rentals.txt");
//    std::vector<std::string> rentedVideoIds;
//    while (std::getline(rentalFile, line)) {
//        size_t pos = line.find(',');
//        std::string rentedVideoId = line.substr(pos + 1, line.find(',', pos + 1) - pos - 1);
//        rentedVideoIds.push_back(rentedVideoId);
//    }
//    rentalFile.close();
//
//    std::cout << "검색된 비디오 목록:" << std::endl;
//    for (size_t i = 0; i < videoList.size(); ++i) {
//        std::string videoId = videoList[i].first;
//        std::string videoDisplayName = videoList[i].second;
//
//        if (std::count(rentedVideoIds.begin(), rentedVideoIds.end(), videoId) > 0) {
//            videoDisplayName += " (대여불가)";
//        }
//
//        std::cout << i + 1 << ". " << videoDisplayName << std::endl;
//    }
//
//    int choice;
//    std::cout << "대여할 비디오 번호를 선택하세요: ";
//    std::cin >> choice;
//
//    if (choice < 1 || choice > videoList.size()) {
//        std::cout << "잘못된 선택입니다." << std::endl;
//        return;
//    }
//
//    std::string selectedVideoId = videoList[choice - 1].first;
//
//    if (std::count(rentedVideoIds.begin(), rentedVideoIds.end(), selectedVideoId) > 0) {
//        std::cout << "선택한 비디오는 이미 대여 중입니다." << std::endl;
//        return;
//    }
//
//    // 현재 날짜를 가져오기
//    std::tm now;
//    std::time_t t = std::time(nullptr); // time_t 변수를 선언하고 현재 시간을 가져옴
//    localtime_s(&now, &t);
//    char dateStr[11];
//    std::strftime(dateStr, sizeof(dateStr), "%Y-%m-%d", &now);
//
//    // 대여 정보를 파일에 저장
//    std::ofstream outfile("rentals.txt", std::ios_base::app);
//    outfile << currentUser->userId << "," << selectedVideoId << "," << dateStr << std::endl;
//
//    // 코인 차감
//    currentUser->coins -= rentalCost;
//
//    // 사용자 정보 업데이트 (코인 정보만)
//    std::vector<User> users = loadUsers();
//    std::ofstream userFile("users.txt");
//    for (auto& user : users) {
//        if (user.userId == currentUser->userId) {
//            user.coins = currentUser->coins;
//        }
//        userFile << user.userId << "," << user.password << "," << user.name << "," << user.birthDate << "," << user.phoneNumber << "," << (user.isAdmin ? "1" : "0") << "," << user.coins << std::endl;
//    }
//
//    std::cout << "비디오 대여가 완료되었습니다." << std::endl;
//}
//
//
//void addVideo() { // 비디오 추가 기능
//    std::string videoName;
//    clearScreen();
//
//    std::cout << "비디오 추가를 시작합니다." << std::endl;
//    std::cout << "비디오 이름: ";
//    std::cin.ignore(); // 이전 입력의 개행 문자를 무시
//    std::getline(std::cin, videoName);
//
//    // 현재 비디오의 개수를 확인하여 순서를 결정
//    std::ifstream infile("videos.txt");
//    int videoCount = 0;
//    std::string line;
//    while (std::getline(infile, line)) {
//        videoCount++;
//    }
//    infile.close();
//
//    // 비디오 정보를 파일에 저장
//    std::ofstream outfile("videos.txt", std::ios_base::app);
//    outfile << videoCount + 1 << ". " << videoName << std::endl;
//
//    std::cout << "비디오 추가가 완료되었습니다." << std::endl;
//}
//
//void addadmin() {
//    // 어드민 추가 기능
//    std::string userId, password, name, birthDate, phoneNumber;
//    clearScreen();
//
//    std::vector<User> users = loadUsers();
//
//    std::cout << "어드민 추가를 시작합니다." << std::endl;
//    std::cout << "유저 ID: ";
//    std::cin >> userId;
//
//    if (!isUserIdUnique(userId, users)) {
//        std::cout << "이미 존재하는 유저 ID입니다. 다시 시도해주세요." << std::endl;
//        return;
//    }
//
//    std::cout << "비밀번호: ";
//    std::cin >> password;
//    std::cout << "이름: ";
//    std::cin >> name;
//    std::cout << "생년월일 (YYYY-MM-DD): ";
//    std::cin >> birthDate;
//    std::cout << "전화번호: ";
//    std::cin >> phoneNumber;
//
//    std::ofstream outfile("users.txt", std::ios_base::app);
//    outfile << userId << "," << password << "," << name << "," << birthDate << "," << phoneNumber << ",1" << std::endl;
//
//    std::cout << "어드민 추가가 완료되었습니다." << std::endl;
//}
//
//// 출력창 초기화
//void clearScreen() {
//    system("cls");  // 유닉스 OS의 경우 clear
//}
