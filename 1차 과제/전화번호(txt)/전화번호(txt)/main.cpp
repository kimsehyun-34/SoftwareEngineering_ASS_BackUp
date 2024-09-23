#include <iostream>
#include <cstdlib> // system() �Լ� �� ���
#include <string>
#include <vector>
#include <fstream>
#include <regex> // regex ����� ���� �߰�

void addition();
void search();
void corr();
void del();
void clearScreen();
void saveToTxt();
void loadFromTxt();
void displayAllContacts();
void searchInTxt(const std::string& name);
void modifyName(const std::string& oldName);
void modifyPhoneNumber(const std::string& name);

std::vector<std::pair<std::string, std::string>> phonebook;

// main �Լ�
int main()
{
    loadFromTxt(); // ���α׷� ���� �� TXT ���Ͽ��� ������ �ε�

    int choice;

    while (true) {
        clearScreen();

        std::cout << "========�޴� ����=======" << std::endl;
        std::cout << "1. ����ó �߰�" << std::endl;
        std::cout << "2. ����ó �˻�" << std::endl;
        std::cout << "3. ����ó ����" << std::endl;
        std::cout << "4. ����ó ����" << std::endl;
        std::cout << "5. ����ó ��ü ���" << std::endl;
        std::cout << "6. ���α׷� ����" << std::endl;
        std::cout << "====================" << std::endl;
        std::cout << "���ڸ� �Է��Ͽ� ����: ";

        // �Է�
        std::cin >> choice;

        if (std::cin.fail()) {
            std::cin.clear(); // �ʱ�ȭ
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // �߸��� �Է� ����
            continue;
        }

        switch (choice) {
        case 1:
            addition();
            break;
        case 2:
            search();
            break;
        case 3:
            corr();
            break;
        case 4:
            del();
            break;
        case 5:
            displayAllContacts();
            break;
        case 6:
            saveToTxt(); // ���α׷� ���� �� TXT ���Ͽ� ������ ����
            std::cout << "���α׷��� �����մϴ�." << std::endl;
            return 0; // ����
        default:
            std::cout << "�߸��� �����Դϴ�. �ٽ� �õ��ϼ���." << std::endl;
            break;
        }

        std::cout << "�޴��� �̵��Ϸ��� ���� Ű�� ��������...";
        std::cin.ignore();
        std::cin.get();
    }

    return 0;
}

