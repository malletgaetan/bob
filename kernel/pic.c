#include "types.h"
#include "x86.h"

#define PIC1		0x20		/* IO base address for master PIC */
#define PIC2		0xA0		/* IO base address for slave PIC */
#define PIC1_COMMAND	PIC1
#define PIC1_DATA	(PIC1+1)
#define PIC2_COMMAND	PIC2
#define PIC2_DATA	(PIC2+1)

#define ICW1_ICW4	0x01		/* Indicates that ICW4 will be present */
#define ICW1_SINGLE	0x02		/* Single (cascade) mode */
#define ICW1_INTERVAL4	0x04		/* Call address interval 4 (8) */
#define ICW1_LEVEL	0x08		/* Level triggered (edge) mode */
#define ICW1_INIT	0x10		/* Initialization - required! */
 
#define ICW4_8086	0x01		/* 8086/88 (MCS-80/85) mode */
#define ICW4_AUTO	0x02		/* Auto (normal) EOI */
#define ICW4_BUF_SLAVE	0x08		/* Buffered mode/slave */
#define ICW4_BUF_MASTER	0x0C		/* Buffered mode/master */
#define ICW4_SFNM	0x10		/* Special fully nested (not) */

void init_pic(void)
{
	outb(0x20, 0x11);
	outb(0xa0, 0x11);
	/* io_wait(); */
	outb(0x21, 0x20);
	outb(0xa1, 0x70);
	/* io_wait(); */
	outb(0x21, 0x04);
	outb(0xa1, 0x02);
	/* io_wait(); */
	outb(0x21, 0x01);
	outb(0xa1, 0x01);
	/* io_wait(); */
	outb(0x21, 0x0);
	outb(0xa1, 0x0);
}



/* void init_pic(void) */
/* { */
/* 	outb(PIC1_COMMAND, ICW1_INIT | ICW1_ICW4);  // starts the initialization sequence (in cascade mode) */
/* 	io_wait(); */
/* 	outb(PIC2_COMMAND, ICW1_INIT | ICW1_ICW4); */
/* 	io_wait(); */
/* 	outb(PIC1_DATA, 0x20);                 // ICW2: Master PIC vector offset */
/* 	io_wait(); */
/* 	outb(PIC2_DATA, 0x70);                 // ICW2: Slave PIC vector offset */
/* 	io_wait(); */
/* 	outb(PIC1_DATA, 4);                       // ICW3: tell Master PIC that there is a slave PIC at IRQ2 (0000 0100) */
/* 	io_wait(); */
/* 	outb(PIC2_DATA, 2);                       // ICW3: tell Slave PIC its cascade identity (0000 0010) */
/* 	io_wait(); */
/* 	outb(PIC1_DATA, ICW4_8086);               // ICW4: have the PICs use 8086 mode (and not 8080 mode) */
/* 	io_wait(); */
/* 	outb(PIC2_DATA, ICW4_8086); */
/* 	io_wait(); */
/* 	outb(PIC1_DATA, 0x00); // no mask */
/* 	outb(PIC2_DATA, 0x00); */
/* } */
