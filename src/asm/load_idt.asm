; load_idt.asm

bits 32

; void load_idt(unsigned long*);
global load_idt
load_idt:
  mov edx, [esp + 4]
  lidt [edx]
  sti
  ret
