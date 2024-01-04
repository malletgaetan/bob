OBJ=kernel
CC=i686-elf-gcc 
LD=i686-elf-ld
CFLAGS=-std=gnu99 -ffreestanding -Wall -Wextra

all: $(OBJ)

$(OBJ): main.o pic.o screen.o int.o interrupts.o idt.o
	$(LD) --oformat binary -Ttext 1000 $^ -o kernel
	# objcopy -O binary -j .text kernel.in kernel.bin

int.o: int.s
	nasm -f elf32 -o $@ $^

# main.o: main.s
# 	nasm -f elf32 -o $@ $^

.o: .c 
	$(CC) -c $^

fclean:
	rm -f *.o kernel

re: fclean all
