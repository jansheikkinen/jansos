#ifndef ASM_IO_H
#define ASM_IO_H

// return the byte at the given port address
extern unsigned char port_inb(unsigned short);

// write a byte at the given port address
extern void port_outb(unsigned short, unsigned char);

#endif
