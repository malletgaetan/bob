OBJ=floppy
CC=i686-elf-gcc 
LD=i686-elf-ld
CFLAGS=-std=gnu99 -ffreestanding -Wall -Wextra

all: $(OBJ)

$(OBJ): kernel

kernel: main.o screen.o
	$(LD) --oformat binary -Ttext 1000 $^ -o kernel

main.o: main.s
	nasm -f elf32 -o $@ $^

.o: .c 
	$(CC) -c $^

fclean:
	rm -f *.o kernel
