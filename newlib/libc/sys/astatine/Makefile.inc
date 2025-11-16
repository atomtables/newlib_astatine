NASM ?= nasm

%.o: %.asm
	$(NASM) -f elf32 -o $@ $<

libc_a_SOURCES += %D%/syscalls.c