#include "idt.h"
#include "types.h"
#include "x86.h"

void _asm_default_int(void);
void _asm_irq_0(void);
void _asm_irq_1(void);

static struct idtg_desc g_idt_gates[IDT_SIZE];
static struct idt_desc g_idt_desc;

void init_idt_gate(u16 select, u32 offset, u8 type, struct idtg_desc* desc) {
    desc->offset0_15 = (u16)(offset & 0xffff);
    desc->select = select;
    desc->type = type;
    desc->offset16_31 = (u16)(offset >> 16);
	desc->reserved = 0;
}

void init_idt(void)
{
	g_idt_desc.base = (u32)g_idt_gates;
	g_idt_desc.limit = IDT_SIZE * 8;
	u16 i = 0;

	while (i < IDT_SIZE)
	{
		init_idt_gate(0x08, (u32)&_asm_default_int, IDT_INT_GATE, &g_idt_gates[i]);
		++i;
	}
	init_idt_gate(0x08, (u32)&_asm_irq_0, (u8)IDT_INT_GATE, &g_idt_gates[32]);
	init_idt_gate(0x08, (u32)&_asm_irq_1, (u8)IDT_INT_GATE, &g_idt_gates[33]);

	__asm__ volatile ("lidt %0" : : "m"(g_idt_desc)); // load the new IDT
    __asm__ volatile ("sti"); // set the interrupt flag
}

