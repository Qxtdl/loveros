ARCH	:=	i386
LOVEROS	:=	loveros

CC		:=	i686-elf-gcc
CFLAGS	:=	-std=gnu99 -nostdlib -ffreestanding -Wall -Wextra -r
AS		:=	i686-elf-as

SRCS 	:= $(shell find src -name '*.c')
BUILD 	:= build

all: clean compile assemble link iso run

clean:
	rm -rf $(BUILD)/*

compile:
	$(CC) $(SRCS) $(CFLAGS) -o $(BUILD)/kernel.o

assemble:
	$(AS) src/boot.s -o $(BUILD)/boot.o

link:
	$(CC) -T linker.ld -o $(BUILD)/$(LOVEROS).bin $(BUILD)/boot.o -nostdlib -ffreestanding $(BUILD)/kernel.o

iso:
	cp $(BUILD)/$(LOVEROS).bin isodir/boot/$(LOVEROS).bin
	grub-mkrescue -o $(BUILD)/$(LOVEROS).iso isodir

run:
	qemu-system-$(ARCH) -cdrom build/$(LOVEROS).iso

