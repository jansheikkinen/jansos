// kernel.c

#define COLUMNS 80
#define LINES   25
#define CHAR_BYTES 2
#define SCREENSIZE COLUMNS * LINES * CHAR_BYTES

#define KEYBOARD_DATA_PORT 0x60
#define KEYBOARD_STATUS_PORT 0x64

#define IDT_SIZE 256
#define INTERRUPT_GATE 0x8E
#define KERNEL_CODE_SEGMENT_OFFSET 0x08

#define PIC1_CMD  0x20
#define PIC1_DATA 0x21
#define PIC2_CMD  0xA0
#define PIC2_DATA 0xA1

#define ENTER_KEY_CODE 0x1C

#define VIDEO_MEMORY_START 0xb8000

#define ENTER_KEYCODE 0x1C

unsigned char keyboard_map[128] = {
  0,  27, '1', '2', '3', '4', '5', '6', '7', '8',	/* 9 */
  '9', '0', '-', '=', '\b',	/* Backspace */
  '\t',			/* Tab */
  'q', 'w', 'e', 'r',	/* 19 */
  't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',	/* Enter key */
    0,			/* 29   - Control */
  'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';',	/* 39 */
 '\'', '`',   0,		/* Left shift */
 '\\', 'z', 'x', 'c', 'v', 'b', 'n',			/* 49 */
  'm', ',', '.', '/',   0,				/* Right shift */
  '*',
    0,	/* Alt */
  ' ',	/* Space bar */
    0,	/* Caps lock */
    0,	/* 59 - F1 key ... > */
    0,   0,   0,   0,   0,   0,   0,   0,
    0,	/* < ... F10 */
    0,	/* 69 - Num lock*/
    0,	/* Scroll Lock */
    0,	/* Home key */
    0,	/* Up Arrow */
    0,	/* Page Up */
  '-',
    0,	/* Left Arrow */
    0,
    0,	/* Right Arrow */
  '+',
    0,	/* 79 - End key*/
    0,	/* Down Arrow */
    0,	/* Page Down */
    0,	/* Insert Key */
    0,	/* Delete Key */
    0,   0,   0,
    0,	/* F11 Key */
    0,	/* F12 Key */
    0,	/* All other keys are undefined */
};

extern void keyboard_handler(void);
extern char read_port(unsigned short port);
extern void write_port(unsigned short port, unsigned char data);
extern void load_idt(unsigned long* idt_ptr);

unsigned int cursor_loc = 0;
char* vidptr = (char*)VIDEO_MEMORY_START;

struct IDT_entry {
  unsigned short offset_low;
  unsigned short selector;
  unsigned char zero;
  unsigned char attr;
  unsigned short offset_high;
};

struct IDT_entry IDT[IDT_SIZE];

void idt_init(void) {
  unsigned long kb_addr, idt_addr, idt_ptr[2];

  kb_addr = (unsigned long)keyboard_handler;
  IDT[PIC1_DATA].offset_low = kb_addr & 0xFFFF;
  IDT[PIC1_DATA].offset_high = (kb_addr & 0xFFFF0000) >> 16;
  IDT[PIC1_DATA].selector = KERNEL_CODE_SEGMENT_OFFSET;
  IDT[PIC1_DATA].zero = 0;
  IDT[PIC1_DATA].attr = INTERRUPT_GATE;

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

  // mask interrupts
  write_port(PIC1_DATA, 0xFF);
  write_port(PIC2_DATA, 0xFF);

  idt_addr = (unsigned long)IDT;
  idt_ptr[0] = (sizeof(struct IDT_entry) * IDT_SIZE) + ((idt_addr & 0xFFFF) << 16);
  idt_ptr[1] = idt_addr >> 16;

  load_idt(idt_ptr);
}

void kb_init(void) {
  // unmask IRQ1
  write_port(0x21, 0xFD);
}

void k_print(const char* str) {
  unsigned int i = 0;
  while(str[i]) {
    vidptr[cursor_loc++] = str[i++];
    vidptr[cursor_loc++] = 0x07;
  }
}

void k_print_newline(void) {
  const unsigned int LINE_SIZE = COLUMNS * CHAR_BYTES;
  cursor_loc += LINE_SIZE - cursor_loc % LINE_SIZE;
}

void k_clear_screen(void) {
  unsigned int i = 0;
  while(i < SCREENSIZE) {
    vidptr[i++] = ' ';
    vidptr[i++] = 0x07;
  }
}

void keyboard_handler_main(void) {
  unsigned char status; char keycode;

  write_port(PIC1_CMD, 0x20);

  status = read_port(KEYBOARD_STATUS_PORT);

  if(status & 0x01) {
    keycode = read_port(KEYBOARD_DATA_PORT);
    if(keycode < 0) return;

    if(keycode == ENTER_KEYCODE) {
      k_print_newline();
      return;
    }

    vidptr[cursor_loc++] = keyboard_map[(unsigned char)keycode];
    vidptr[cursor_loc++] = 0x07;
  }
}

void k_main(void) {
  const char* str = "Hello, world!";

  k_clear_screen();
  k_print(str);
  k_print_newline();

  idt_init();
  kb_init();

  while(1);
}
