#include <stdio.h>

#include <kernel/tty.h>

void kernel_main(void) {
	terminal_initialize();
	printf("Hello, kernel World!\n");
	printf("this is now a new line !\n is this a newline ?");
	terminal_changecolor();
	printf("now change the color !");
}
