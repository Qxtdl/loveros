ARCH		:=	i386
LOVEROS		:=	loveros

CC			:=	i686-elf-gcc
CFLAGS		:=	-std=gnu99 -nostdlib -ffreestanding -Wall -Wextra -r
AS			:=	i686-elf-as

BUILD 		:= build
BIN_TARGET	:= $(BUILD)/$(LOVEROS).bin
ISO_TARGET	:= $(BUILD)/$(LOVEROS).iso

CSRCS := $(shell find src -name '*.c')
ASRCS := $(shell find src -name '*.s')
COBJS := $(patsubst %.c,$(BUILD)/%_c.o,$(CSRCS))
AOBJS := $(patsubst %.s,$(BUILD)/%_s.o,$(ASRCS))
OBJS  := $(COBJS) $(AOBJS)

all: clean $(OBJS) $(BIN_TARGET) $(ISO_TARGET)

clean:
	rm -rf $(BUILD)/*
	mkdir -p build

$(BUILD)/%_c.o: %.c
	mkdir -p $(dir $@)
	$(CC) $< $(CFLAGS) -o $@

$(BUILD)/%_s.o: %.s
	mkdir -p $(dir $@)
	$(AS) $(ASFLAGS) -c $< -o $@

$(BIN_TARGET): $(OBJS)
	$(CC) -T linker.ld -nostdlib -ffreestanding $(OBJS) -o $@

$(ISO_TARGET):
	cp $(BIN_TARGET) isodir/boot/$(LOVEROS).bin
	grub-mkrescue -o $(BUILD)/$(LOVEROS).iso isodir

run:
	qemu-system-$(ARCH) -d int -no-reboot -no-shutdown -monitor stdio \
	-cdrom build/$(LOVEROS).iso