// �߰�
void addition()
{
    std::string name, phoneNumber;
    std::regex phoneRegex("^(010-[0-9]{4}-[0-9]{4}|02-[0-9]{3,4}-[0-9]{4}|[0-6]{3}-[0-9]{3,4}-[0~9]{4})$"); // ��ȭ��ȣ�� 010-1234-1234, 02-0000-0000, 02-000-0000 ���� ��� ����ǥ����
    std::regex phoneRegexNoDash("^(010[0-9]{8}|02[0-9]{7,8}|[0-6]{3}[0-9]{7,8})$"); // ��ȭ��ȣ�� 01012341234, 0200000000, 020000000 ���� ���

    // �̸� �Է�
    while (true) {
        clearScreen();

        std::cout << "�̸�: ";
        std::cin.ignore(); // ���� ����
        std::getline(std::cin, name);

        if (name.empty()) {
            std::cout << "�̸��� ��� �ֽ��ϴ�. �ٽ� �Է��� �ּ���." << std::endl;
        }
        else {
            break;
        }
    }

    // ��ȭ��ȣ �Է�
    while (true)
    {
        std::cout << "��ȭ��ȣ: ";
        std::getline(std::cin, phoneNumber);

        if (phoneNumber.empty()) {
            std::cout << "��ȭ��ȣ�� ��� �ֽ��ϴ�. �ٽ� �Է��� �ּ���." << std::endl;
        }
        else if (std::regex_match(phoneNumber, phoneRegexNoDash)) { // - �߰�
            if (phoneNumber.substr(0, 2) == "02" && phoneNumber.length() == 9) {
                phoneNumber = phoneNumber.substr(0, 2) + "-" + phoneNumber.substr(2, 3) + "-" + phoneNumber.substr(5, 4);
            }
            else if (phoneNumber.substr(0, 2) == "02" && phoneNumber.length() == 10) {
                phoneNumber = phoneNumber.substr(0, 2) + "-" + phoneNumber.substr(2, 4) + "-" + phoneNumber.substr(6, 4);
            }
            else if (phoneNumber.substr(0, 3) == "031" || "032" || "042" || "051" || "052" || "053" || "062" || "064" || " 033" || "041" || "043" || "054" || "055" || "061" || "063" && phoneNumber.length() == 10) {
                phoneNumber = phoneNumber.substr(0, 3) + "-" + phoneNumber.substr(3, 3) + "-" + phoneNumber.substr(6, 4);
            }
            else if (phoneNumber.substr(0, 3) == "031" || "032" || "042" || "051" || "052" || "053" || "062" || "064" || "033" || "041" || "043" || "054" || "055" || "061" || "063" && phoneNumber.length() == 11) {
                phoneNumber = phoneNumber.substr(0, 3) + "-" + phoneNumber.substr(3, 4) + "-" + phoneNumber.substr(7, 4);
            }
            else {
                phoneNumber = phoneNumber.substr(0, 3) + "-" + phoneNumber.substr(3, 4) + "-" + phoneNumber.substr(7, 4);
            }
            break;
        }
        else if (std::regex_match(phoneNumber, phoneRegex)) {// - �ִ°�� �н�
            break;
        }
        else {
            std::cout << "�߸��� ��ȭ��ȣ �����Դϴ�. ��ȭ��ȣ�� 010-xxxx-xxxx �Ǵ� 010xxxxxxxx �̰ų� ������ȭ�� ��� 02-(x)xxx-xxxx, 02(x)xxxxxxx �����̾�� �մϴ�." << std::endl;
        }
    }

    // �ߺ� Ȯ��
    for (const auto& contact : phonebook) {
        if (contact.second == phoneNumber) {
            std::cout << "�ߺ��Ǵ� ����ó�� �̹� ����Ǿ� �ֽ��ϴ�." << std::endl;
            return;
        }
    }

    // ����Ʈ�� ����ó ����
    phonebook.push_back(std::make_pair(name, phoneNumber));
    std::cout << "����Ϸ�!" << std::endl;

    // ����ó �߰� �� �ڵ����� TXT ���Ͽ� ����
    saveToTxt();
}


// �˻�
void search()
{
    std::string name;
    std::cout << "�˻��� �̸�: ";
    std::cin.ignore();
    std::getline(std::cin, name);

    searchInTxt(name);
}

// TXT ���Ͽ��� �̸� �˻�
void searchInTxt(const std::string& name)
{
    std::ifstream file("phonebook.txt");
    if (file.is_open()) {
        std::string line;
        bool found = false;
        while (std::getline(file, line)) {
            if (line.find(name) != std::string::npos) {
                size_t namePos = line.find("\"name\": \"") + 9;
                size_t nameEnd = line.find("\"", namePos);
                std::string foundName = line.substr(namePos, nameEnd - namePos);

                size_t phonePos = line.find("\"phoneNumber\": \"") + 16;
                size_t phoneEnd = line.find("\"", phonePos);
                std::string foundPhoneNumber = line.substr(phonePos, phoneEnd - phonePos);

                std::cout << "�̸�: " << foundName << " , ��ȭ��ȣ: " << foundPhoneNumber << std::endl;
                found = true;
            }
        }
        if (!found) {
            std::cout << "����ó�� ã���� �����ϴ�." << std::endl;
        }
    }
}

// ����
void corr()
{
    std::string name;
    std::cout << "������ ����ó�� �̸�: ";
    std::cin.ignore(); // ���� ����
    std::getline(std::cin, name);

    bool found = false;
    for (const auto& contact : phonebook) {
        if (contact.first == name) {
            found = true;
            break;
        }
    }

    if (!found) {
        std::cout << "����ó�� ã���� �����ϴ�" << std::endl;
        return;
    }

    int choice;
    std::cout << "==== �����ϰ� ���� �׸��� ������ �ּ��� ====" << std::endl;
    std::cout << "1. �̸� ����" << std::endl;
    std::cout << "2. ��ȭ��ȣ ����" << std::endl;
    std::cout << "���ڸ� �Է��Ͽ� ����: ";
    std::cin >> choice;

    switch (choice) {
    case 1:
        modifyName(name);
        break;
    case 2:
        modifyPhoneNumber(name);
        break;
    default:
        std::cout << "�߸��� �����Դϴ�. �ٽ� �õ��ϼ���." << std::endl;
        break;
    }

    // ����ó ���� �� �ڵ����� TXT ���Ͽ� ����
    saveToTxt();
}

