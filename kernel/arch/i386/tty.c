#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include <kernel/tty.h>

#include "vga.h"

// définir la taille du terminal
static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;
static uint16_t* const VGA_MEMORY = (uint16_t*) 0xB8000;

static size_t terminal_row;
static size_t terminal_column;
static uint8_t terminal_color;
static uint16_t* terminal_buffer;

static uint8_t ttet;
static uint8_t ttee;

// initialiser le terminal (couleur, emplacement du texte)
void terminal_initialize(void) {
	terminal_row = 0;
	terminal_column = 0;
	//terminal_bg_color = VGA_COLOR_BLACK;
	//terminal_font_color = VGA_COLOR_LIGHT_GREY;
	terminal_color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
	terminal_buffer = VGA_MEMORY;
	for (size_t y = 0; y < VGA_HEIGHT; y++) {
		for (size_t x = 0; x < VGA_WIDTH; x++) {
			const size_t index = y * VGA_WIDTH + x;
			terminal_buffer[index] = vga_entry(' ', terminal_color);
		}
	}
}

// fonction à définir...
void terminal_putentryat(unsigned char c, uint8_t color, size_t x, size_t y) {
	const size_t index = y * VGA_WIDTH + x;
	terminal_buffer[index] = vga_entry(c, color);
}

// 'définir' le caractère a écrire et l'envoyer dans la fonction 'terminal_putentryat'
void terminal_putchar(char c) {
	unsigned char uc = c;
	terminal_putentryat(uc, terminal_color, terminal_column, terminal_row);
	if (++terminal_column == VGA_WIDTH) {
		terminal_column = 0;
		if (++terminal_row == VGA_HEIGHT)
			terminal_row = 0;
	}
	if (c == '\n'){
		terminal_row = terminal_row + 1;
		terminal_column = 0;
	}
}

// fonction pour changer la couleur du texte et du fond
void change_color(uint8_t color) {

	ttet = VGA_COLOR_BROWN;
	ttee = VGA_COLOR_LIGHT_BROWN;

	if (color == 1) {
		terminal_color = vga_entry_color(ttet, ttee);
	}else if (color == 2) {
		terminal_color = vga_entry_color(VGA_COLOR_BLUE, VGA_COLOR_GREEN);
	}else if (color == 3) {
		terminal_color = vga_entry_color(VGA_COLOR_BLUE, VGA_COLOR_GREEN);
	}else if (color == 4) {
		terminal_color = vga_entry_color(VGA_COLOR_BLUE, VGA_COLOR_GREEN);
	}else if (color == 5) {
		terminal_color = vga_entry_color(VGA_COLOR_BLUE, VGA_COLOR_GREEN);
	}
}


void terminal_write(const char* data, size_t size) {
	for (size_t i = 0; i < size; i++)
		terminal_putchar(data[i]);
}

void terminal_writestring(const char* data) {
	terminal_write(data, strlen(data));
}
