section .text

global main 

main:
	mov rax, 1		;	write(
	mov rdi, 1		;		STDOUT_FILENO, 
	mov rsi, msg	;		"....WOODY....\n",
	mov rsi, msglen	;		14,
	syscall			;	);

	mov rax, 60		;	exit(
	mov rdi, 0		;		EXIT_SUCCESS
	syscall			;	);

section .rodata
	msg:	db "....WOODY....", 14
	msglen:	equ $ - msg
