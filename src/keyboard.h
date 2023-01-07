#ifndef KEYBOARD_H
#define KEYBOARD_H

#define KEYBOARD_DATA_PORT 0x60
#define KEYBOARD_STATUS_PORT 0x64

#define ENTER_KEYCODE 0x1C

void kb_init(void);
void keyboard_handler_main(void);

extern unsigned char keyboard_map[];

#endif
