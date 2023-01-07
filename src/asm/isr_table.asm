; isr_table.asm

%macro isr_err_stub 1
isr_stub_%+%1:
  call exception_handler
  iret
%endmacro

%macro isr_no_err_stub 1
isr_stub_%+%1:
  call exception_handler
  iret
%endmacro

extern exception_handler
isr_no_err_stub 0  ; 0x0
isr_no_err_stub 1  ; 0x1
isr_no_err_stub 2  ; 0x2
isr_no_err_stub 3  ; 0x3
isr_no_err_stub 4  ; 0x4
isr_no_err_stub 5  ; 0x5
isr_no_err_stub 6  ; 0x6
isr_no_err_stub 7  ; 0x7
isr_err_stub    8  ; 0x8
isr_no_err_stub 9  ; 0x9
isr_err_stub    10 ; 0xA
isr_err_stub    11 ; 0xB
isr_err_stub    12 ; 0xC
isr_err_stub    13 ; 0xD
isr_err_stub    14 ; 0xE
isr_no_err_stub 15 ; 0xF
isr_no_err_stub 16 ; 0x10
isr_err_stub    17 ; 0x11
isr_no_err_stub 18 ; 0x12
isr_no_err_stub 19 ; 0x13
isr_no_err_stub 20 ; 0x14
isr_no_err_stub 21 ; 0x15
isr_no_err_stub 22 ; 0x16
isr_no_err_stub 23 ; 0x17
isr_no_err_stub 24 ; 0x18
isr_no_err_stub 25 ; 0x19
isr_no_err_stub 26 ; 0x1A
isr_no_err_stub 27 ; 0x1B
isr_no_err_stub 28 ; 0x1C
isr_no_err_stub 29 ; 0x1D
isr_err_stub    30 ; 0x1E
isr_no_err_stub 31 ; 0x1F

global isr_stub_table
isr_stub_table:
  %assign i 0
  %rep 32
  dd isr_stub_%+i
  %assign i i + 1
  %endrep
