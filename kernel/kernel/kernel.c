#include <stdio.h>

#include <kernel/tty.h>
#include "../include/kernel/kernel.h"
#include "../include/kernel/idt.h"
#include "../include/kernel/isr.h"
#include "../include/kernel/timer.h"
#include "../include/kernel/drivers/keyboard.h"


void kernel_main(void) {
	change_color(0, 0);
	terminal_initialize();
	char hellomess = "kernel world";
	printf("Hello,", hellomess, "!\n");
	change_color(4, 2);
	printf("this is now a new line !\n");
	change_color(1, 3);
	printf("now change the color !");
}

void execute_command(char* input)
{

}