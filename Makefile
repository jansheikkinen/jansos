# Makefile

AS = i686-elf-as
CC = i686-elf-gcc
LIBS = -lgcc
CLAGS = -ffreestanding -nostdlib -O2 -std=gnu17 -Wall -Wextra -Wshadow \
				-Wwrite-strings -Wstrict-prototypes $(LIBS)

C_SRC = $(wildcard src/*.c) $(wildcard src/**/*.c)
S_SRC = $(wildcard src/*.s) $(wildcard src/**/*.s)
OBJ = $(C_SRC:.c=.o) $(S_SRC:.s=.o)

BUILD = build

all: clear dirs clean run

intercept: clean
	intercept-build --append make build

dirs:
	mkdir -p $(BUILD)/boot/grub src tests doc

run: mkrescue
	qemu-system-i386 -cdrom $(BUILD)/kernel.iso

mkrescue: build
	cp $(BUILD)/kernel.bin $(BUILD)/boot/kernel.bin
	cp grub.cfg $(BUILD)/boot/grub/grub.cfg
	grub-mkrescue -o $(BUILD)/kernel.iso $(BUILD)

build: $(OBJ)
	$(C)) $(CFLAGS) $(INCLUDE) -o $(BUILD)/kernel.bin $?

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDE) -o $@ $<

%.o: %.s
	$(AS) -o $@ $<

clean:
	rm -Rf $(OBJ) $(BUILD)/*

clear:
	clear
