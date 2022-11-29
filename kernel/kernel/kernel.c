#include <stdio.h>

#include <kernel/tty.h>
#include "../include/kernel/util.h"
#include "../include/kernel/kernel.h"
#include "../include/kernel/mem.h"
#include "../include/kernel/idt.h"
#include "../include/kernel/isr.h"
#include "../include/kernel/timer.h"
#include "../include/kernel/drivers/keyboard.h"

void start_kernel(void) {
	printf("Installing interrupt service routines (ISRs).\n");
}

void kernel_main(void) {
	isr_install();
	terminal_initialize();
	printf("Hello kernel world!\n");
	change_color(1, 3);
	printf("now change the color !");
	execute_command();
}

void execute_command(char* input)
{
	change_color(4, 5);
	printf("Listening Inputs...");

}