; kernel.asm

bits 32

section .text
  align 4
  dd 0x1BADB002
  dd 0x00
  dd - (0x1BADB002 - 0x00)


global _start

extern k_main
_start:
  cli
  mov esp, stack_space
  call k_main
  hlt

section .bss
  resb 8192
stack_space:
