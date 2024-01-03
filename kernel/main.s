[BITS 32]

EXTERN reset_screen, print
GLOBAL _start

_start:
	call reset_screen

    mov  eax, msg
    push eax
    call print
    pop  eax

    mov  eax, msg2
    push eax
    call print
    pop  eax


end:
    jmp end

msg  db "yooooooooooooooooooooo", 10, 0
msg2 db "shiiiiiiiiiiiiiiii", 10, 0
