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
    global _start

_start:
    ;call _printPromptNumber
    ;call _inputNumber
    call _printPromptString
    call _inputString
    ;call _printOutputNumber
    ;call _printNumber
    call _printOutputString
    call _printString

    ;mov rax, 1
    ;mov rdi, 1
    ;mov rsi, text
    ;mov rdx, 14
    ;syscall

    mov rax, 60
    mov rdi, 0
    syscall


_inputString:
    mov rax, 0
    mov rdi, 0 ; 0 -> STDIN
    mov rsi, string
    mov rdx, 64
    syscall
    ret



_printPromptString:
    mov rax, 1
    mov rdi, 1
    mov rsi, promptString
    mov rdx, 14
    syscall 
    ret


_printOutputString:
    mov rax, 1
    mov rdi, 1
    mov rsi, outputString
    mov rdx, 19
    syscall 
    ret


_printString:
    mov rax, 1
    mov rdi, 1
    mov rsi, string
    mov rdx, 64
    syscall 
    ret


