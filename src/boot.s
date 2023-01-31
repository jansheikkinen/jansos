/* boot.s */

/* multiboot header */
.set ALIGN,    1 << 0
.set MEMINFO,  1 << 1
.set FLAGS,    ALIGN | MEMINFO
.set MAGIC,    0x1BADB002
.set CHECKSUM, -(MAGIC + FLAGS)

.section .multiboot
.align 4
.long MAGIC
.long FLAGS
.long CHECKSUM

/* stack */
.section .bss
.align   16

stack_bottom:
.skip 16384
stack_top:

/* entry point */
.section .text
.global _start
.type _start, @function
_start:
  /* set stack pointer to top of stack */
  mov $stack_top, %esp

  /* high-level kernel */
  call k_main

  /* halt the processor */
  cli
1:
  hlt
  jmp 1b

/* debug symbol */
.size _start, . - _start
