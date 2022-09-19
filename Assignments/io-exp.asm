;
; Program: IO
; Description: This program takes a number and string via C scanf(), outputs them using C printf()
; 
; Input: number, string
; Ouput: number, string
;

section .data
    promptString: db "Input string:", 0

    inputString: db "%s", 0

    printString: db "%s", 0x0a, 0

section .bss
    string: resb 1

section .text
    global _start
    extern printf
    extern scanf
    extern exit


_start:
    

    ; Ask user for string
    lea rdi, [promptString]
    xor rax, rax
    call printf

    ; scanf() / input the string
    lea rdi, [inputString]
    mov rsi, string
    call scanf


    ; printf() / output the string
    lea rdi, [printString]
    mov rsi, [string]
    xor rax, rax
    call printf


        
    ; Exit the program safely (Using C exit function)
    call exit
    ret





