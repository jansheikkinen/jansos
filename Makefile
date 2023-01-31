# Makefile

AS = i686-elf-as
CC = i686-elf-gcc
LIBS = -lgcc
CFLAGS = -ffreestanding -nostdlib -O2 -std=gnu17 -Wall -Wextra -Wshadow \
				-Wwrite-strings -Wstrict-prototypes $(LIBS)

C_SRC = $(wildcard src/*.c) $(wildcard src/**/*.c)
S_SRC = $(wildcard src/*.s) $(wildcard src/**/*.s)
OBJ = $(C_SRC:.c=.o) $(S_SRC:.s=.o)

BUILD = build
LINK_FILE = linker.ld

all: clear clean dirs run

intercept: clean
	intercept-build --append make build

dirs:
	mkdir -p $(BUILD)/iso/boot/grub src tests doc

run: mkrescue
	qemu-system-i386 -cdrom $(BUILD)/kernel.iso

mkrescue: build
	cp $(BUILD)/kernel.bin $(BUILD)/iso/boot/kernel.bin
	cp grub.cfg $(BUILD)/iso/boot/grub/grub.cfg
	grub-mkrescue -o $(BUILD)/kernel.iso $(BUILD)/iso

build: $(OBJ)
	$(CC) -T $(LINK_FILE) $(CFLAGS) $(INCLUDE) -o $(BUILD)/kernel.bin $?

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDE) -o $@ -c $<

%.o: %.s
	$(AS) -o $@ -c $<

clean:
	rm -Rf $(OBJ) $(BUILD)/*

clear:
	clear
