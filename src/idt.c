// idt.c

#include "asm.h"
#include "interrupt.h"
#include "idt.h"

__attribute__((aligned(0x10))) struct idt_entry IDT[IDT_SIZE];

void idt_set_descriptor(unsigned short index, unsigned long isr,
    unsigned short flags) {
  IDT[index].offset_low = isr & 0xFFFF;
  IDT[index].offset_high = (isr & 0xFFFF0000) >> 16;
  IDT[index].selector = KERNEL_CODE_SEGMENT_OFFSET;
  IDT[index].attributes = flags;
  IDT[index].reserved = 0;
}

static void pic_init(void) {
  // ICW1 - initialisation; expects 3 more commands
  write_port(PIC1_CMD, 0x11);
  write_port(PIC2_CMD, 0x11);

  // ICW2 - vector offset for interrupt number
  write_port(PIC1_DATA, 0x20);
  write_port(PIC2_DATA, 0x28);

  // ICW3 - cascading off
  write_port(PIC1_DATA, 0x00);
  write_port(PIC2_DATA, 0x00);

  // ICW4 - environment; set 80x86 mode
  write_port(PIC1_DATA, 0x01);
  write_port(PIC2_DATA, 0x01);
  // initialisation end
}

void idt_init(void) {
  unsigned long idt_addr, idt_ptr[2];

  // exception handlers
  for(unsigned long i = 0; i < 0x20; i++) {
    idt_set_descriptor(i, (unsigned long)isr_stub_table[i], INTERRUPT_GATE);
  }

  idt_set_descriptor(0x21, (unsigned long)keyboard_handler, INTERRUPT_GATE);

  pic_init();

  // mask all interrupts
  write_port(PIC1_DATA, 0xFF);
  write_port(PIC2_DATA, 0xFF);

  idt_addr = (unsigned long)IDT;
  idt_ptr[0] = (sizeof(struct idt_entry) * IDT_SIZE) + ((idt_addr & 0xFFFF) << 16);
  idt_ptr[1] = idt_addr >> 16;

  load_idt(idt_ptr);
}
