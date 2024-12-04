#ifndef FLASHMEMORY_H
#define FLASHMEMORY_H

#include <iostream>
#include <vector>
#include <string>
#include <fstream>

const int SECTOR_SIZE = 512; // 섹터 크기 (바이트)
const int SPARE_SIZE = 16;   // 여분 영역 크기 (바이트)
const int BLOCK_SIZE = 32;   // 블록당 섹터 수
const int FLASH_SIZE = 3 * 1024 * 1024; // 플래시 메모리 크기 (바이트)
const int TOTAL_BLOCKS = FLASH_SIZE / (SECTOR_SIZE * BLOCK_SIZE); // 전체 블록 수
const int SPARE_BLOCKS = TOTAL_BLOCKS * 0.05; // 여분 블록 수 (전체 블록의 5%)

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
    std::vector<std::vector<char>> spareMemory; // 여분 블록을 위한 벡터 추가
};

#endif