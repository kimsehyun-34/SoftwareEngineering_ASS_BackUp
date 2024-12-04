SECTOR_SIZE = 512
SPARE_SIZE = 16
BLOCK_SIZE = 32
FLASH_SIZE = 3 * 1024 * 1024
TOTAL_BLOCKS = FLASH_SIZE // (SECTOR_SIZE * BLOCK_SIZE)
SPARE_BLOCKS = int(TOTAL_BLOCKS * 0.05)

total_sectors = FLASH_SIZE // SECTOR_SIZE
total_spare_sectors = SPARE_BLOCKS * BLOCK_SIZE
total_memory_size = (total_sectors + total_spare_sectors) * (SECTOR_SIZE + SPARE_SIZE)

print(f"전체 플래시 메모리 용량: {total_memory_size / (1024 * 1024):.2f} MB")


SECTOR_SIZE = 512
SPARE_SIZE = 16
BLOCK_SIZE = 32
FLASH_SIZE = 3 * 1024 * 1024
TOTAL_BLOCKS = FLASH_SIZE // (SECTOR_SIZE * BLOCK_SIZE)
SPARE_BLOCKS = int(TOTAL_BLOCKS * 0.05)

total_sectors = FLASH_SIZE // SECTOR_SIZE
total_spare_sectors = SPARE_BLOCKS * BLOCK_SIZE
total_memory_size = total_sectors * SECTOR_SIZE
spare_memory_size = total_spare_sectors * SECTOR_SIZE

usable_memory_size = total_memory_size - spare_memory_size

print(f"사용자가 사용할 수 있는 용량: {usable_memory_size / (1024 * 1024):.2f} MB")

SECTOR_SIZE = 512
SPARE_SIZE = 16
BLOCK_SIZE = 32
FLASH_SIZE = 3 * 1024 * 1024
TOTAL_BLOCKS = FLASH_SIZE // (SECTOR_SIZE * BLOCK_SIZE)
SPARE_BLOCKS = int(TOTAL_BLOCKS * 0.05)

total_sectors = FLASH_SIZE // SECTOR_SIZE
total_spare_sectors = SPARE_BLOCKS * BLOCK_SIZE
total_memory_size = total_sectors * (SECTOR_SIZE + SPARE_SIZE)
spare_memory_size = total_spare_sectors * (SECTOR_SIZE + SPARE_SIZE)

# 섹터 번호와 구분자 문자열 크기 포함
total_file_size = total_memory_size + spare_memory_size + total_sectors * 10

print(f"최종 출력되는 txt 파일의 크기: {total_file_size // 1024} KB")

