// kernel.c

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "vga/terminal.h"

#ifdef __linux__
#error "not using a cross-compiler"
#endif

#ifndef __i386__
#error "kernel only works for x86"
#endif

int k_main(void) {
  struct Terminal term;
  term_init(&term);
  term_puts(&term, "Hello, world!\n");

  return 0;
}
