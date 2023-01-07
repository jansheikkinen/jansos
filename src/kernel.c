// kernel.c

#include "idt.h"
#include "screen.h"
#include "keyboard.h"

void k_main(void) {
  const char* str = "Hello, world!";

  k_clear_screen();
  k_print(str);
  k_print_newline();

  idt_init();
  kb_init();

  while(1) __asm__("hlt");
}
