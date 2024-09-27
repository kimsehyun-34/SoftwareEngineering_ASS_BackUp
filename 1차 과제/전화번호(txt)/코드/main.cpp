#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include "addition.h"
#include "search.h"
#include "correction.h"
#include "delete.h"
#include "file_io.h"
#include "display.h"
#include "clear_screen.h"

std::vector<std::pair<std::string, std::string>> phonebook;

int main()
{
    loadFromTxt(phonebook);

    int choice;

    while (true) {
        clearScreen();

        std::cout << "========�޴� ����=======" << std::endl;
        std::cout << "1. ����ó �߰�" << std::endl;
        std::cout << "2. ����ó �˻�" << std::endl;
        std::cout << "3. ����ó ����" << std::endl;
        std::cout << "4. ����ó ����" << std::endl;
        std::cout << "5. ����ó ��ü ����" << std::endl;
        std::cout << "6. ���α׷� ����" << std::endl;
        std::cout << "====================" << std::endl;
        std::cout << "��ȣ�� �Է��ϼ���: ";

        std::cin >> choice;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        switch (choice) {
        case 1:
            addition(phonebook);
            break;
        case 2:
            search(phonebook);
            break;
        case 3:
            corr(phonebook);
            break;
        case 4:
            del(phonebook);
            break;
        case 5:
            displayAllContacts(phonebook);
            break;
        case 6:
            saveToTxt(phonebook);
            std::cout << "���α׷��� �����մϴ�." << std::endl;
            return 0;
        default:
            std::cout << "�߸��� �����Դϴ�. �ٽ� �õ��ϼ���." << std::endl;
            break;
        }

        std::cout << "�޴��� �̵��Ϸ��� �ƹ� Ű�� ��������...";
        std::cin.ignore();
        std::cin.get();
    }

    return 0;
}