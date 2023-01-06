#ifndef IDT_H
#define IDT_H

#define IDT_SIZE 256
#define INTERRUPT_GATE 0x8E
#define KERNEL_CODE_SEGMENT_OFFSET 0x08

#define PIC1_CMD  0x20
#define PIC1_DATA 0x21
#define PIC2_CMD  0xA0
#define PIC2_DATA 0xA1

struct idt_entry {
  unsigned short offset_low;
  unsigned short selector;
  unsigned char reserved;
  unsigned char attributes;
  unsigned short offset_high;
} __attribute__((packed));

struct idtr {
  unsigned short base;
  unsigned int limit;
} __attribute__((packed));

void idt_set_descriptor(unsigned short, unsigned long, unsigned short);

void idt_init(void);

#endif
