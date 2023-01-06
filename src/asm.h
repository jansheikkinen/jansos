#ifndef ASM_H
#define ASM_H

// a collection of functions defined in assembly


extern void keyboard_handler(void);
extern char read_port(unsigned short);
extern void write_port(unsigned short, unsigned short);
extern void load_idt(unsigned long*);

#endif
