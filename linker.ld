ENTRY(_start)

SECTIONS {
  . = 1M;

  /* multiboot header and code */
  .text BLOCK(4K) : ALIGN(4K) {
    *(.multiboot)
    *(.text)
  }

  /* RO data */
  .rodata BLOCK(4K) : ALIGN(4K) {
    *(.rodata)
  }

  /* initialised RW */
  .data BLOCK(4K) : ALIGN(4K) {
    *(.data)
  }

  /* uninitialised RW */
  .bss BLOCK(4K) : ALIGN(4K) {
    *(COMMON)
    *(.bss)
  }
}