// �̸� ����
void modifyName(const std::string& oldName)
{
    std::string newName;

    while (true) {
        std::cout << "������ �̸�: ";
        std::cin.ignore(); // ���� ����
        std::getline(std::cin, newName);

        if (newName.empty()) {
            std::cout << "�̸��� ��� �ֽ��ϴ�. �ٽ� �Է��� �ּ���." << std::endl;
        }
        else {
            break;
        }
    }

    for (auto& contact : phonebook) {
        if (contact.first == oldName) {
            contact.first = newName;
            std::cout << "�̸� ���� ����" << std::endl;
            break;
        }
    }
}

// ��ȭ��ȣ ����
void modifyPhoneNumber(const std::string& name)
{
    std::string newPhoneNumber;
    std::regex phoneRegex("^[0-9]+$"); // ��ȭ��ȣ�� ���ڸ� ���

    while (true) {
        std::cout << "������ ��ȭ��ȣ: ";
        std::cin.ignore(); // ���� ����
        std::getline(std::cin, newPhoneNumber);

        if (newPhoneNumber.empty()) {
            std::cout << "��ȭ��ȣ�� ��� �ֽ��ϴ�. �ٽ� �Է��� �ּ���." << std::endl;
        }
        else if (!std::regex_match(newPhoneNumber, phoneRegex)) {
            std::cout << "�߸��� ��ȭ��ȣ �����Դϴ�. ��ȭ��ȣ�� ���ڸ� �����ؾ� �մϴ�." << std::endl;
        }
        else {
            break;
        }
    }

    for (auto& contact : phonebook) {
        if (contact.first == name) {
            contact.second = newPhoneNumber;
            std::cout << "��ȭ��ȣ ���� ����" << std::endl;
            break;
        }
    }
}

// ����
void del()
{
    std::string name;
    std::cout << "������ ����ó�� �̸�: ";
    std::cin.ignore(); // ���� ����
    std::getline(std::cin, name);

    auto it = std::remove_if(phonebook.begin(), phonebook.end(), [&](const std::pair<std::string, std::string>& contact) {
        return contact.first == name;
        });

    if (it != phonebook.end()) {
        phonebook.erase(it, phonebook.end());
        std::cout << "���� �Ϸ�." << std::endl;
        // ����ó ���� �� �ڵ����� TXT ���Ͽ� ����
        saveToTxt();
    }
    else {
        std::cout << "����ó�� ã���� �����ϴ�." << std::endl;
    }
}

// ����ó ��ü ��� �Լ�
void displayAllContacts()
{
    if (phonebook.empty()) {
        std::cout << "����� ������ �����ϴ�." << std::endl;
        return;
    }
    std::cout << "-------------------------" << std::endl;
    for (const auto& contact : phonebook) {
        std::cout << "�̸�: " << contact.first << " , ��ȭ��ȣ: " << contact.second << std::endl;
        std::cout << "-------------------------" << std::endl;
    }
}

// ���â �ʱ�ȭ
void clearScreen()
{
    system("cls");  // ���н� OS�� ��� clear
}

// TXT ���Ͽ� ������ ����
void saveToTxt()
{
    std::ofstream file("phonebook.txt");
    file << "[\n";
    for (size_t i = 0; i < phonebook.size(); ++i) {
        file << "  {\"name\": \"" << phonebook[i].first << "\", \"phoneNumber\": \"" << phonebook[i].second << "\"}";
        if (i != phonebook.size() - 1) {
            file << ",";
        }
        file << "\n";
    }
    file << "]";
}

// TXT ���Ͽ��� ������ �ε�
void loadFromTxt()
{
    std::ifstream file("phonebook.txt");
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            if (line.find("{") != std::string::npos) {
                std::string name, phoneNumber;
                size_t namePos = line.find("\"name\": \"") + 9;
                size_t nameEnd = line.find("\"", namePos);
                name = line.substr(namePos, nameEnd - namePos);

                size_t phonePos = line.find("\"phoneNumber\": \"") + 16;
                size_t phoneEnd = line.find("\"", phonePos);
                phoneNumber = line.substr(phonePos, phoneEnd - phonePos);

                phonebook.push_back(std::make_pair(name, phoneNumber));
            }
        }
    }
}