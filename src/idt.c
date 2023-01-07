// idt.c

#include "asm/io.h"
#include "asm/load_idt.h"
#include "asm/keyboard.h"
#include "asm/isr_table.h"
#include "pic.h"
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
  port_outb(PIC1_CMD, 0x11);
  port_outb(PIC2_CMD, 0x11);

  // ICW2 - vector offset for interrupt number
  port_outb(PIC1_DATA, 0x20);
  port_outb(PIC2_DATA, 0x28);

  // ICW3 - cascading off
  port_outb(PIC1_DATA, 0x00);
  port_outb(PIC2_DATA, 0x00);

  // ICW4 - environment; set 80x86 mode
  port_outb(PIC1_DATA, 0x01);
  port_outb(PIC2_DATA, 0x01);
  // initialisation end
}

void idt_init(void) {
  unsigned long idt_addr, idt_ptr[2];

  // exception handlers
  for(unsigned long i = 0; i < 0x20; i++) {
    idt_set_descriptor(i, (unsigned long)isr_stub_table[i], INTERRUPT_GATE);
  }

  // set up keyboard interrupt handling
  idt_set_descriptor(0x21, (unsigned long)keyboard_handler, INTERRUPT_GATE);

  // initialise the PICs
  pic_init();

  // mask all interrupts
  port_outb(PIC1_DATA, 0xFF);
  port_outb(PIC2_DATA, 0xFF);

  // load the idt
  idt_addr = (unsigned long)IDT;
  idt_ptr[0] = (sizeof(struct idt_entry) * IDT_SIZE) + ((idt_addr & 0xFFFF) << 16);
  idt_ptr[1] = idt_addr >> 16;

  load_idt(idt_ptr);
}
