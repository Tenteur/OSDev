#include <stdio.h>

#include <kernel/tty.h>

void kernel_main(void) {
	terminal_initialize();
	printf("Hello, kernel World!\n");
	change_color("red", "bg");
	printf("this is now a new line !\n");
	change_color("red", "f");
	printf("now change the color !");
	//printf(inportb(0x64));
	//printf(inportb(0x60));
	//printf(outportb(0x64));
	
}
