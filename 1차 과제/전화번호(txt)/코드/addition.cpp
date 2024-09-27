#include "addition.h"
#include <iostream>
#include <regex>
#include "file_io.h"
#include "clear_screen.h"

void addition(std::vector<std::pair<std::string, std::string>>& phonebook)
{
    std::string name, phoneNumber;
    std::regex phoneRegex("^(010-[0-9]{4}-[0-9]{4}|02-[0-9]{3,4}-[0-9]{4}|[0-6]{3}-[0-9]{3,4}-[0-9]{4})$");
    std::regex phoneRegexNoDash("^(010[0-9]{8}|02[0-9]{7,8}|[0-6]{3}[0-9]{7,8})$");

    while (true) {
        clearScreen();

        std::cout << "�̸�: ";
        std::cin.ignore();
        std::getline(std::cin, name);

        if (name.empty()) {
            std::cout << "�̸��� ��� �ֽ��ϴ�. �ٽ� �Է��ϼ���." << std::endl;
        }
        else {
            break;
        }
    }

    while (true)
    {
        std::cout << "��ȭ��ȣ(�ؿܹ�ȣ�� ��� '-'�� �Բ� �Է�): ";
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
        else if (std::regex_match(phoneNumber, phoneRegex)) {// - �ִ°�� �н�
            break;
        }
        else {
            std::cout << "�߸��� ��ȭ��ȣ �����Դϴ�. ��ȭ��ȣ�� 010-xxxx-xxxx �Ǵ� 010xxxxxxxx �̰ų� ������ȭ�� ��� (������ȣ)-(x)xxx-xxxx, (������ȣ)(x)xxxxxxx �����̾�� �մϴ�." << std::endl;
        }
    }

    for (const auto& contact : phonebook) {
        if (contact.second == phoneNumber) {
            std::cout << "�ߺ��� ��ȭ��ȣ�� �̹� �����մϴ�." << std::endl;
            return;
        }
    }

    phonebook.push_back(std::make_pair(name, phoneNumber));
    std::cout << "�߰� �Ϸ�!" << std::endl;

    saveToTxt(phonebook);
}
