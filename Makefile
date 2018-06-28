C_SOURCES = init/init.c \
            arm/mailboxes.c \
            arm/uart.c \
            arm/rand.c \
            arm/delays.c \
            arm/powerManagement.c \
            arm/framebuffer.c \
            lib/ctype.c \
            lib/memoryUtils.c \
            lib/debug.c \
            mm/mm.c \
            arm/mmu.c

C_OBJECTS = init.o \
			mailboxes.o \
			uart.o \
			rand.o \
			delays.o \
			powerManagement.o \
			framebuffer.o \
			ctype.o \
			memoryUtils.o \
			debug.o \
			mm.o \
			mmu.o

# aarch64-linux-gnu TOOLCHAIN!

ASM_SOURCES = arm/boot.S \
			arm/hardwareUtils.S
ASM_OBJECTS = boot.o \
			hardwareUtils.o

FONT_SOURCES = init/bootFonts/mainFont.psf
FONT_OBJECTS = mainFont.o

CC = aarch64-linux-gnu-gcc
CC_FLAGS = -O2 -ffreestanding -nostdlib -nostartfiles \
			-I include/ -mgeneral-regs-only

LD = aarch64-linux-gnu-ld
LD_FLAGS = -nostdlib -nostartfiles -T linker.ld
LD_OUTPUT = Image.elf

QEMU = qemu-system-aarch64
QEMU_FLAGS = -M raspi3 -serial stdio

ASM = aarch64-linux-gnu-as

OBJCOPY = aarch64-linux-gnu-objcopy
OBJCOPY_FLAGS = -O binary

.PHONY: all clean

all:
	$(ASM) -c arm/boot.S -o boot.o
	$(ASM) -c arm/hardwareUtils.S -o hardwareUtils.o

	$(LD) -r -b binary -o $(FONT_OBJECTS) $(FONT_SOURCES)
	$(CC) $(CC_FLAGS) -c $(C_SOURCES)
	$(LD) $(LD_FLAGS) $(ASM_OBJECTS) $(C_OBJECTS) $(FONT_OBJECTS) -o $(LD_OUTPUT)
	$(OBJCOPY) $(OBJCOPY_FLAGS) $(LD_OUTPUT) Image.img
	$(QEMU) $(QEMU_FLAGS) -kernel Image.img

clean:
	rm $(C_OBJECTS)
	rm $(ASM_OBJECTS)
	rm $(FONT_OBJECTS)
	rm Image.*