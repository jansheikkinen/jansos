; kernel.asm

bits 32

section .text
  align 4
  dd 0x1BADB002
  dd 0x00
  dd - (0x1BADB002 - 0x00)


global _start
global keyboard_handler
global read_port
global write_port
global load_idt

extern k_main
extern keyboard_handler_main

keyboard_handler:
  call keyboard_handler_main
  iretd

read_port:
  mov edx, [esp + 4]
  in al, dx
  ret

write_port:
  mov edx, [esp + 4]
  mov al, [esp + 8]
  out dx, al
  ret

load_idt:
  mov edx, [esp + 4]
  lidt [edx]
  sti
  ret

_start:
  cli
  mov esp, stack_space
  call k_main
  hlt

section .bss
  resb 8192
stack_space:
