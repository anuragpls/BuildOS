#include "console.h"
#include <stdint.h>

static const int VGA_WIDTH = 80;
static const int VGA_HEIGHT = 25;
static uint16_t* const VGA_MEMORY = (uint16_t*) 0xB8000;

static int cursor_row = 0;
static int cursor_col = 0;
static uint8_t console_color = 0x0F; // white on black

static uint8_t make_color(enum vga_color fg, enum vga_color bg) {
    return (uint8_t) fg | ((uint8_t) bg << 4);
}

static uint16_t make_entry(char c, uint8_t color) {
    return (uint16_t) c | ((uint16_t) color << 8);
}

void console_initialize(void) {
    for (int row = 0; row < VGA_HEIGHT; row++) {
        for (int col = 0; col < VGA_WIDTH; col++) {
            const int index = row * VGA_WIDTH + col;
            VGA_MEMORY[index] = make_entry(' ', console_color);
        }
    }
    cursor_row = 0;
    cursor_col = 0;
}

void console_set_color(enum vga_color fg, enum vga_color bg) {
    console_color = make_color(fg, bg);
}

static void console_scroll(void) {
    for (int row = 1; row < VGA_HEIGHT; row++) {
        for (int col = 0; col < VGA_WIDTH; col++) {
            VGA_MEMORY[(row - 1) * VGA_WIDTH + col] = VGA_MEMORY[row * VGA_WIDTH + col];
        }
    }
    for (int col = 0; col < VGA_WIDTH; col++) {
        VGA_MEMORY[(VGA_HEIGHT - 1) * VGA_WIDTH + col] = make_entry(' ', console_color);
    }
    cursor_row = VGA_HEIGHT - 1;
}

void console_putchar(char c) {
    if (c == '\n') {
        cursor_col = 0;
        cursor_row++;
    } else {
        const int index = cursor_row * VGA_WIDTH + cursor_col;
        VGA_MEMORY[index] = make_entry(c, console_color);
        cursor_col++;
        if (cursor_col == VGA_WIDTH) {
            cursor_col = 0;
            cursor_row++;
        }
    }

    if (cursor_row == VGA_HEIGHT) {
        console_scroll();
    }
}

void console_print(const char* str) {
    for (int i = 0; str[i] != '\0'; i++) {
        console_putchar(str[i]);
    }
}
