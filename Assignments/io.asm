;
; Program: IO
; Description: This program takes a number and string via C scanf(), outputs them using C printf()
; 
; Input: number, string
; Ouput: number, string
;

section .data
    promptNumber: db "Input number:", 0
    promptString: db "Input string:", 0

    inputNumber: db "%d", 0
    inputString: db "%s", 0

    printNumber: db "%d", 0x0a, 0
    printString: db "%s", 0x0a, 0

section .bss
    number: resb 4

section .text
    global _start
    extern printf
    extern scanf
    extern exit


_start:
    
    lea rdi, [promptNumber]
    call printf
    lea rdi, [inputNumber]
    mov rdx, number
    lea rsi, rdx
    call scanf
    lea rdi, [printNumber]
    mov rsi, [number]
    call printf
    

    call exit
    ret





