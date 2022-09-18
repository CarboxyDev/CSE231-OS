;
; Program: IO
; Description: This program takes a number and string as scanf(), outputs them as printf()
; 
; Input: number, string
; Ouput: number, string
;

section .data
    promptNumber db "Input number:"
    promptString db "Input string:"
    outputNumber db "Your chosen number:"
    outputString db "Your chosen string:"

section .bss
    string resb 64
    number resb 16



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

