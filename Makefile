ASM = nasm
ASM_FLAGS = -f elf32

CC = gcc
CFLAGS = -Wall -Wextra -pedantic -g -fno-stack-protector -m32 -c -nostdlib -ffreestanding

LD = ld
LD_FLAGS = -m elf_i386 -nostdlib -T

C_SRC = $(wildcard src/*.c) $(wildcard src/**/*.c)
C_OBJ = $(C_SRC:.c=.o)

ASM_SRC = $(wildcard src/*.asm) $(wildcard src/**/*.asm)
ASM_OBJ = $(ASM_SRC:.asm=.o)

BUILD = build

all: clear dirs clean run

dirs:
	mkdir -p $(BUILD) src tests

run: build
	qemu-system-i386 -kernel $(BUILD)/kernel-69

build: $(C_OBJ) $(ASM_OBJ)
	$(LD) $(LD_FLAGS) link.ld -o build/kernel-69 $(C_OBJ) $(ASM_OBJ)

%.o: %.asm
	$(ASM) $(ASM_FLAGS) -o $@ $<

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm -Rf $(C_OBJ) $(ASM_OBJ) build/*

clear:
	clear
