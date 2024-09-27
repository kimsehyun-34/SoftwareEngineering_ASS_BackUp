#include "correction.h"
#include <iostream>
#include <regex>
#include "file_io.h"
#include "clear_screen.h"


void corr(std::vector<std::pair<std::string, std::string>>& phonebook)
{
    clearScreen();
    std::string name;
    std::cout << "������ ����ó�� �̸�: ";
    std::cin.ignore(); // ���� ����
    std::getline(std::cin, name);

    std::vector<int> indices;
    for (size_t i = 0; i < phonebook.size(); ++i) {
        if (phonebook[i].first == name) {
            indices.push_back(static_cast<int>(i)); // ������ �κ�
        }
    }

    if (indices.empty()) {
        std::cout << "����ó�� ã�� �� �����ϴ�." << std::endl;
        return;
    }

    std::cout << "==== �˻��� ����ó ====" << std::endl;
    for (size_t i = 0; i < indices.size(); ++i) {
        std::cout << i + 1 << ". �̸�: " << phonebook[indices[i]].first << ", ��ȭ��ȣ: " << phonebook[indices[i]].second << std::endl;
    }

    int contactChoice;
    std::cout << "������ ����ó�� ��ȣ�� �Է��ϼ���: ";
    std::cin >> contactChoice;

    if (contactChoice < 1 || contactChoice > static_cast<int>(indices.size())) {
        std::cout << "�߸��� �����Դϴ�. �ٽ� �õ��ϼ���." << std::endl;
        return;
    }

    int index = indices[contactChoice - 1];

    int choice;
    std::cout << "==== �����ϰ� ���� �׸��� ������ �ּ��� ====" << std::endl;
    std::cout << "1. �̸� ����" << std::endl;
    std::cout << "2. ��ȭ��ȣ ����" << std::endl;
    std::cout << "���ڸ� �Է��Ͽ� ����: ";
    std::cin >> choice;

    switch (choice) {
    case 1:
        modifyName(phonebook, index); // ������ �κ�
        break;
    case 2:
        modifyPhoneNumber(phonebook, index); // ������ �κ�
        break;
    default:
        std::cout << "�߸��� �����Դϴ�. �ٽ� �õ��ϼ���." << std::endl;
        break;
    }

    // ����ó ���� �� �ڵ����� TXT ���Ͽ� ����
    saveToTxt(phonebook);
}


// �̸��� �����ϴ� �Լ�
void modifyName(std::vector<std::pair<std::string, std::string>>& phonebook, int index) {
    std::string newName;
    std::cout << "�� �̸��� �Է��ϼ���: ";
    std::cin.ignore();
    std::getline(std::cin, newName);

    phonebook[index].first = newName;
    std::cout << "�̸��� �����Ǿ����ϴ�." << std::endl;
}

