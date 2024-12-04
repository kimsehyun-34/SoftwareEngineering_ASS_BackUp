#include "FlashMemory.h"

FlashMemory::FlashMemory() {
    init();
}

void FlashMemory::init() {
    int totalSectors = FLASH_SIZE / SECTOR_SIZE;
    int totalSpareSectors = SPARE_BLOCKS * BLOCK_SIZE;
    memory.resize(totalSectors, std::vector<char>(SECTOR_SIZE + SPARE_SIZE, 0));
    spareMemory.resize(totalSpareSectors, std::vector<char>(SECTOR_SIZE + SPARE_SIZE, 0));
    std::cout << "플래시 메모리 초기화 완료" << std::endl;
}

std::string FlashMemory::Flash_read(int psn) {
    if (psn < 0 || psn >= memory.size()) {
        return "Error: 읽기 연산 불가";
    }
    std::string data(memory[psn].begin(), memory[psn].end() - SPARE_SIZE);
    std::cout << "P_R " << psn << " -> " << data << std::endl;
    return data;
}

std::string FlashMemory::Flash_write(int psn, const std::string& data) {
    if (psn < 0 || psn >= memory.size() || data.size() > SECTOR_SIZE) {
        return "Error: 쓰기 연산 불가";
    }

    // 섹터가 비어 있는지 확인
    for (char c : memory[psn]) {
        if (c != 0) {
            return "Error: 섹터가 비어 있지 않음";
        }
    }

    std::copy(data.begin(), data.end(), memory[psn].begin());
    std::cout << "P_W " << psn << " " << data << " -> 쓰기 연산 완료" << std::endl;
    return "쓰기 연산 완료";
}

std::string FlashMemory::Flash_erase(int pbn) {
    int startSector = pbn * BLOCK_SIZE;
    int endSector = startSector + BLOCK_SIZE;
    if (startSector < 0 || endSector > memory.size()) {
        return "Error: 지우기 연산 불가";
    }
    for (int i = startSector; i < endSector; ++i) {
        std::fill(memory[i].begin(), memory[i].end(), 0);
    }
    std::cout << "P_E " << pbn << " -> 지우기 연산 수행" << std::endl;
    return "지우기 연산 수행";
}

void FlashMemory::print_memory_to_file(const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "파일을 열 수 없습니다: " << filename << std::endl;
        return;
    }
    for (int i = 0; i < memory.size(); ++i) {
        // 섹터 번호 출력
        file << i << " / ";

        // 저장된 값 출력 (섹터 영역)
        for (int j = 0; j < SECTOR_SIZE; ++j) {
            file << memory[i][j];
        }

        // 여분 영역 출력
        for (int j = SECTOR_SIZE; j < SECTOR_SIZE + SPARE_SIZE; ++j) {
            file << memory[i][j];
        }

        file << "\n";
    }

    file.close();
    std::cout << "플래시 메모리 상태가 파일에 저장됨 " << filename << std::endl;
}