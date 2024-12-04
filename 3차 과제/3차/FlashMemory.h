#ifndef FLASHMEMORY_H
#define FLASHMEMORY_H

#include <iostream>
#include <vector>
#include <string>
#include <fstream>

const int SECTOR_SIZE = 512; // ���� ũ�� (����Ʈ)
const int SPARE_SIZE = 16;   // ���� ���� ũ�� (����Ʈ)
const int BLOCK_SIZE = 32;   // ��ϴ� ���� ��
const int FLASH_SIZE = 3 * 1024 * 1024; // �÷��� �޸� ũ�� (����Ʈ)
const int TOTAL_BLOCKS = FLASH_SIZE / (SECTOR_SIZE * BLOCK_SIZE); // ��ü ��� ��
const int SPARE_BLOCKS = TOTAL_BLOCKS * 0.05; // ���� ��� �� (��ü ����� 5%)

class FlashMemory {
public:
    FlashMemory();
    void init();
    std::string Flash_read(int psn);
    std::string Flash_write(int psn, const std::string& data);
    std::string Flash_erase(int pbn);
    void print_memory_to_file(const std::string& filename);

private:
    std::vector<std::vector<char>> memory;
    std::vector<std::vector<char>> spareMemory; // ���� ����� ���� ���� �߰�
};

#endif