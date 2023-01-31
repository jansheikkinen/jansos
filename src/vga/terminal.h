#pragma once

#include <stddef.h>
#include <stdint.h>

enum VGAColors {
  VGA_BLACK,
  VGA_BLUE,
  VGA_GREEN,
  VGA_CYAN,
  VGA_RED,
  VGA_MAGENTA,
  VGA_BROWN,
  VGA_LIGHT_GRAY,
  VGA_DARK_GRAY,
  VGA_LIGHT_BLUE,
  VGA_LIGHT_GREEN,
  VGA_LIGHT_CYAN,
  VGA_LIGHT_RED,
  VGA_LIGHT_MAGENTA,
  VGA_LIGHT_BROWN,
  VGA_WHITE,
};

const size_t VGA_WIDTH = 80;
const size_t VGA_HEIGHT = 25;
const size_t VGA_SIZE = (VGA_WIDTH * VGA_HEIGHT) * sizeof(uint16_t);

struct Terminal {
  size_t row, col;
  uint8_t color;
  uint16_t* buffer;
};

void term_init(struct Terminal*);

void term_set_color(struct Terminal*, uint8_t);
void term_putc_at(struct Terminal*, unsigned char, size_t, size_t, uint8_t);
void term_putc(struct Terminal*, unsigned char);

void term_put(struct Terminal*, const char*, size_t);
void term_puts(struct Terminal*, const char*);
