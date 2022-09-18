;
; Program: IO
; Description: This program takes a number and string as scanf(), outputs them as printf()
; 
; Input: number, string
; Ouput: number, string
;

    section .data
promptNumber: db "Input number:", 0x0a, 0


    section .text
    global _start
    extern printf
    extern scanf
    extern exit


_start:
    push rbp
    mov rbp, rsp
    lea rdi, [promptNumber]
    xor eax, eax
    call printf
    xor eax, eax
    pop rbp
    call exit
    ret

