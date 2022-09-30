#include <stdio.h>

#include <kernel/tty.h>
#include <kernel/char.h>


void kernel_main(void) {
	terminal_initialize();
	printf("Hello, kernel World!\n");
	change_color(4, 2);
	printf("this is now a new line !\n");
	change_color(1, 3);
	printf("now change the color !");
}


uint8 inb(uint16 port)
{
    uint8 ret;
    asm volatile("inb %1, %0" : "=a"(ret) : "d"(port));
    return ret;
}

void outb(uint16 port, uint8 data)
{
    asm volatile("outb %0, %1" : "=a"(data) : "d"(port));
}

char get_input_keycode()
{
    char ch = 0;
    while ((ch = inb(KEYBOARD_PORT)) != 0) {
        if (ch > 0)
            return ch;
    }
    return ch;
}

/*
keep the cpu busy for doing nothing(nop)
so that io port will not be processed by cpu
here timer can also be used, but lets do this in looping counter
*/
void wait_for_io(uint32 timer_count)
{
    while (1) {
        asm volatile("nop");
        timer_count--;
        if (timer_count <= 0)
            break;
    }
}

void sleep(uint32 timer_count)
{
    wait_for_io(timer_count);
}

void test_input()
{
    char ch = 0;
    char keycode = 0;
    do {
        keycode = get_input_keycode();
        if (keycode == KEY_ENTER) {
            print_new_line();
        }
        else {
            ch = get_ascii_char(keycode);
            printf(ch);
        }
        sleep(0x02FFFFFF);
    } while (ch > 0);
}

void kernel_entry()
{
    change_color(5, 3);
    printf("\nType here, one key per second, ENTER to go to next line");
    test_input();
}