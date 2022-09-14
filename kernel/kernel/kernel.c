#include <stdio.h>

#include <kernel/tty.h>

void kernel_main(void) {
	terminal_initialize();
	printf("Hello, kernel World!\n");
	printf("this is now a new line !\n is this a newline ?");
	printf("now change the \r color !");
}
