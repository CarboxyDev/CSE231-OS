;
; Program: Experimental Program
; Description: This is an experimental ASM program with no clear objective. Just meant for practice and experimentation.
; 
; Input: Undefined
; Ouput: Undefined
;

section .data
    prompt1 db "Input number: "
    prompt2 db "Input string: "
    output1 db "Your chosen number:"
    output2 db "Your chosen string:"


section .text
    global _start

_start:
    mov rax, 1
    mov rdi, 1
    mov rsi, text
    mov rdx, 14
    syscall

    mov rax, 60
    mov rdi, 0
    syscall



