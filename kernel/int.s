extern isr_default_int, isr_clock_int, isr_keyboard_int
global _asm_default_int, _asm_irq_0, _asm_irq_1
[BITS 32]

_asm_default_int:
	call isr_default_int
	mov al, 0x20
	out 0x20, al
	iret

_asm_irq_0:
	call isr_clock_int
	mov al, 0x20
	out 0x20, al
	iret

_asm_irq_1:
	call isr_keyboard_int
	mov al, 0x20
	out 0x20, al
	iret
