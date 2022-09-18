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



section .text
    global _start
    extern printf
    extern scanf
    extern exit


_start:
    
    lea rdi, [promptNumber]
    call printf

    call exit
    ret

