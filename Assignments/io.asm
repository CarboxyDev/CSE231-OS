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
    xor rax, rax ; Zero'ing the rax register as it signifies the number of floating pt registers used
    call printf

    ; scanf() / input the number
    lea rdi, [inputNumber]
    mov rsi, number
    call scanf

    ; Ask user for string
    lea rdi, [promptString]
    xor rax, rax
    call printf

    ; scanf() / input the string
    lea rdi, [inputString]
    lea rsi, string
    call scanf




    ; printf() / output the number
    lea rdi, [printNumber]
    mov rsi, [number]
    xor rax, rax
    call printf


    ; printf() / output the string
    lea rdi, [printString]
    mov rsi, [string]
    xor rax, rax
    add rsp, 8
    call printf


        
    ; Exit the program safely (Using C exit function)
    call exit
    ret





