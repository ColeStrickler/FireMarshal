CC=riscv64-unknown-elf-gcc
CFLAGS=-mcmodel=medany -Wall -fno-common -fno-builtin -O0
LDFLAGS=-static -nostdlib -nostartfiles -lgcc

hello: hello.o crt.o syscalls.o
	$(CC) -T link.ld $(LDFLAGS) $^ -o $@

%.o: %.c util.h encoding.h
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.S
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o
	rm -f hello
