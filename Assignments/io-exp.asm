;
; Program: IO
; Description: This program takes a number and string via C scanf(), outputs them using C printf()
; 
; Input: number, string
; Ouput: number, string
;

section .data
    prompt: db "Enter string:", 0

    input: db "%s", 0

    print: db "%s", 0x0a, 0

section .bss
    string: resb 64

section .text
    global _start
    extern printf
    extern scanf
    extern exit


_start:

    ; Ask user for string
    lea rdi, [prompt]
    xor rax, rax
    call printf
    ; scanf() / input the string
    lea rdi, [input]
    mov rsi, string
    call scanf
    ; printf() / output the string
    lea rdi, [print]
    mov rsi, [string]
    xor rax, rax
    call printf


    call exit
    ret

