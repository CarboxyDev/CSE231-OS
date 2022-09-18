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
    string: resb 64

section .text
    global _start
    extern printf
    extern scanf
    extern exit


_start:
    
    ; Ask user for number
    lea rdi, [promptNumber]
    call printf

    ; scanf() / input the number
    lea rdi, [inputNumber]
    mov rsi, number
    call scanf

    ; Ask user for string
    lea rdi, [promptString]
    call printf

    ; scanf() / input the string
    lea rdi, [inputString]
    mov rsi, string
    call scanf




    ; printf() / output the number
    lea rdi, [printNumber]
    mov rsi, [number]
    call printf

    ; printf() / output the string
    ;lea rdi, [printString]
    ;mov rsi, [string]
    ;call printf


        
    ; Exit the program safely (Using C exit function)
    call exit
    ret





