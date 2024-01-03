[ORG 0x0]
[BITS 16]

%define KSIZE
%define BASE 0x100

setup:
	mov ax, 0x07c0 ; where bootsector code will be placed in memory by BIOS -> 0x7c00 after shift
	mov ds, ax
	mov es, ax
	mov ax, 0x8000
	mov ss, ax
	mov sp, 0xf000 ; stack from 0x8f000 -> 0x80000 | 64kb

load_kernel:
	mov si, load
	call print

	mov [bootdrv], dl ; save current disk id

	; reset disk system
	xor ax, ax
	int 0x13

	push es
	mov ax, BASE
	mov es, ax
	mov bx, 0
	mov ah, 2
	mov al, KSIZE
	mov ch, 0
	mov cl, 2
	mov dh, 0
	mov dl, [bootdrv]
	int 0x13
	pop es

load_gdt:
	mov si, exe
	call print
	cli ; disable interrupts
	lgdt [gdtptr]
protected_mode_switch:
	mov eax, cr0
	or eax, 1
	mov cr0, eax
	jmp load_segment ; since org 0, can't reload code segment directly or would break everything
load_segment:
	mov ax, (gdt_ds - gdt)
	mov ds, ax
	mov fs, ax
	mov gs, ax
	mov es, ax
	mov ss, ax
	mov esp, 0x9F000
	jmp dword (gdt_cs - gdt):0x1000 ; reload code segment

print:
        push ax
        push bx
        mov ah, 0x0e ; BIOS tty
.print_loop:
        mov al, [si]
        cmp al, 0
        jz .print_end
        int 0x10 ; BIOS video mode interrupt
        inc si
        jmp .print_loop
.print_end:
		pop bx
		pop ax
        ret

bootdrv: db 0
load: db "bootloader: loading kernel", 10, 13, 0
exe: db "bootloader: executing kernel", 10, 13, 0

gdt:
	gdt_null: ; null gdt entry
		dq 0
	gdt_cs: ; gdt code segment
		dw 0xffff ; limit [0:15]
		db 0, 0, 0 ; base [0:23]
		db 0b10011011 ; access byte [0:7]
		db 0b11011111 ; limit [16:19] & flags[0:3]
		db 0 ; base [24:31]
	gdt_ds: ; gdt data segment
		dw 0xffff ; limit [0:15]
		db 0, 0, 0 ; base [0:23]
		db 0b10010011 ; access byte [0:7]
		db 0b11011111 ; limit [16:19] & flags[0:3]
		db 0 ; base [24:31]
gdtptr:
	dw (gdtptr - gdt) ; limit storage
	dd 0x07c00 + gdt ; linear address of base storage (ds(0x07c0) << 4 + offset)
	
times 510-($-$$) db 0
dw 0xaa55
