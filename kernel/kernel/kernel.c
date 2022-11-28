#include <stdio.h>

#include <kernel/tty.h>
#include "../include/kernel/kernel.h"


void kernel_main(void) {
	change_color(0, 0);
	terminal_initialize();
	printf("Hello, kernel World!\n");
	change_color(4, 2);
	printf("this is now a new line !\n");
	change_color(1, 3);
	printf("now change the color !");
}

void execute_command(char* input)
{

}