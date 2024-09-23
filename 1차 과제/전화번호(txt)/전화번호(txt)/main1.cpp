//#include <iostream>
//#include <cstdlib> // system() 함수 에 사용
//#include <string>
//#include <vector>
//#include <fstream>
//#include <regex> // regex 사용을 위해 추가
//
//void addition();
//void search();
//void corr();
//void del();
//void clearScreen();
//void saveToTxt();
//void loadFromTxt();
//void displayAllContacts();
//void searchInTxt(const std::string& name);
//void modifyName(const std::string& oldName);
//void modifyPhoneNumber(const std::string& name);
//
//std::vector<std::pair<std::string, std::string>> phonebook;
//
//// main 함수
//int main()
//{
//    loadFromTxt(); // 프로그램 시작 시 TXT 파일에서 데이터 로드
//
//    int choice;
//
//    while (true) {
//        clearScreen();
//
//        std::cout << "========메뉴 선택=======" << std::endl;
//        std::cout << "1. 연락처 추가" << std::endl;
//        std::cout << "2. 연락처 검색" << std::endl;
//        std::cout << "3. 연락처 수정" << std::endl;
//        std::cout << "4. 연락처 삭제" << std::endl;
//        std::cout << "5. 연락처 전체 출력" << std::endl;
//        std::cout << "6. 프로그램 종료" << std::endl;
//        std::cout << "====================" << std::endl;
//        std::cout << "숫자를 입력하여 선택: ";
//
//        // 입력
//        std::cin >> choice;
//
//        if (std::cin.fail()) {
//            std::cin.clear(); // 입력 스트림 상태 플래그 초기화
//            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // 잘못된 입력 무시
//            continue;
//        }
//
//        switch (choice) {
//        case 1:
//            addition();
//            break;
//        case 2:
//            search();
//            break;
//        case 3:
//            corr();
//            break;
//        case 4:
//            del();
//            break;
//        case 5:
//            displayAllContacts();
//            break;
//        case 6:
//            saveToTxt(); // 프로그램 종료 시 TXT 파일에 데이터 저장
//            std::cout << "프로그램을 종료합니다." << std::endl;
//            return 0; // 종료
//        default:
//            std::cout << "잘못된 선택입니다. 다시 시도하세요." << std::endl;
//            break;
//        }
//
//        std::cout << "메뉴로 이동하려면 엔터 키를 누르세요...";
//        std::cin.ignore();
//        std::cin.get();
//    }
//
//    return 0;
//}
//
//// 추가
//void addition()
//{
//    std::string name, phoneNumber;
//    std::regex phoneRegex("^[0-9]+$"); // 전화번호는 숫자만 허용
//
//    // 이름 입력
//    while (true) {
//        clearScreen();
//
//        std::cout << "이름: ";
//        std::cin.ignore(); // 버퍼 비우기
//        std::getline(std::cin, name);
//
//        if (name.empty()) {
//            std::cout << "이름이 비어 있습니다. 다시 입력해 주세요." << std::endl;
//        }
//        else {
//            break;
//        }
//    }
//
//    // 전화번호 입력
//    while (true)
//    {
//        std::cout << "전화번호: ";
//        std::getline(std::cin, phoneNumber);
//
//        if (phoneNumber.empty()) {
//            std::cout << "전화번호가 비어 있습니다. 다시 입력해 주세요." << std::endl;
//        }
//        else if (!std::regex_match(phoneNumber, phoneRegex)) {
//            std::cout << "잘못된 전화번호 형식입니다. 전화번호는 숫자만 포함해야 합니다." << std::endl;
//        }
//        else {
//            break;
//        }
//    }
//
//    // 리스트에 연락처 저장
//    phonebook.push_back(std::make_pair(name, phoneNumber));
//    std::cout << "저장완료!" << std::endl;
//
//    // 연락처 추가 후 자동으로 TXT 파일에 저장
//    saveToTxt();
//}
//
//// 검색
//void search()
//{
//    std::string name;
//    std::cout << "검색할 이름: ";
//    std::cin.ignore(); // 버퍼 비우기
//    std::getline(std::cin, name);
//
//    searchInTxt(name);
//}
//
//// TXT 파일에서 이름 검색
//void searchInTxt(const std::string& name)
//{
//    std::ifstream file("phonebook.txt");
//    if (file.is_open()) {
//        std::string line;
//        bool found = false;
//        while (std::getline(file, line)) {
//            if (line.find(name) != std::string::npos) {
//                size_t namePos = line.find("\"name\": \"") + 9;
//                size_t nameEnd = line.find("\"", namePos);
//                std::string foundName = line.substr(namePos, nameEnd - namePos);
//
//                size_t phonePos = line.find("\"phoneNumber\": \"") + 16;
//                size_t phoneEnd = line.find("\"", phonePos);
//                std::string foundPhoneNumber = line.substr(phonePos, phoneEnd - phonePos);
//
//                std::cout << "이름: " << foundName << " , 전화번호: " << foundPhoneNumber << std::endl;
//                found = true;
//            }
//        }
//        if (!found) {
//            std::cout << "연락처를 찾을수 없습니다." << std::endl;
//        }
//    }
//}
//
//
//// 수정
//void corr()
//{
//    std::string name;
//    std::cout << "수정할 연락처의 이름: ";
//    std::cin.ignore(); // 버퍼 비우기
//    std::getline(std::cin, name);
//
//    bool found = false;
//    for (const auto& contact : phonebook) {
//        if (contact.first == name) {
//            found = true;
//            break;
//        }
//    }
//
//    if (!found) {
//        std::cout << "연락처를 찾을수 없습니다" << std::endl;
//        return;
//    }
//
//    int choice;
//    std::cout << "==== 수정하고 싶은 항목을 선택해 주세요 ====" << std::endl;
//    std::cout << "1. 이름 수정" << std::endl;
//    std::cout << "2. 전화번호 수정" << std::endl;
//    std::cout << "숫자를 입력하여 선택: ";
//    std::cin >> choice;
//
//    switch (choice) {
//    case 1:
//        modifyName(name);
//        break;
//    case 2:
//        modifyPhoneNumber(name);
//        break;
//    default:
//        std::cout << "잘못된 선택입니다. 다시 시도하세요." << std::endl;
//        break;
//    }
//
//    // 연락처 수정 후 자동으로 TXT 파일에 저장
//    saveToTxt();
//}
//
//// 이름 수정
//void modifyName(const std::string& oldName)
//{
//    std::string newName;
//
//    while (true) {
//        std::cout << "수정할 이름: ";
//        std::cin.ignore(); // 버퍼 비우기
//        std::getline(std::cin, newName);
//
//        if (newName.empty()) {
//            std::cout << "이름이 비어 있습니다. 다시 입력해 주세요." << std::endl;
//        }
//        else {
//            break;
//        }
//    }
//
//    for (auto& contact : phonebook) {
//        if (contact.first == oldName) {
//            contact.first = newName;
//            std::cout << "이름 수정 성공" << std::endl;
//            break;
//        }
//    }
//}
//
//
//
//// 전화번호 수정
//void modifyPhoneNumber(const std::string& name)
//{
//    std::string newPhoneNumber;
//    std::regex phoneRegex("^[0-9]+$"); // 전화번호는 숫자만 허용
//
//    while (true) {
//        std::cout << "수정할 전화번호: ";
//        std::cin.ignore(); // 버퍼 비우기
//        std::getline(std::cin, newPhoneNumber);
//
//        if (newPhoneNumber.empty()) {
//            std::cout << "전화번호가 비어 있습니다. 다시 입력해 주세요." << std::endl;
//        }
//        else if (!std::regex_match(newPhoneNumber, phoneRegex)) {
//            std::cout << "잘못된 전화번호 형식입니다. 전화번호는 숫자만 포함해야 합니다." << std::endl;
//        }
//        else {
//            break;
//        }
//    }
//
//    for (auto& contact : phonebook) {
//        if (contact.first == name) {
//            contact.second = newPhoneNumber;
//            std::cout << "전화번호 수정 성공" << std::endl;
//            break;
//        }
//    }
//}
//
//
//
//// 삭제
//void del()
//{
//    std::string name;
//    std::cout << "삭제할 연락처의 이름: ";
//    std::cin.ignore(); // 버퍼 비우기
//    std::getline(std::cin, name);
//
//    auto it = std::remove_if(phonebook.begin(), phonebook.end(), [&](const std::pair<std::string, std::string>& contact) {
//        return contact.first == name;
//        });
//
//    if (it != phonebook.end()) {
//        phonebook.erase(it, phonebook.end());
//        std::cout << "삭제 완료." << std::endl;
//        // 연락처 삭제 후 자동으로 TXT 파일에 저장
//        saveToTxt();
//    }
//    else {
//        std::cout << "연락처를 찾을수 없습니다." << std::endl;
//    }
//}
//
//// 연락처 전체 출력 함수
//void displayAllContacts()
//{
//    if (phonebook.empty()) {
//        std::cout << "저장된 정보가 없습니다." << std::endl;
//        return;
//    }
//
//    for (const auto& contact : phonebook) {
//        std::cout << "이름: " << contact.first << " , 전화번호: " << contact.second << std::endl;
//    }
//}
//
//// 출력창 초기화
//void clearScreen()
//{
//    system("cls");  // 유닉스 OS의 경우 clear
//}
//
//// TXT 파일에 데이터 저장
//void saveToTxt()
//{
//    std::ofstream file("phonebook.txt");
//    file << "[\n";
//    for (size_t i = 0; i < phonebook.size(); ++i) {
//        file << "  {\"name\": \"" << phonebook[i].first << "\", \"phoneNumber\": \"" << phonebook[i].second << "\"}";
//        if (i != phonebook.size() - 1) {
//            file << ",";
//        }
//        file << "\n";
//    }
//    file << "]";
//}
//
//// TXT 파일에서 데이터 로드
//void loadFromTxt()
//{
//    std::ifstream file("phonebook.txt");
//    if (file.is_open()) {
//        std::string line;
//        while (std::getline(file, line)) {
//            if (line.find("{") != std::string::npos) {
//                std::string name, phoneNumber;
//                size_t namePos = line.find("\"name\": \"") + 9;
//                size_t nameEnd = line.find("\"", namePos);
//                name = line.substr(namePos, nameEnd - namePos);
//
//                size_t phonePos = line.find("\"phoneNumber\": \"") + 16;
//                size_t phoneEnd = line.find("\"", phonePos);
//                phoneNumber = line.substr(phonePos, phoneEnd - phonePos);
//
//                phonebook.push_back(std::make_pair(name, phoneNumber));
//            }
//        }
//    }
//}