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
            arm/mmu.c \
            arm/irq.c \
            arm/timer.c

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
			mmu.o \
			irq.o \
			timer.o

# aarch64-linux-gnu TOOLCHAIN!

ASM_SOURCES = arm/boot.S \
			arm/hardwareUtils.S \
			arm/io.S \
			arm/irq.S

ASM_OBJECTS = boot.o \
			hardwareUtils.o \
			io.o \
			irqASM.o

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

ASM = aarch64-linux-gnu-gcc
ASM_FLAGS = -I include/ -MMD

OBJCOPY = aarch64-linux-gnu-objcopy
OBJCOPY_FLAGS = -O binary

.PHONY: all clean

all:
	$(ASM) $(ASM_FLAGS) -c arm/boot.S -o boot.o
	$(ASM) -c arm/hardwareUtils.S -o hardwareUtils.o
	$(ASM) -c arm/io.S -o io.o
	$(ASM) -c arm/irq.S -o irqASM.o

	$(LD) -r -b binary -o $(FONT_OBJECTS) $(FONT_SOURCES)
	$(CC) $(CC_FLAGS) -c $(C_SOURCES)
	$(LD) $(LD_FLAGS) $(ASM_OBJECTS) $(FONT_OBJECTS) $(C_OBJECTS) -o $(LD_OUTPUT)
	$(OBJCOPY) $(OBJCOPY_FLAGS) $(LD_OUTPUT) kernel8.img
	$(QEMU) $(QEMU_FLAGS) -kernel kernel8.img

clean:
	rm $(C_OBJECTS)
	rm $(ASM_OBJECTS)
	rm $(FONT_OBJECTS)
	rm Image.*
	rm kernel8.*