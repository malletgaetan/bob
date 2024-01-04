#ifndef IDT_H
# define IDT_H

# include "types.h"

// https://wiki.osdev.org/Interrupt_Descriptor_Table

# define IDT_SIZE 0xff
# define IDT_INT_GATE 0x8e

// IDT Gate Descriptor
struct idtg_desc {
    u16 offset0_15; // address of entry point of the Interrupt Service Routine
    u16 select; // segment selector of addr `offset`
	u8 reserved; // set to 0
    u8 type; // gate type
    u16 offset16_31; // address of entry point of the Interrupt Service Routine
} __attribute__ ((packed));

// IDT Descriptor
struct idt_desc {
	u16 limit;
	u32 base; // linear address of idt_desc
} __attribute__ ((packed));

void init_idt_gate(u16 select, u32 offset, u8 type, struct idtg_desc* desc);
void init_idt(void);

#endif
