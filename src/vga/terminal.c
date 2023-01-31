// terminal.c

#include "terminal.h"
#include "../string.h"

#define VGA_BUFFER ((uint16_t*)0xB8000)
#define VGA_INDEX(x, y) pos_to_index((x), (y), VGA_WIDTH)

const size_t VGA_WIDTH = 80;
const size_t VGA_HEIGHT = 25;
const size_t VGA_SIZE = (VGA_WIDTH * VGA_HEIGHT) * sizeof(uint16_t);

static inline uint8_t vga_color(enum VGAColors fg, enum VGAColors bg) {
  return fg | bg << 4;
}

static inline uint16_t vga_char(unsigned char c, uint8_t color) {
  return (uint16_t)c | (uint16_t)color << 8;
}

static inline size_t pos_to_index(size_t x, size_t y, size_t width) {
  return (y * width) + x;
}

void term_init(struct Terminal* term) {
  term->row = 0, term->col = 0;
  term->color = vga_color(VGA_WHITE, VGA_BLACK);
  term->buffer = VGA_BUFFER;

  for(size_t y = 0; y < VGA_HEIGHT; y++) {
    for(size_t x = 0; x < VGA_WIDTH; x++) {
      term->buffer[VGA_INDEX(x, y)] = vga_char(' ', term->color);
    }
  }
}

void term_set_color(struct Terminal* term, uint8_t color) {
  term->color = color;
}

void term_putc_at(struct Terminal* term, unsigned char c,
    size_t x, size_t y, uint8_t color) {
  const size_t i = VGA_INDEX(x, y);
  if(i < VGA_SIZE) term->buffer[i] = vga_char(c, color);
}

void term_putc(struct Terminal* term, unsigned char c) {
  switch(c) {
    case '\n':
      term->row += 1; term->col = 0; break;
    case '\b':
      term->col -= 1; break;
    default:
      term_putc_at(term, c, term->col, term->row, term->color);
  }

  if(++term->col >= VGA_WIDTH) {
    term->col = 0;
    if(++term->row >= VGA_HEIGHT)
      term->row = 0;
  }
}

void term_put(struct Terminal* term, const char* data, size_t len) {
  for(size_t i = 0; i < len; i++)
    term_putc(term, data[i]);
}

void term_puts(struct Terminal* term, const char* str) {
  term_put(term, str, strlen(str));
}
