// screen.c

#include "screen.h"

unsigned int cursor_loc = 0;
char* vid_ptr = (char*)VIDEO_MEMORY_START;

void k_print(const char* str) {
  unsigned int i = 0;
  while(str[i]) {
    vid_ptr[cursor_loc++] = str[i++];
    vid_ptr[cursor_loc++] = 0x07;
  }
}

void k_print_newline(void) {
  const unsigned int LINE_SIZE = COLUMNS * CHAR_BYTES;
  cursor_loc += LINE_SIZE - cursor_loc % LINE_SIZE;
}

void k_clear_screen(void) {
  unsigned int i = 0;
  while(i < SCREENSIZE) {
    vid_ptr[i++] = ' ';
    vid_ptr[i++] = 0x07;
  }
}
