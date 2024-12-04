#include "FlashMemory.h"

int main() {
    FlashMemory flash;

    //flash.Flash_write(0, "A");

    /*flash.Flash_write(0, "A");
    flash.Flash_read(0);
    flash.Flash_write(0, "Ab'");
	flash.Flash_read(0);

	flash.Flash_write(5, "B");
	flash.Flash_write(6, "C");
	flash.Flash_write(7, "D");
	flash.Flash_read(5);
	flash.Flash_read(6);
	flash.Flash_read(7);

	flash.Flash_write(60, "F");

    flash.Flash_read(2);
    flash.Flash_erase(0);
    flash.Flash_read(0);*/

    flash.print_memory_to_file("flash_memory_state.txt");

    return 0;
}