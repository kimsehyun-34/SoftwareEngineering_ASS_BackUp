#include <iostream>
#include "user.h"
#include "admin.h"
#include "utils.h"

int main() {
    int choice;

    while (true) {
        clearScreen();

        std::cout << "�޴��� �����Ͻʽÿ�:" << std::endl;
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
        std::cout << "�޴��� �̵��Ϸ��� �ƹ� Ű�� �����ʽÿ�...";
        std::cin.ignore();
        std::cin.get();
    }

    return 0;
}