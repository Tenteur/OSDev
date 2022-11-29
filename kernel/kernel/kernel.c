#include <stdio.h>

#include <kernel/tty.h>
#include "../include/kernel/kernel.h"
#include "../include/kernel/idt.h"
#include "../include/kernel/isr.h"
#include "../include/kernel/timer.h"
#include "../include/kernel/drivers/keyboard.h"

//void start_kernel() {
//	printf("Installing interrupt service routines (ISRs).\n");
//	//isr_install();
//}

void kernel_main(void) {
	terminal_initialize();
	char c = "kernel world!";
	printf("c=%c\n", c);
	change_color(4, 2);
	printf("this is now a new line !\n");
	change_color(1, 3);
	printf("now change the color !");
}

void execute_command(char* input)
{
	change_color(4, 5);
	printf("Listening Inputs...");

}