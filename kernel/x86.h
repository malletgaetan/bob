#ifndef X86_H
# define X86_H

# include "types.h"

static inline void outb(u16 port, u8 val)
{
    asm volatile ("outb %0, %1" : : "a"(val), "Nd"(port) : "memory");
    /* There's an outb %al, $imm8 encoding, for compile-time constant port numbers that fit in 8b. (N constraint).
     * Wider immediate constants would be truncated at assemble-time (e.g. "i" constraint).
     * The  outb  %al, %dx  encoding is the only option for all other cases.
     * %1 expands to %dx because  port  is a uint16_t.  %w1 could be used if we had the port number a wider C type */
}

static inline u8 inb(u16 port)
{
    u8 ret;
    asm volatile ("inb %1, %0"
                   : "=a"(ret)
                   : "Nd"(port)
                   : "memory");
    return ret;
}

static inline void io_wait(void)
{
    outb(0x80, 0);
}

// INFO gcc doesn't optimize out asm without output operand, no need for volatile
static inline void cli(void)
{
	asm ("cli" : : );
}

static inline void sti(void)
{
	asm ("sti" : : );
}

static inline void lidt(u32 base, u16 size)
{
    struct {
        u16 length;
        u32 base;
    } __attribute__((packed)) IDTR = { size, base };
 
    asm ( "lidt %0" : : "m"(IDTR) );  // let the compiler choose an addressing mode
}

#endif
