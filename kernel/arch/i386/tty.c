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

static uint8_t font_color = VGA_COLOR_WHITE;
static uint8_t back_color = VGA_COLOR_BLACK;


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
	if (c == '\n') {
		terminal_color = vga_entry_color(VGA_COLOR_BLACK, VGA_COLOR_BLACK);
	}
	terminal_putentryat(uc, terminal_color, terminal_column, terminal_row);
	terminal_color = vga_entry_color(font_color, back_color);
	if (++terminal_column == VGA_WIDTH) {
		terminal_column = 0;
		if (++terminal_row == VGA_HEIGHT) {
			terminal_row = 0;
		}
	}
	if (c == '\n'){
		terminal_row = terminal_row + 1;
		terminal_column = 0;
	}
}

// fonction pour changer la couleur du texte et du fond
void change_color(uint8_t fcolor, uint8_t bgcolor) {

	if (fcolor == 1) {
		font_color = VGA_COLOR_BLUE;
	}else if (fcolor == 2) {
		font_color = VGA_COLOR_GREEN;
	}else if (fcolor == 3) {
		font_color = VGA_COLOR_RED;
	}else if (fcolor == 4) {
		font_color = VGA_COLOR_WHITE;
	}else if (fcolor == 5) {
		font_color = VGA_COLOR_BLACK;
	}

	if (bgcolor == 1) {
		back_color = VGA_COLOR_BLUE;
	}
	else if (bgcolor == 2) {
		back_color = VGA_COLOR_GREEN;
	}
	else if (bgcolor == 3) {
		back_color = VGA_COLOR_RED;
	}
	else if (bgcolor == 4) {
		back_color = VGA_COLOR_WHITE;
	}
	else if (bgcolor == 5) {
		back_color = VGA_COLOR_BLACK;
	}

	terminal_color = vga_entry_color(font_color, back_color);
}


void terminal_write(const char* data, size_t size) {
	for (size_t i = 0; i < size; i++)
		terminal_putchar(data[i]);
}

void terminal_writestring(const char* data) {
	terminal_write(data, strlen(data));
}

 void encodeGdtEntry(uint8_t* target, struct GDT source) {
	// Check the limit to make sure that it can be encoded
	if (source.limit > 0xFFFFF) {
		printf("GDT cannot encode limits larger than 0xFFFFF");
	}

	// Encode the limit
	target[0] = source.limit & 0xFF;
	target[1] = (source.limit >> 8) & 0xFF;
	target[6] = (source.limit >> 16) & 0x0F;

	// Encode the base
	target[2] = source.base & 0xFF;
	target[3] = (source.base >> 8) & 0xFF;
	target[4] = (source.base >> 16) & 0xFF;
	target[7] = (source.base >> 24) & 0xFF;

	// Encode the access byte
	target[5] = source.access_byte;

	// Encode the flags
	target[6] |= (source.flags << 4);
} 