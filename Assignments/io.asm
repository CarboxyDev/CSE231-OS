;
; Program: IO
; Description: This program takes a number and string as scanf(), outputs them as printf()
; 
; Input: number, string
; Ouput: number, string
;

    section .data
promptNumber:    db "Input number:",0x0a, 0


    section .text
    global main
    extern printf
    extern scanf

main:
    push rbp
    mov rbp, rsp
    lea rdi, [promptNumber]
    xor eax, eax
    call printf
    xor eax, eax
    pop rbp
    ret

