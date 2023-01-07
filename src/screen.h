#ifndef SCREEN_H
#define SCREEN_H

#define COLUMNS 80
#define LINES   25
#define CHAR_BYTES 2
#define SCREENSIZE (COLUMNS * LINES * CHAR_BYTES)

#define VIDEO_MEMORY_START 0xb8000

void k_print(const char*);
void k_print_newline(void);
void k_clear_screen(void);

extern unsigned int cursor_loc;
extern char* vid_ptr;

#endif
