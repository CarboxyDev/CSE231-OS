; This program is my first x86 Assembly program :)
; 
; Program: Exit
; Description: This program does nothing but just exits using an exit sys call (Linux)
; 
; Input: None
; Output: Exit status
;


	segment .text
	global _start

_start:
	mov eax,1         ; 1 is the exit syscall number
	mov ebx,5					; is the status value to return
	int 0x80					; executes sys call
