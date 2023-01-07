; io.asm

bits 32

; char port_inb(unsigned short);
global port_inb
port_inb:
  mov edx, [esp + 4]
  in al, dx
  ret

; void port_outb(unsigned short, unsigned short);
global port_outb
port_outb:
  mov edx, [esp + 4]
  mov al, [esp + 8]
  out dx, al
  ret