// ��ȭ��ȣ ����
void modifyPhoneNumber(std::vector<std::pair<std::string, std::string>>& phonebook, int index) {
    std::string newPhoneNumber;
    std::regex phoneRegex("^(010-[0-9]{4}-[0-9]{4}|02-[0-9]{3,4}-[0-9]{4}|[0-6]{3}-[0-9]{3,4}-[0-9]{4})$"); // ��ȭ��ȣ ���� ����ǥ����
    std::regex phoneRegexNoDash("^(010[0-9]{8}|02[0-9]{7,8}|[0-6]{3}[0-9]{7,8})$"); // ��ȭ��ȣ ���� ����ǥ����

    while (true) {
        std::cout << "�� ��ȭ��ȣ�� �Է��ϼ���: ";
        std::cin.ignore();
        std::getline(std::cin, newPhoneNumber);

        if (newPhoneNumber.empty()) {
            std::cout << "��ȭ��ȣ�� ��� �ֽ��ϴ�. �ٽ� �Է��� �ּ���." << std::endl;
        }
        else if (std::regex_match(newPhoneNumber, phoneRegexNoDash)) { // - �߰�
            if (newPhoneNumber.substr(0, 2) == "02" && newPhoneNumber.length() == 9) { // ����������ȣ 2�ڸ�-3�ڸ�-4�ڸ�
                newPhoneNumber = newPhoneNumber.substr(0, 2) + "-" + newPhoneNumber.substr(2, 3) + "-" + newPhoneNumber.substr(5, 4);
            }
            else if (newPhoneNumber.substr(0, 2) == "02" && newPhoneNumber.length() == 10) { // ����������ȣ 2�ڸ�-4�ڸ�-4�ڸ�
                newPhoneNumber = newPhoneNumber.substr(0, 2) + "-" + newPhoneNumber.substr(2, 4) + "-" + newPhoneNumber.substr(6, 4);
            }
            else if ((newPhoneNumber.substr(0, 3) == "031" || newPhoneNumber.substr(0, 3) == "032" || newPhoneNumber.substr(0, 3) == "042" ||
                newPhoneNumber.substr(0, 3) == "051" || newPhoneNumber.substr(0, 3) == "052" || newPhoneNumber.substr(0, 3) == "053" ||
                newPhoneNumber.substr(0, 3) == "062" || newPhoneNumber.substr(0, 3) == "064" || newPhoneNumber.substr(0, 3) == "033" ||
                newPhoneNumber.substr(0, 3) == "041" || newPhoneNumber.substr(0, 3) == "043" || newPhoneNumber.substr(0, 3) == "054" ||
                newPhoneNumber.substr(0, 3) == "055" || newPhoneNumber.substr(0, 3) == "061" || newPhoneNumber.substr(0, 3) == "063") &&
                newPhoneNumber.length() == 10) { // ������ȣ 3�ڸ�-3�ڸ�-4�ڸ�
                newPhoneNumber = newPhoneNumber.substr(0, 3) + "-" + newPhoneNumber.substr(3, 3) + "-" + newPhoneNumber.substr(6, 4);
            }
            else if ((newPhoneNumber.substr(0, 3) == "031" || newPhoneNumber.substr(0, 3) == "032" || newPhoneNumber.substr(0, 3) == "042" ||
                newPhoneNumber.substr(0, 3) == "051" || newPhoneNumber.substr(0, 3) == "052" || newPhoneNumber.substr(0, 3) == "053" ||
                newPhoneNumber.substr(0, 3) == "062" || newPhoneNumber.substr(0, 3) == "064" || newPhoneNumber.substr(0, 3) == "033" ||
                newPhoneNumber.substr(0, 3) == "041" || newPhoneNumber.substr(0, 3) == "043" || newPhoneNumber.substr(0, 3) == "054" ||
                newPhoneNumber.substr(0, 3) == "055" || newPhoneNumber.substr(0, 3) == "061" || newPhoneNumber.substr(0, 3) == "063") &&
                newPhoneNumber.length() == 11) { // ������ȣ 3�ڸ�-4�ڸ�-4�ڸ�
                newPhoneNumber = newPhoneNumber.substr(0, 3) + "-" + newPhoneNumber.substr(3, 4) + "-" + newPhoneNumber.substr(7, 4);
            }
            else if (newPhoneNumber.substr(0, 3) == "010" && newPhoneNumber.length() == 11) {
                newPhoneNumber = newPhoneNumber.substr(0, 3) + "-" + newPhoneNumber.substr(3, 4) + "-" + newPhoneNumber.substr(7, 4); // �޴�����ȣ 010-4�ڸ�-4�ڸ�
            }
            else {
                std::cout << "�߸��� ��ȭ��ȣ �����Դϴ�. �ٽ� �Է��� �ּ���." << std::endl;
                continue;
            }
            break;
        }
        else if (std::regex_match(newPhoneNumber, phoneRegex)) {// - �ִ°�� �н�
            break;
        }
        else {
            std::cout << "�߸��� ��ȭ��ȣ �����Դϴ�. ��ȭ��ȣ�� 010-xxxx-xxxx �Ǵ� 010xxxxxxxx �̰ų� ������ȭ�� ��� (������ȣ)-(x)xxx-xxxx, (������ȣ)(x)xxxxxxx �����̾�� �մϴ�." << std::endl;
        }
    }

    phonebook[index].second = newPhoneNumber;
    std::cout << "��ȭ��ȣ�� �����Ǿ����ϴ�." << std::endl;
}
