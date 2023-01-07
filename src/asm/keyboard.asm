; keyboard.asm

bits 32

extern keyboard_handler_main

; void keyboard_handler(void);
global keyboard_handler
keyboard_handler:
  call keyboard_handler_main
  iretd
