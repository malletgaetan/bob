#include "types.h"
#include "idt.h"
#include "screen.h"
#include "x86.h"
#include "pic.h"

// INFO big issue you can here is ld actually compile and put everything in the same order as given arguments
// example: ld a.o b.o c.o, the a code will reside before the b code which will reside before the c code
// One funny ^^ things is that main, or _start isn't put at the top of the binary, which is required for us since our simple
// bootloader just jump directly to the first instructions of the kernel.
//
// possible solutions: 
// https://stackoverflow.com/questions/19470666/gcc-how-to-tell-gcc-to-put-the-main-function-at-the-start-of-the-text-sectio
// https://stackoverflow.com/questions/63807228/x86-assembly-what-is-the-difference-between-text-startup-section-and-text-sec
//
// for the moment, we'll just try to have main.c compile at the start with only main function in it

void _start(void)
{
	reset_screen();
	print((u8 *)"kernel: initialization...\n");
	init_idt();
	print((u8 *)"kernel: IDT loaded\n");
	init_pic();
	print((u8 *)"kernel: interrupts initialized\n");
	while (1) ;
}

